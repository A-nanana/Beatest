//-----------------------------
// @name   object_common.cpp
// @brief  オブジェクト共通 クラス
// @auther A.namami
// @date   2026/3/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "object_common.h"

ObjectCommon::ObjectCommon(const int graph_handle, float x, float y)
    :GraphNode(graph_handle, x, y), hit_box_(x, y, NULL, NULL) {
    
    GetGraphSize(graph_handle_, &size_x_, &size_y_);

    hit_box_.SetToSize(size_x_, size_y_);

    hit_use_ = true;
}

void ObjectCommon::SetRotate(float angle)
{
    hit_box_.lotate_rad_ = angle;
    rotate_ = angle;
}

void ObjectCommon::SetHitSize(float x, float y)
{
    hit_box_.SetToSize(x, y);
}

bool ObjectCommon::IsHit(ObjectCommon* other)
{
    //当たり判定を扱えるか
    if (hit_use_ && other->IsObject()) {
        return hit_box_.HitCheckToBox(other->GetHitBox());

    }
    return false;
}
