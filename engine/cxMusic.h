//
//  cxMusic.h
//  cxEngineCore
//
//  Created by xuhua on 7/29/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#ifndef cxEngineCore_cxMusic_h
#define cxEngineCore_cxMusic_h

#include "cxOpenAL.h"
#include "cxAction.h"

CX_CPP_BEGIN

class cxMusic : public cxAction
{
public:
    CX_DECLARE(cxMusic);
protected:
    explicit cxMusic();
    virtual ~cxMusic();
protected:
    void OnInit();
    void OnExit();
    void OnStep(cxFloat dt);
    void OnReset();
private:
    cxBool isfollow;
    void updateForFollowView();
    cxALSource *source;
public:
    cxEvent<cxMusic, cxView *> onFollow;
public:
    cxMusic *BindFollow(cxView *pview);
    cxALSource *GetSource();
    cxBool Init(cchars file,cchars key=nullptr);
    cxBool Init(const cxStr *data,cxALBuffer::DataType type);
public:
    static cxMusic *Create(cchars file,cchars key=nullptr);
    static cxMusic *Create(const cxStr *data,cxALBuffer::DataType type);
};

CX_CPP_END

#endif


