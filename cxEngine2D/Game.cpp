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
#include <engine/cxTable.h>
#include <engine/cxPath.h>
#include <engine/cxTriangles.h>
#include <engine/cxMusic.h>
#include "Game.h"
#include <core/cxKDTree.h>
#include "Sea.h"
#include <engine/cxBox2D.h>
#include <engine/cxSpine.h>
#include <core/cxSqlite.h>

CX_CPP_BEGIN

CX_IMPLEMENT(Game);


Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::OnMain()
{
    SetPlanSize(cxSize2F(2048, 1536));
    
    cxSqlite *db = cxSqlite::Create("test.db",false);
    cxBool ret =  db->Begin();
    ret = db->Exec("CREATE TABLE IF NOT EXISTS Test (Id INTEGER PRIMARY KEY AUTOINCREMENT,Name VARCHAR(20),Path VARCHAR(20));");
    
    for(cxInt i=0;i<10;i++){
        cxSqlStmt *stmt = db->Prepare("INSERT INTO Test(Name,Path)VALUES(?,?)");
        ret = stmt->Bind(1, "1");
        ret = stmt->Bind(2, "2");
        ret = stmt->Exec();
    }
    ret = db->Commit();
}

CX_CPP_END

