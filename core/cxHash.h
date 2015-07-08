//
//  cxHash.h
//  cxEngineCore
//
//  Created by xuhua on 5/27/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#ifndef cxEngineCore_cxHash_h
#define cxEngineCore_cxHash_h

#include <unordered_map>
#include "cxObject.h"
#include "cxStr.h"

CX_CPP_BEGIN

#define CX_HASH_MAX_KEY  64

struct cxHashKey
{
    cxInt length;
    cxByte data[CX_HASH_MAX_KEY + 1];
    cxHashKey();
    cxHashKey(cxInt key);
    cxHashKey(cchars key);
    cxHashKey(cxULong key);
    cxHashKey(const cxStr *key);
    static cxHashKey Format(cchars fmt,...);
};

struct cxHasher
{
    size_t operator()(const cxHashKey& k) const;
    bool operator()(const cxHashKey& lhs, const cxHashKey& rhs) const;
};

typedef std::unordered_map<cxHashKey, cxObject *,cxHasher,cxHasher> cxHashMap;

class cxArray;
class cxHash : public cxObject
{
public:
    CX_DECLARE(cxHash);
protected:
    explicit cxHash();
    virtual ~cxHash();
private:
    cxHashMap mh;
public:
    typedef cxHashMap::iterator Iter;
    Iter Begin();
    Iter End();
    Iter Remove(Iter &iter);
public:
    cxInt Size() const;
    cxBool IsEmpty() const;
    cxHash *Clear();
    void Del(const cxHashKey &key);
    cxHash *Set(const cxHashKey &key,cxObject *obj);
    cxBool Has(const cxHashKey &key);
    cxObject *Get(const cxHashKey &key);
    template<class T>
    T *At(const cxHashKey &key);
    cxArray *ToArray();
};

template<class T>
CX_INLINE T *cxHash::At(const cxHashKey &key)
{
    return static_cast<T *>(Get(key));
}

CX_CPP_END

#endif


