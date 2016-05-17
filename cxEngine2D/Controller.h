//
//  Controller.h
//  cxEngineTest
//
//  Created by xuhua on 5/16/16.
//  Copyright © 2016 xuhua. All rights reserved.
//

#ifndef cxEngineTest_Controller_h
#define cxEngineTest_Controller_h

#include <core/cxHash.h>
#include <engine/cxAtlas.h>

CX_CPP_BEGIN

#define AT_LEFT(_src_,_dst_)    (_dst_.x == _src_.x-1 && _dst_.y == _src_.y)

#define AT_RIGHT(_src_,_dst_)   (_dst_.x == _src_.x+1 && _dst_.y == _src_.y)

#define AT_TOP(_src_,_dst_)     (_dst_.x == _src_.x && _dst_.y == _src_.y+1)

#define AT_BOTTOM(_src_,_dst_)  (_dst_.x == _src_.x && _dst_.y == _src_.y-1)


class Controller;
class CardItem : public cxSprite
{
public:
    CX_DECLARE(CardItem);
protected:
    explicit CardItem();
    virtual ~CardItem();
private:
    Controller *controller;
    cxUInt type;
    cxPoint2I idx;
public:
    //丢弃
    void Drop();
    //当前所在的位置
    cxPoint2I Index() const;
    void SetIdx(const cxPoint2I &i);
    //两个item是否相等，相等意味着可合成
    virtual cxBool IsEqu(const CardItem *item);
public:
    static CardItem *Create(Controller *c,const cxPoint2I &idx);
};

class Controller : public cxView
{
public:
    CX_DECLARE(Controller);
protected:
    explicit Controller();
    virtual ~Controller();
private:
    cxHash *items;
    cxSize2F itemSize;
    cxInt col;
    cxInt row;
    cxPoint2I srcIdx;//选中的key位置
    cxPoint2I dstIdx;//目标位置
    //临时保存的坐标，当没有可消除的块时交换显示
    cxPoint2I srcTmp;
    cxPoint2I dstTmp;
protected:
    cxBool OnDispatch(const cxengine::cxTouchable *e);
public:
    //计算idx位置处左右上下相等的元素数量，不包括idx
    cxBox4I Compute(const cxPoint2I &idx);
    //丢弃idx位置的view
    CardItem *DropView(const cxPoint2I &idx);
    cxMoveTo *SwapView(const cxPoint2I &src,const cxPoint2I &dst);
    void Reset();
    //是否可以从src移动到dst
    cxBool IsMoveTo(const cxPoint2I &src,const cxPoint2I &dst);
    cxBool IsValidIdx(const cxPoint2I &idx);
    CardItem *ToView(const cxPoint2I &idx);
    cxBool HasView(const cxPoint2I &idx);
    void SetView(const cxPoint2I &idx,CardItem *pview);
    cxPoint2F ToPos(const cxPoint2I &idx);
    cxPoint2I ToIdx(const cxPoint2F &pos);
    cxPoint2I ToIdx(cxInt key);
    cxInt ToKey(const cxPoint2I &idx);
    cxInt ToKey(const cxPoint2F &pos);
public:
    const cxSize2F ItemSize() const;
    void Init();
    static Controller *Create(cxInt c,cxInt r);
public:
    //计算是否可交换,idx为选中的坐标
    virtual cxBool IsSwap(const cxPoint2I &idx);
    //可交换
    virtual cxBool OnSwap(const cxPoint2I &src,const cxPoint2I &dst);
    //进入战斗
    virtual cxBool OnFight(const cxPoint2I &src);
};

CX_CPP_END

#endif


