//
//  cxStr.h
//  cxEngineCore
//
//  Created by xuhua on 5/24/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#ifndef __cxEngineCore__cxStr__
#define __cxEngineCore__cxStr__

#include <string>
#include "cxObject.h"

CX_CPP_BEGIN

class cxStr : public cxObject,private std::string
{
public:
    CX_DECLARE(cxStr);
protected:
    explicit cxStr();
    virtual ~cxStr();
public:
    static cxStr *UTF8(cchars fmt,...);
    static cxBool IsOK(const cxStr *str);
    static cxBool IsOK(cchars str);
    static cxBool IsEqu(cchars s1,cchars s2);
    
    cxStr *Init(cxInt size,char c=0);
    cxStr *Init(cchars str);
    cxStr *Init(cxAny data,cxInt size);

    void Print() const;
    
    cxUInt32 HashValue() const;
    
    cxBool IsEmpty() const;
    cxInt Size() const;
    char At(cxInt n) const;
    cchars Data() const;
    chars Buffer() const;
    
    const cxStr *TeaEncode(const cxStr *key) const;
    const cxStr *TeaDecode(const cxStr *key) const;
    
    const cxStr *LzmaCompress() const;
    const cxStr *LzmaUncompress() const;
    
    const cxStr *MD5();
    
    cxStr *AppFmt(cchars fmt,va_list ap);
    cxStr *AppFmt(cchars fmt,...);
    cxStr *Append(cchars data);
    cxStr *Append(cchars data,cxInt n);
    cxStr *Append(const cxStr *str);
    
    cxStr *InsFmt(cxInt pos,cchars fmt,va_list ap);
    cxStr *InsFmt(cxInt pos,cchars fmt,...);
    cxStr *Insert(cxInt pos,cchars data);
    cxStr *Insert(cxInt pos,cchars data,cxInt n);
    cxStr *Insert(cxInt pos,const cxStr *str);
    
    cxStr *Clear();
    cxStr *Erase(cxInt p,cxInt n);
    cxStr *Erase(cxInt p);
    
    cxBool IsEqu(const cxStr *str) const;
    cxBool IsCaseEqu(const cxStr *str) const;
    cxBool IsEqu(cchars str) const;
    cxBool IsCaseEqu(cchars str) const;
    cxBool IsEqu(cchars d,cxInt l) const;
    
    cxBool HasPrefix(const cxStr *str) const;
    cxBool HasPrefix(cchars str) const;
    cxBool HasSuffix(const cxStr *str) const;
    cxBool HasSuffix(cchars str) const;
};

CX_CPP_END

#endif /* defined(__cxEngineCore__cxStr__) */
