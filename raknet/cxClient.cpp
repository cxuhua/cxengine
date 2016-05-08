//
//  cxClient.cpp
//  RaknetServer
//
//  Created by xuhua on 5/4/16.
//  Copyright © 2016 xuhua. All rights reserved.
//


#include "cxClient.h"

CX_CPP_BEGIN

CX_IMPLEMENT(cxClient);

cxClient::cxClient()
{
    memset(&publicKey, 0, sizeof(publicKey));
    peer->Startup(1, &socket, 1);
}

cxClient::~cxClient()
{
    
}

void cxClient::SetPublicKey(cchars data)
{
    memcpy(publicKeyData, data, cat::EasyHandshake::PUBLIC_KEY_BYTES);
    publicKey.publicKeyMode = RakNet::PKM_ACCEPT_ANY_PUBLIC_KEY;
    publicKey.myPublicKey = publicKeyData;
}

void cxClient::OnPacket(RakNet::Packet *packet)
{
    RakNet::MessageID type = packet->data[0];
    switch (type) {
        case ID_CONNECTION_REQUEST_ACCEPTED:{
            remote = packet->guid;
            OnConnected();
            break;
        }
        case ID_CONNECTION_LOST:{
            OnLost();
            break;
        }
        case ID_CONNECTION_ATTEMPT_FAILED:{
            OnError(1);
            break;
        }
        case ID_DISCONNECTION_NOTIFICATION:{
            OnLost();
            break;
        }
        default:{
            cxRaknet::OnPacket(packet);
            break;
        }
    }
}

void cxClient::OnError(cxInt error)
{
    CX_LOGGER("OnError:%d",error);
}

void cxClient::OnConnected()
{
    CX_LOGGER("OnConnected");
}

void cxClient::OnLost()
{
    CX_LOGGER("OnLost");
}

void cxClient::OnMessage(RakNet::RakNetGUID clientId, const cxStr *message)
{
    CX_LOGGER("OnMessage %s",message->ToString());
}

RakNet::ConnectionAttemptResult cxClient::Connect(cchars host,cxInt port,cchars pass)
{
    if(publicKey.myPublicKey == NULL){
        CX_LOGGER("public key miss");
        return RakNet::SECURITY_INITIALIZATION_FAILED;
    }
    peer->SetOccasionalPing(true);
    return peer->Connect(host, port, pass, (int)strlen(pass),&publicKey);
}

CX_CPP_END

