//
//  cxMusic.cpp
//  cxEngineCore
//
//  Created by xuhua on 7/29/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#include "cxEngine.h"
#include <core/cxStr.h>
#include "cxMusic.h"

CX_CPP_BEGIN

CX_IMPLEMENT(cxMusic);

cxMusic::cxMusic()
{
    source = nullptr;
    Forever();
}

cxMusic::~cxMusic()
{
    source = nullptr;
}

void cxMusic::OnInit()
{
    CX_ASSERT(source != nullptr, "source not set");
    source->Play();
    cxAction::OnInit();
}

void cxMusic::OnReset()
{
    source->Reset();
    cxAction::OnReset();
}

void cxMusic::OnExit()
{
    source->Stop();
    cxAction::OnExit();
}

void cxMusic::OnStep(cxFloat dt)
{
    if(source->Update(dt)){
        Expire();
    }
    cxAction::OnStep(dt);
}

cxALSource *cxMusic::GetSource()
{
    return source;
}

cxMusic *cxMusic::Create(const cxStr *data,cxALBuffer::DataType type)
{
    cxMusic *ret = cxMusic::Create();
    cxALSource *source = cxOpenAL::Instance()->Source(data, type);
    if(source == nullptr){
        CX_ERROR("create music action error for data len=%d",data->Size());
        return ret;
    }
    cxObject::swap(&ret->source, source);
    return ret;
}

cxMusic *cxMusic::Create(cchars file,cchars key)
{
    if(key == nullptr){
        key = file;
    }
    cxMusic *ret = cxMusic::Create();
    cxALSource *source = cxOpenAL::Instance()->Source(file, key);
    if(source == nullptr){
        CX_ERROR("create music action error for file=%s",file);
        return ret;
    }
    ret->source = source;
    return ret;
}

CX_CPP_END

