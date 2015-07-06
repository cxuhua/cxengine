//
//  cxTimeLine.h
//  cxEngineCore
//
//  Created by xuhua on 7/2/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#ifndef cxEngineCore_cxTimeLine_h
#define cxEngineCore_cxTimeLine_h

#include <vector>
#include <core/cxArray.h>
#include "cxTexture.h"
#include "cxAction.h"

CX_CPP_BEGIN

class cxTimePoint : public cxObject
{
public:
    CX_DECLARE(cxTimePoint);
protected:
    explicit cxTimePoint();
    virtual ~cxTimePoint();
private:
    cxObject *object;
    cxFloat time;
public:
    cxTimePoint *Init(cxFloat at);
    
    cxObject *Object() const;
    void SetObject(cxObject *pobj);
    
    cxFloat Time() const;
};

class cxTimeLine : public cxAction
{
public:
    CX_DECLARE(cxTimeLine);
protected:
    explicit cxTimeLine();
    virtual ~cxTimeLine();
protected:
    virtual void OnTime(const cxTimePoint *tp);
    void OnStep(cxFloat dt);
    void OnInit();
    
    std::vector<cxFloat> times;
    cxArray *points;
    
    cxInt prev;  //
    cxInt idx;      //0-n
    cxInt from;     //0-(size-1);
    cxInt to;       //0-(size-1)
public:
    cxEvent<cxTimeLine,const cxTimePoint *> onTime;
public:
    cxTimeLine *SetRange(cxInt afrom,cxInt ato);
    cxInt Index() const;
    void UpdateTime();
    
    cxTimePoint *TimePoint();   //at OnTime invoke
    cxTimePoint *At(cxInt i);   //
    
    cxTimePoint *Append(cxFloat time);
    cxInt Size() const;
    
    cxAction *Reverse();
    cxAction *Clone();
};

CX_CPP_END

#endif


