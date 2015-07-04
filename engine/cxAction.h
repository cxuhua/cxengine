//
//  cxAction.h
//  cxEngineCore
//
//  Created by xuhua on 6/16/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#ifndef cxEngineCore_cxAction_h
#define cxEngineCore_cxAction_h

#include "cxTiming.h"
#include <math/cxPoint2F.h>
#include <math/cxPoint3F.h>
#include <math/cxSize2F.h>
#include <math/cxColor4F.h>

CX_CPP_BEGIN

typedef cxULong cxActionId;

class cxView;
class cxAction : public cxObject
{
    friend cxView;
public:
    CX_DECLARE(cxAction);
protected:
    explicit cxAction();
    virtual ~cxAction();
    virtual void OnInit();
    virtual void OnExit();
    virtual void OnStop();
    virtual void OnReset();
    virtual void OnStep(cxFloat dt);
    virtual cxBool Update(cxFloat dt);
private:
    cxULong actionId;
    cxTimingFunc timing;
    cxView *pview;
    cxFloat speed;
    cxFloat elapsed;
    cxFloat time;
    cxDouble prev;
    cxBool ispause;
    cxBool isinit;
    cxBool isexit;
    cxFloat deltaTimeFix(cxFloat dt);
    cxInt repeat;
public:
    cxAction *SetID(cxULong aid);
    cxULong ID() const;
    
    cxAction *SetRepeat(cxInt v);
    
    cxTimingFunc Timing() const;
    cxAction *SetTiming(cxTimingFunc f);
    
    cxAction *SetTime(cxFloat v);
    const cxFloat Time() const;
    const cxFloat Elapsed() const;
    
    cxBool IsPause() const;
    
    cxAction *SetSpeed(cxFloat v);
    cxFloat Speed() const;
    
    cxAction *SetView(cxView *view);
    cxView *View();
public:
    cxEvent<cxAction> onInit;
    cxEvent<cxAction> onStop;
    cxEvent<cxAction> onExit;
public:
    cxFloat Progress() const;
    void SetExit(cxBool v);
    void Reset();
    void Pause();
    void Resume();
    void Stop();
    cxAction *AttachTo(cxView *pview);
    virtual cxAction *Clone();
    virtual cxAction *Reverse();
};

CX_CPP_END

#endif


