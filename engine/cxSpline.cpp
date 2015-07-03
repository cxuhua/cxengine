//
//  cxSpline.cpp
//  cxEngineCore
//
//  Created by xuhua on 7/3/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#include "cxView.h"
#include "cxSpline.h"

CX_CPP_BEGIN

CX_IMPLEMENT(cxSpline);

cxSpline::cxSpline()
{
    angle = INFINITY;
    tension = 0;
}

cxSpline::~cxSpline()
{
    
}

const cxPoint2F &cxSpline::at(cxInt idx)
{
    idx = CX_MIN(points.Size() - 1, CX_MAX(idx, 0));
    return points.At(idx);
}

void cxSpline::OnInit()
{
    cxFloat num = points.Size();
    if(num < 2){
        SetExit(true);
        return;
    }
    delta = 1.0f/((cxFloat)num - 1.0f);
    prev = View()->Position();
    angle = INFINITY;
}

void cxSpline::OnAngle()
{
    onAngle.Fire(this);
}

void cxSpline::OnStep(cxFloat dt)
{
    cxFloat pt = Progress();
    cxInt idx = 0;
    cxFloat lt = 0;
    if (pt >= 1.0f){
        idx = points.Size() - 1;
        lt = 1.0f;
    }else{
        idx = pt / delta;
        lt = (pt - delta * (cxFloat)idx)/delta;
    }
    const cxPoint2F &p0 = at(idx - 1);
    const cxPoint2F &p1 = at(idx + 0);
    const cxPoint2F &p2 = at(idx + 1);
    const cxPoint2F &p3 = at(idx + 2);
    cxPoint2F npos = cxCardinalSplineAt(p0, p1, p2, p3, this->tension, lt);
    cxPoint2F diff = npos - prev;
    cxPoint2F cpos = View()->Position();
    npos = cpos + diff;
    prev = npos;
    cxFloat tmp = diff.Angle();
    if(angle != tmp){
        angle = tmp;
        OnAngle();
    }
    View()->SetPosition(npos);
}

cxAction *cxSpline::Reverse()
{
    cxSpline *rv = cxSpline::Create();
    for(cxInt i=points.Size()-1; i >= 0;i--){
        rv->points.Append(points.At(i));
    }
    rv->SetTime(Time());
    return rv;
}

cxAction *cxSpline::Clone()
{
    cxSpline *rv = cxSpline::Create();
    for(cxInt i=0; i < points.Size();i++){
        rv->points.Append(points.At(i));
    }
    rv->SetTime(Time());
    return rv;
}

cxFloat cxSpline::Angle()
{
    return angle;
}

void cxSpline::Append(const cxPoint2F &v)
{
    points.Append(v);
}

void cxSpline::Clear()
{
    points.Clear();
}

CX_CPP_END
