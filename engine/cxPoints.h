//
//  cxPoints.h
//  cxEngineCore
//  points move
//  Created by xuhua on 26/03/2017.
//  Copyright © 2017 xuhua. All rights reserved.
//

#ifndef cxEngineCore_cxPoints_h
#define cxEngineCore_cxPoints_h

#include <math/cxPoint2I.h>
#include "cxAction.h"

CX_CPP_BEGIN

class cxPoints : public cxAction
{
public:
    CX_DECLARE(cxPoints);
protected:
    explicit cxPoints();
    virtual ~cxPoints();
protected:
    void OnStep(cxFloat dt);
    void OnInit();
    virtual cxPoint2F ToPos(const cxPoint2I &v);
    virtual cxPoint2I ToIdx(const cxPoint2F &v);
    virtual cxBool OnArrive(const cxInt &v);
private:
    cxPoint2IArray ps;
    cxFloat speed;
    cxInt idx;
    cxPoint2F np;
    cxPoint2F angle;
    cxBool next(cxInt i);
    cxBool isArrive(cxView *v,const cxPoint2F &p);
public:
    void SetPoints(const cxPoint2IArray &v);
    void SetSpeed(const cxFloat &v);
};

CX_CPP_END

#endif


