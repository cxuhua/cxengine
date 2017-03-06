//
//  IOSEngine.cpp
//  cxEngine2D
//
//  Created by xuhua on 6/17/15.
//  Copyright (c) 2015 xuhua. All rights reserved.
//

#include <engine/cxSprite.h>
#include <engine/cxTexture.h>
#include <engine/cxAtlas.h>
#include <engine/cxLabel.h>
#include <core/cxUtil.h>
#include <engine/cxMove.h>
#include <engine/cxRotate.h>
#include <engine/cxScale.h>
#include <engine/cxButton.h>
#include <engine/cxContainer.h>
#include <engine/cxEmitter.h>
#include <engine/cxTimeLine.h>
#include <engine/cxTimer.h>
#include <engine/cxAnimate.h>
#include <engine/cxTcp.h>
#include <engine/cxHttp.h>
#include <engine/cxSpline.h>
#include <engine/cxFollow.h>
#include <engine/cxBezier.h>
#include <engine/cxFade.h>
#include <engine/cxTint.h>
#include <engine/cxSequence.h>
#include <engine/cxJump.h>
#include <engine/cxResize.h>
#include <engine/cxProgress.h>
#include <core/cxNumber.h>
#include <engine/cxTable.h>
#include <engine/cxPath.h>
#include <engine/cxTriangles.h>
#include <engine/cxMusic.h>
#include <engine/cxMultiple.h>
#include "Game.h"
#include <core/cxKDTree.h>
#include <engine/cxScript.h>

#include <engine/cxFrames.h>
#include <engine/cxActionGroup.h>
#include <engine/cxLoading.h>
#include <engine/cxRand.h>

#include <ext/pb_encode.h>
#include <ext/pb_decode.h>


CX_CPP_BEGIN

CX_IMPLEMENT(Game);

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::test()
{
    
}

void Game::OnMain()
{
    SetPlanSize(cxSize2F(2048, 1536));
    
    cxSprite *sp = cxSprite::Create("t.png");
    sp->SetSize(400);
    Window()->Append(sp);
    //加载纹理
    LoadTexture("jl.lqt");
    //加载帧序列
    LoadFrames("frames.csv");
    //加载动作组
    LoadActions("actions.csv");
    //获取法师帧序列
    const cxFrames *fs = GetFrames("Mage");
    //获取法师的动作列表
    const cxActionGroup *ag = GetActions("Mage");
    //获得move动作
    const cxActionAttr *move = ag->Action("move");
    //创建动画
    cxAnimate *animate = fs->Animate();
    animate->onFrame+=[](cxAnimate *pav,cxInt frame){
        
    };
    animate->onKey+=[](cxAnimate *pav,cxInt key){
        CX_LOGGER("%d",key);
    };
    animate->SetAction(move, 1);
    //创建载体
    cxTriangles *atlas = cxTriangles::Create();
    atlas->SetFlipX(true);
    atlas->SetSize(400);
    atlas->Append(animate);//加入动画
    Window()->Append(atlas);
}

CX_CPP_END

