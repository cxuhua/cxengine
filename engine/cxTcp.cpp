//
//  cxTcp.cpp
//  cxEngineCore
//
//  Created by xuhua on 7/3/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//


#include "cxEngine.h"
#include "cxTcp.h"

CX_CPP_BEGIN

CX_IMPLEMENT(cxTcp);

cxTcp::cxTcp()
{
    shutdown = false;
    connected = false;
    uv_loop_t *loop = cxEngine::Instance()->Looper();
    uv_tcp_init(loop, &handle);
    handle.data = this;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = 0;
    buffer = (char *)malloc(4096);
    bufsiz = 4096;
}

cxTcp::~cxTcp()
{
    free(buffer);
}

void cxTcp::OnClose()
{
    onClose.Fire(this);
}

void cxTcp::OnData(char *buffer,cxInt size)
{
    
}

void cxTcp::OnConnected()
{
    onConnected.Fire(this);
}

void cxTcp::OnIpAddr(cchars ip)
{
    
}

void cxTcp::shutdown_cb(uv_shutdown_t* req, int status)
{
    cxTcp *tcp = static_cast<cxTcp *>(req->data);
    tcp->shutdown = true;
}

void cxTcp::close_cb(uv_handle_t* handle)
{
    cxTcp *tcp = static_cast<cxTcp *>(handle->data);
    tcp->connected = false;
    tcp->OnClose();
    //PS:at close release tcp instance
    tcp->Release();
}

void cxTcp::alloc_cb(uv_handle_t* handle,size_t suggested,uv_buf_t* buf)
{
    cxTcp *tcp = static_cast<cxTcp *>(handle->data);
    if(suggested > tcp->bufsiz){
        tcp->buffer = (char *)realloc(tcp->buffer,suggested);
        tcp->bufsiz = (cxInt)suggested;
    }
    buf->base = tcp->buffer;
    buf->len = tcp->bufsiz;
}

void cxTcp::Close(cxInt err)
{
    error = err;
    if(!uv_is_closing((uv_handle_t *)&handle)){
        uv_close((uv_handle_t *)&handle, close_cb);
    }
}

void cxTcp::read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{
    cxTcp *tcp = static_cast<cxTcp *>(handle->data);
    if (nread >= 0) {
        tcp->OnData(buf->base, (cxInt)nread);
    }else{
        tcp->Close((cxInt)nread);
    }
}

void cxTcp::write_cb(uv_write_t* req, int status)
{
    cxStr *data = static_cast<cxStr *>(req->data);
    data->Release();
    free(req);
}

cxBool cxTcp::Write(cxStr *data)
{
    if(!connected){
        return false;
    }
    if(!uv_is_writable((uv_stream_t *)&handle)){
        return false;
    }
    uv_write_t *wreq = (uv_write_t *)malloc(sizeof(uv_write_t));
    data->Retain();
    wreq->data = data;
    uv_buf_t buf = uv_buf_init(data->Buffer(),data->Size());
    cxInt ret = uv_write(wreq, (uv_stream_t *)&this->handle, &buf, 1, write_cb);
    if(ret == 0){
        return true;
    }
    Close(ret);
    free(wreq);
    data->Release();
    return false;
}

void cxTcp::connect_cb(uv_connect_t* req, int status)
{
    cxTcp *tcp = static_cast<cxTcp *>(req->data);
    if(status != 0){
        tcp->Close(status);
        return;
    }
    tcp->connected = true;
    tcp->OnConnected();
    cxInt ret = uv_read_start(req->handle, alloc_cb, read_cb);
    if(ret != 0){
        tcp->Close(ret);
    }
}

void cxTcp::resolved_cb(uv_getaddrinfo_t *resolver, int status, struct addrinfo *res)
{
    cxTcp *tcp = static_cast<cxTcp *>(resolver->data);
    cxBool flags = false;
    if(status == 0){
        char addrs[17]={0};
        uv_ip4_name((struct sockaddr_in*)res->ai_addr, addrs, 16);
        tcp->OnIpAddr(addrs);
        tcp->connreq.data = tcp;
        flags=(uv_tcp_connect(&tcp->connreq, &tcp->handle, (struct sockaddr *)res->ai_addr, connect_cb) == 0);
    }
    if(!flags){
        tcp->Close(status);
    }
    uv_freeaddrinfo(res);
}

cxBool cxTcp::Connect(cchars host,cxInt port)
{
    uv_loop_t *loop = cxEngine::Instance()->Looper();
    resolver.data = this;
    char ports[16]={0};
    snprintf(ports, 16, "%d",port);
    cxInt ret = uv_getaddrinfo(loop,&resolver,resolved_cb,host,ports,&hints);
    if(ret != 0){
        Close(ret);
    }
    return ret == 0;
}


CX_CPP_END
