//
//  cxAnimate.cpp
//  cxEngineCore
//
//  Created by xuhua on 7/3/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#include "cxSprite.h"
#include "cxAnimate.h"

CX_CPP_BEGIN

CX_IMPLEMENT(cxAnimate);

cxAnimate::cxAnimate()
{
    ptex = nullptr;
}

cxAnimate::~cxAnimate()
{
    cxObject::release(&ptex);
}

void cxAnimate::OnInit()
{
    CX_ASSERT(ptex != nullptr, "tex not set");
    cxTimeLine::OnInit();
    View()->To<cxSprite>()->SetTexture(ptex);
}

void cxAnimate::OnTime()
{
    cxInt idx = Index();
    cxTimePoint *tp = At(idx);
    cxTexCoord *coord = tp->Object()->To<cxTexCoord>();
    View()->To<cxSprite>()->SetTexCoord(coord);
}

cxAnimate *cxAnimate::AppFmt(cxFloat time,cchars fmt,...)
{
    CX_ASSERT(ptex != nullptr && cxStr::IsOK(fmt), "must set texture");
    char key[256]={0};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(key, 256, fmt, ap);
    va_end(ap);
    return Append(time, key);
}

cxAnimate *cxAnimate::Append(cxFloat time,cchars key)
{
    CX_ASSERT(ptex != nullptr && cxStr::IsOK(key), "must set texture");
    cxTexCoord *coord = ptex->At(key);
    cxTimePoint *tp = Push(time);
    tp->SetObject(coord);
    return this;
}

cxAnimate *cxAnimate::SetTexture(cchars key)
{
    CX_ASSERT(cxStr::IsOK(key), "key error");
    cxTexture *ctex = cxObject::gcpull<cxTexture>(key);
    CX_ASSERT(ctex != nullptr, "texture error %s",key);
    cxObject::swap(&ptex, ctex);
    return this;
}

CX_CPP_END

