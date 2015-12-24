//
//  DB.cpp
//  card
//
//  Created by xuhua on 12/14/15.
//  Copyright © 2015 xuhua. All rights reserved.
//

#include <core/cxUtil.h>
#include "DB.h"
#include "Game.h"

CX_CPP_BEGIN

CX_IMPLEMENT(Update)

Update::Update()
{
    key = nullptr;
    dataId = nullptr;
    version = 0;
    time = 0;
}

Update::~Update()
{
    cxObject::release(&key);
    cxObject::release(&dataId);
}

void Update::SetVersion(cxInt v)
{
    version = v;
}

void Update::SetDataId(const cxStr *v)
{
    cxObject::swap(&dataId, v);
}

void Update::SetTime(cxInt64 v)
{
    time = v;
}

cxBool Update::Delete()
{
    cxSqlStmt *stmt = db->Prepare("DELETE FROM updates WHERE Key=?;");
    stmt->Bind(1, key->ToString());
    return stmt->Exec();
}

cxBool Update::Insert()
{
    cxSqlStmt *stmt = db->Prepare("INSERT INTO updates VALUES(?,?,?,?);");
    stmt->Bind(1, key->ToString());
    stmt->Bind(2, version);
    stmt->Bind(3, dataId->ToString());
    stmt->Bind(4, time);
    return stmt->Exec();
}

Update *Update::Create(DB *db,cchars key)
{
    Update *ret = Update::Create();
    ret->db = db;
    ret->key = cxStr::Alloc()->Init(key);
    return ret;
}

CX_IMPLEMENT(Word)

Word::Word()
{
    key = nullptr;
    level = 1;
    ver = 1;
    isbuy = false;
    isuse = true;
    time = 0;
    group = 0;
}

Word::~Word()
{
    cxObject::release(&key);
}

Data *Word::GetData()
{
    return nullptr;
}

Word *Word::Create(DB *db,const cxStr *key)
{
    return Create(db, key->ToString());
}

Word *Word::Create(DB *db,cchars key)
{
    Word *word = Word::Create();
    word->db = db;
    word->key = cxStr::Alloc()->Init(key);
    return word;
}

void Word::SetValue(cxSqlStmt *stmt)
{
    //1 -> key
    level = stmt->ToInt(2);
    ver = stmt->ToInt(3);
    isbuy = stmt->ToBool(4);
    isuse = stmt->ToBool(5);
    time = stmt->ToInt64(6);
    group = stmt->ToInt(7);
    last = stmt->ToInt64(8);
}

cxBool Word::Exists()
{
    CX_ASSERT(cxStr::IsOK(key), "key not set");
    CX_ASSERT(db != nullptr, "db not set");
    cxSqlStmt *stmt = db->Prepare("SELECT Key,Level,Version,IsBuy,IsUse,Time,GroupId,Last FROM words WHERE key=? LIMIT 1");
    stmt->Bind(1, key->ToString());
    if(!stmt->Step()){
        return false;
    }
    SetValue(stmt);
    return true;
}

cxInt64 Word::NextTime()
{
    CX_ASSERT(db != nullptr, "db not set");
    return db->LevelTime(level);
}

cxBool Word::Insert()
{
    CX_ASSERT(cxStr::IsOK(key), "key not set");
    cxSqlStmt *stmt = db->Prepare("INSERT INTO words VALUES(?,?,?,?,?,?,?,?);");
    stmt->Bind(1, key->ToString());
    stmt->Bind(2, group);
    stmt->Bind(3, level);
    stmt->Bind(4, ver);
    stmt->Bind(5, isbuy);
    stmt->Bind(6, isuse);
    stmt->Bind(7, NextTime());
    stmt->Bind(8, db->TimeNow());
    return stmt->Exec();
}

CX_IMPLEMENT(DB);

DB::DB()
{
    LVS[0] = 5 * TIME_MINUTE;
    LVS[1] = 30 * TIME_MINUTE;
    LVS[2] = 12 * TIME_HOUR;
    LVS[3] = 1 * TIME_DAY;
    LVS[4] = 2 * TIME_DAY;
    LVS[5] = 4 * TIME_DAY;
    LVS[6] = 7 * TIME_DAY;
    LVS[7] = 15 * TIME_DAY;
    LVS[8] = 30 * TIME_DAY;
}

