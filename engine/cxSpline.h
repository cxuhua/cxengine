//
//  cxSpline.h
//  cxEngineCore
//
//  Created by xuhua on 7/3/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#ifndef cxEngineCore_cxSpline_h
#define cxEngineCore_cxSpline_h

#include <math/cxPoint2F.h>
#include "cxAction.h"

CX_CPP_BEGIN

class cxSpline : public cxAction
{
public:
    CX_DECLARE(cxSpline);
protected:
    explicit cxSpline();
    virtual ~cxSpline();
    void OnStep(cxFloat dt);
    void OnInit();
    virtual void OnAngle();
private:
    cxPoint2FArray points;
    cxPoint2F prev;
    const cxPoint2F &at(cxInt idx);
    cxFloat delta;
    cxFloat tension;
    cxFloat angle;
public:
    void Append(const cxPoint2F &v);
    void Clear();
    cxFloat Angle();
    cxEvent<cxSpline> onAngle;
    cxAction *Reverse();
    cxAction *Clone();
};

CX_CPP_END

#endif

