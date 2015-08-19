//
//  cxFrames.cpp
//  cxEngineCore
//
//  Created by xuhua on 7/8/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//


#include "cxFrames.h"

CX_CPP_BEGIN

CX_IMPLEMENT(cxFrames);

cxFrames::cxFrames()
{
    repeat = 1;
    blend = BlendFunc::ALPHA;
    scale = 1.0f;
    mapnum = 1;
    map[0] = 0;
    layer = 1;
    group = 1;
    offset = 0;
    time = 0.1f;
    count = 0;
    ptex = nullptr;
    points = cxArray::Alloc();
}

cxFrames::~cxFrames()
{
    cxObject::release(&ptex);
    points->Release();
}

const cxInt cxFrames::Num() const
{
    return mapnum;
}

const cxInt *cxFrames::Map() const
{
    return map;
}

void cxFrames::SetMaps(cxInt count,...)
{
    if(count == 0){
        return;
    }
    mapnum = count;
    va_list ap;
    va_start(ap, count);
    cxInt i = 0;
    do{
        map[i++] = va_arg(ap, cxInt);
    }while(--count > 0);
    va_end(ap);
}

void cxFrames::SetMaps(const cxStr *str)
{
    if(!cxStr::IsOK(str)){
        return;
    }
    SetMaps(str->ToString());
}

void cxFrames::SetMaps(cchars maps)
{
    if(!cxStr::IsOK(maps)){
        return;
    }
    char buffers[16]={0};
    cxInt len = (cxInt)strlen(maps);
    cxInt b = 0;
    mapnum = 0;
    for(cxInt i=0;i<len;i++){
        if(maps[i] != ',')continue;
        memcpy(buffers, maps + b, i-b);
        buffers[i - b] = 0;
        map[mapnum++] = atoi(buffers);
        b = i+1;
    }
    if(len > b){
        memcpy(buffers, maps + b, len-b);
        buffers[len - b] = 0;
        map[mapnum++] = atoi(buffers);
    }
}

void cxFrames::SetRepeat(const cxStr *str)
{
    if(!cxStr::IsOK(str)){
        return;
    }
    SetRepeat(str->ToString());
}

void cxFrames::SetRepeat(cchars str)
{
    if(!cxStr::IsOK(str)){
        return;
    }
    char buffers[16]={0};
    cxInt len = (cxInt)strlen(str);
    cxInt b = 0;
    repeats.clear();
    for(cxInt i=0;i<len;i++){
        if(str[i] != ',')continue;
        memcpy(buffers, str + b, i-b);
        buffers[i - b] = 0;
        repeats.push_back(atoi(buffers));
        b = i+1;
    }
    if(len > b){
        memcpy(buffers, str + b, len-b);
        buffers[len - b] = 0;
        repeats.push_back(atoi(buffers));
    }
}

const cxTexCoord *cxFrames::TexCoord(cxInt idx,cxInt layer) const
{
    const cxArray *layers = Layers(idx);
    return layers->At(layer)->To<cxTexCoord>();
}

const cxArray *cxFrames::Layers(cxInt idx) const
{
    const cxTimePoint *tp = At(idx);
    return tp->Object()->To<cxArray>();
}

cxTexCoord *cxFrames::layerEnd(cxInt group,cxInt count,cxInt layer)
{
    cxInt idx = group * Count() + count - 1;
    const cxTimePoint *tp = At(idx);
    cxArray *layers = tp->Object()->To<cxArray>();
    return layers->At(layer)->To<cxTexCoord>();
}

void cxFrames::loadlayers(cxArray *layers,cxInt c,cxInt g)
{
    const cxTexture *texture = Texture();
    for(cxInt l = 0;l < Layer();l++){
        char key[128]={0};
        snprintf(key, 128, "%d.%d.png",Offset()+g*100+c,l);
        cxTexCoord *coord = texture->At(key);
        if(coord == nullptr && c > 0){
            coord = layerEnd(g, c, l);
        }
        CX_ASSERT(coord != nullptr, "%s texture key miss",key);
        layers->Append(coord);
    }
}

cxBool cxFrames::Init()
{
    CX_ASSERT(Texture() != nullptr && Count() > 0 && Group() > 0 && Layer() > 0, "data format error");
    for(cxInt g = 0;g < Group();g++){
        for(cxInt c = 0;c < Count();c++){
            cxFloat repeat = 1;
            if(c < repeats.size()){
                repeat = repeats.at(c);
            }
            cxTimePoint *tp = Append(Time() * repeat);
            cxArray *layers = cxArray::Alloc();
            tp->SetObject(layers);
            layers->Release();
            loadlayers(layers, c, g);
        }
    }
    return true;
}

cxFrames *cxFrames::SetBlend(const BlendFunc &func)
{
    blend = func;
    return this;
}

cxFrames *cxFrames::SetBlend(const cxStr *name)
{
    if(!cxStr::IsOK(name)){
        return this;
    }
    if(name->IsCaseEqu("ADD")){
        blend = BlendFunc::ADDITIVE;
        return this;
    }
    if(name->IsCaseEqu("MUL")){
        blend = BlendFunc::MULTIPLIED;
        return this;
    }
    if(name->IsCaseEqu("ALPHA")){
        blend = BlendFunc::ALPHA;
        return this;
    }
    return this;
}

const BlendFunc cxFrames::Blend() const
{
    return blend;
}

cxFrames *cxFrames::SetRepeat(cxInt v)
{
    repeat = v;
    return this;
}

const cxInt cxFrames::Repeat() const
{
    //forever loop play
    if(repeat == 0){
        return INT_MAX;
    }
    return repeat;
}

cxFrames *cxFrames::SetSize(const cxSize2F &v)
{
    size = v;
    return this;
}

const cxSize2F &cxFrames::Size() const
{
    return size;
}

cxFrames *cxFrames::SetScale(cxFloat v)
{
    CX_ASSERT(v > 0, "scale must > 0");
    scale = v;
    return this;
}

const cxFloat cxFrames::Scale() const
{
    return scale;
}

cxFrames *cxFrames::SetTexture(const cxTexture *atex)
{
    cxObject::swap(&ptex, atex);
    return this;
}

const cxTexture *cxFrames::Texture() const
{
    return ptex;
}

cxFrames *cxFrames::SetOffset(cxInt v)
{
    offset = v;
    return this;
}

const cxInt cxFrames::Offset() const
{
    return offset;
}

cxFrames *cxFrames::SetGroup(cxInt v)
{
    group = v;
    return this;
}

const cxInt cxFrames::Group() const
{
    return group;
}

cxFrames *cxFrames::SetLayer(cxInt v)
{
    layer = v;
    return this;
}

const cxInt cxFrames::Layer() const
{
    return layer;
}

cxFrames *cxFrames::SetCount(cxInt v)
{
    count = v;
    return this;
}

const cxInt cxFrames::Count() const
{
    return count;
}

cxFrames *cxFrames::SetTime(cxFloat v)
{
    time = v;
    return this;
}

const cxFloat cxFrames::Time() const
{
    return time;
}

const cxTimePoint *cxFrames::At(cxInt idx) const
{
    return points->At(idx)->To<cxTimePoint>();
}

cxTimePoint *cxFrames::Append(cxFloat time)
{
    cxTimePoint *tp = cxTimePoint::Create()->Init(time);
    points->Append(tp);
    return tp;
}

const cxArray *cxFrames::Points() const
{
    return points;
}

CX_CPP_END