DB::~DB()
{
    
}

cxArray *DB::ReviewWords(cxInt count)
{
    cxInt64 now = TimeNow();
    cxArray *ws = cxArray::Create();
    cxSqlStmt *stmt = Prepare("SELECT Key,Level,Version,IsBuy,IsUse,Time,GroupId,Last FROM words "
                              "WHERE IsBuy = 1 AND IsUse = 1 AND Time <= ? LIMIT ?");
    stmt->Bind(1, now);
    stmt->Bind(2, count);
    while(stmt->Step()){
        Word *word = Word::Create(this, stmt->ToString(1));
        word->SetValue(stmt);
        ws->Append(word);
    }
    return ws;
}

const cxStr *DB::GetValue(cchars key)
{
    cxSqlStmt *stmt = Prepare("SELECT Value FROM config WHERE Key='%s';",key);
    if(stmt->Step()){
        return stmt->ToString(1);
    }
    return nullptr;
}

cxBool DB::SetValue(cchars key,const cxStr *value)
{
    cxSqlStmt *stmt = Prepare("UPDATE config SET Value=? WHERE Key='%s';",key);
    stmt->Bind(1, value->ToString());
    return stmt->Exec();
}

cxInt64 DB::TimeNow()
{
    //从网络获得当前时间
    return G()->GetNet()->TimeNow();
}

cxInt64 DB::LevelTime(cxInt level)
{
    cxInt64 now = TimeNow();
    if(level >=1 && level <= 9){
        return now + LVS[level-1];
    }
    return now + (level * 3 + 1) * TIME_DAY;
}

cxInt DB::DataVersion()
{
    return GetValue("DataVersion")->ToInt();
}

cxBool DB::SetDataVersion(cxInt ver)
{
    return SetValue("DataVersion", cxStr::UTF8("%d",ver));
}

cxBool DB::SetBindId(const cxStr *id)
{
    return SetValue("BindId", id);
}

const cxStr *DB::BindId()
{
    return GetValue("BindId");
}

cxBool DB::SetTempId(const cxStr *id)
{
    return SetValue("TempId", id);
}

const cxStr *DB::TempId()
{
    return GetValue("TempId");
}

cxBool DB::Init()
{
    if(!cxSqlite::Init("card.db", false)){
        CX_ERROR("init db error");
        return false;
    }
    Begin();
    if(!ExistTable("config")){
        //创建配置表
        Exec("CREATE TABLE config(Key VARCHAR(32) PRIMARY KEY,Value VARCHAR(128));");
        //词库版本(DataVersion),是否有新的词卡
        Exec("INSERT INTO config VALUES('DataVersion','0');");
        //用户TempId,用户唯一id
        const cxStr *id = cxUtil::Instance()->UUID()->MD5();
        Exec("INSERT INTO config VALUES('TempId','%s');",id->ToString());
    }
    if(!ExistTable("words")){
        //创建词卡表
        Exec("CREATE TABLE words("
             "Key VARCHAR(256) PRIMARY KEY,"//词条主键,按小写方式存储
             "GroupId INT,"                 //分组id
             "Level INT,"                   //等级
             "Version INT,"                 //数据版本,是否更新或者删除词卡数据,由服务器端确定
             "IsBuy INT,"                   //是否已经购买
             "IsUse INT,"                   //是否用于复习
             "Time INT,"                    //下次复习时间
             "Last INT);");                 //最后复习时间
        //创建分类索引
        Exec("CREATE INDEX GroupIndex ON words(GroupId ASC)");
        //创建复习时间索引
        Exec("CREATE INDEX TimeIndex ON words(Time ASC)");
        //创建是否使用索引
        Exec("CREATE INDEX IsUseIndex ON words(IsUse ASC)");
    }
    if(!ExistTable("updates")){
        //将要更新的word列表,更新数据后删除
        Exec("CREATE TABLE updates(Key VARCHAR(32) PRIMARY KEY,Version INT, DataId VARCHAR(32),Time INT);");
    }
    Commit();
    return true;
}

CX_CPP_END

