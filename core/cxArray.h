//
//  cxArray.h
//  cxEngineCore
//
//  Created by xuhua on 5/23/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#ifndef __cxEngineCore__cxArray__
#define __cxEngineCore__cxArray__

#include <vector>
#include "cxObject.h"

CX_CPP_BEGIN

// >0 desc,<0 asc,=0
typedef cxInt (*cxCmpFunc)(const void *lp, const void *rp);

class cxArray : public cxObject
{
public:
    CX_DECLARE(cxArray);
public:
    typedef std::vector<cxObject *>::iterator FIter;
    typedef std::vector<cxObject *>::reverse_iterator RIter;
protected:
    explicit cxArray();
    virtual ~cxArray();
private:
    std::vector<cxObject *> mv;
public:
    static cxBool IsOK(const cxArray *v);
    RIter RBegin();
    RIter REnd();
    FIter FBegin();
    FIter FEnd();
    FIter Remove(FIter &iter);
    RIter Remove(RIter &iter);
public:
    cxObject **Buffer();
    cxObject *Last() const;
    cxObject *First() const;
    cxObject *At(cxInt idx) const;
    cxBool IsEmpty() const;
    cxInt Size() const;
    cxArray *Swap(cxInt src,cxInt dst);
    cxArray *Replace(cxInt idx,cxObject *obj);
    cxArray *Append(cxObject *obj);
    cxArray *Appends(cxArray *vs);
    cxArray *Remove(cxObject *obj);
    cxArray *Remove(cxInt idx);
    cxArray *Sort(cxCmpFunc func);
    cxArray *Clear();
};

CX_CPP_END
#endif /* defined(__cxEngineCore__cxArray__) */
