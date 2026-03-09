//-----------------------------
// @name   object_common.cpp
// @brief  オブジェクト共通 クラス
// @auther A.namami
// @date   2026/3/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <iostream>
#include "..\..\110_drawing_tools\tool.h"
#include "object_common.h"

ObjectCommon::ObjectCommon(const char* name, float x, float y, float hit_size_x, float hit_size_y)
    :GraphNode(name, x, y) {

    rotate_ = 0.0f;

    hit_use_ = true;
}

ObjectCommon::ObjectCommon(const int graph_handle, float x, float y)
    :GraphNode(graph_handle, x, y){
    
    GetGraphSize(graph_handle_, &size_x_, &size_y_);

    rotate_ = 0.0f;
    hit_use_ = true;

}

void ObjectCommon::SetRotate(float angle)
{
    rotate_ = angle;
}

void ObjectCommon::SetHitSize(float x, float y)
{
    size_x_ = x;
    size_y_ = y;
}

void ObjectCommon::SetPosition(const float& x, const float& y)
{
    Node::SetPosition(x, y);
    
}

void ObjectCommon::SetWorldPosition()
{
    Node::SetWorldPosition();
    //頂点(回転の中心と図形の中心を合わせる)設定
    point_[0].Set(-size_x_ / 2, -size_y_ / 2);
    point_[1].Set(+size_x_ / 2, -size_y_ / 2);
    point_[2].Set(+size_x_ / 2, +size_y_ / 2);
    point_[3].Set(-size_x_ / 2, +size_y_ / 2);
    //回転行列で変換
    Matrix2 mat;//変換用マトリクス
    mat.SetMatrixRotate(rotate_);
    for (int i = 0; i < hit_set::squair_point; i++) {
        point_[i].ChangeForMatrix(mat);
        point_[i].Add(GetWorldPosition()); //ワールド座標に変換
    }

    //ベクトル計算
    for (int i = 0; i < hit_set::squair_point; i++) {
        vectol_[i].Set(point_[(i + 1) % hit_set::squair_point]);
        vectol_[i].Sub(point_[i]);
    }
}

bool ObjectCommon::HitCheckToPoint(Vector2D* other)
{
    for (int i = 0; i < hit_set::squair_point; i++) {

        //頂点へのベクトル
        Vector2D to_point_(other->x_ - point_[i].x_, other->y_ - point_[i].y_);
        //計算結果用
        float result_ = vectol_[i].x_ * to_point_.y_ - vectol_[i].y_ * to_point_.x_;

        //外積が0未満(ベクトルの右側)なら当たり判定の外
        if (result_ < 0) {
            return false;
        }




    }
    return true;
}

bool ObjectCommon::HitCheckToBox(ObjectCommon* other)
{
    for (int i = 0; i < hit_set::squair_point; i++) {
        if (HitCheckToPoint(&other->point_[i])) {
            return true;
        }
    }
    return false;
}

bool ObjectCommon::IsHit(ObjectCommon* other)
{
    //当たり判定を扱えるか
    if (hit_use_ && other->IsObject()) {
        DrawLine(point_[0].x_, point_[0].y_, point_[2].x_, point_[2].y_, ChangeColorToCode(255, 255, 255), FALSE);

        return HitCheckToBox(other);
        


    }
    return false;
    
}
