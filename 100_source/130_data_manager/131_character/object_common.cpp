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
#include "..\..\110_drawing_tools\defining.h"

ObjectCommon::ObjectCommon(const char* name, float x, float y, float hit_size_x, float hit_size_y)
    :GraphNode(name, x, y) {

    rotate_ = 0.0f;
    hit_size_.Set(hit_size_x, hit_size_y);
    hit_use_ = true;
    distance_ = window_setting::null_param;

}

ObjectCommon::ObjectCommon(const char* name, float x, float y, float extender, float hit_size_x, float hit_size_y)
    :GraphNode(name, x, y,extender) {

    rotate_ = 0.0f;
    hit_size_.Set(hit_size_x, hit_size_y);
    hit_use_ = true;
    distance_ = window_setting::null_param;

}
ObjectCommon::ObjectCommon(const int graph_handle, float x, float y)
    :GraphNode(graph_handle, x, y){
    
    GetGraphSize(graph_handle_, &size_x_, &size_y_);
    size_x_ *= window_setting::graph_extender_;
    size_y_ *= window_setting::graph_extender_;
    hit_size_.Set(size_x_, size_y_);

    rotate_ = 0.0f;
    hit_use_ = true;
    distance_= window_setting::null_param;

}

void ObjectCommon::SetRotate(float angle)
{
    rotate_ = angle;
}

void ObjectCommon::SetHitSize(float x, float y)
{
    hit_size_.x_ = x;
    hit_size_.y_ = y;
}

void ObjectCommon::SetPosition(const float& x, const float& y)
{
    Node::SetPosition(x, y);
    
}

void ObjectCommon::SetWorldPosition()
{
    Node::SetWorldPosition();
    //頂点(回転の中心と図形の中心を合わせる)設定
    point_[0].Set(-hit_size_.x_ / 2, -hit_size_.y_ / 2);
    point_[1].Set(+hit_size_.x_ / 2, -hit_size_.y_ / 2);
    point_[2].Set(+hit_size_.x_ / 2, +hit_size_.y_ / 2);
    point_[3].Set(-hit_size_.x_ / 2, +hit_size_.y_ / 2);
    //回転行列で変換
    Matrix2 mat;//変換用マトリクス
    mat.SetMatrixRotate(rotate_);
    for (int i = 0; i < hit_set::squair_point; i++) {
        point_[i].ChangeForMatrix(mat);
        point_[i].Add(GetWorldPosition().x_ + size_x_ /2, GetWorldPosition().y_ + size_y_ /2); //ワールド座標に変換
    }

    //ベクトル計算
    for (int i = 0; i < hit_set::squair_point; i++) {
        vectol_[i].Set(point_[(i + 1) % hit_set::squair_point]);
        vectol_[i].Sub(point_[i]);
    }
}

void ObjectCommon::SetAngle(float to_x, float to_y)
{

    //算出用座標
    float dy = to_y  - world_position_.y_;
    float dx = to_x  - world_position_.x_;
    //算出用角度
    float angle;
    //0がらみの安定化
    if (AlmostEqual(dx, 0) && AlmostEqual(dy, 0)) {
        angle = system_set::repair_rad;
    }
    else {
        angle = atan2(dy, dx);
    }

    rotate_ = angle;
}

const float ObjectCommon::GetAllLength()
{
    //返り値
    Vector2D returner(GetWorldPosition());
    returner.Add(size_x_, size_y_);
    return returner.Length_2zyou();
}

void ObjectCommon::Load()
{
    GraphNode::Load();
    //当たり判定を使うか
    if (!hit_use_) return;
    //当たり判定の作成がされているか
    if (hit_size_.x_ > NULL || hit_size_.y_ > NULL) {
        return;
    }
    hit_size_.Set(size_x_, size_y_);
}

bool ObjectCommon::HitCheckToPoint(Vector2D* other, int* dist_)
{
    bool returner = true;//当たり判定の返り値
    for (int i = 0; i < hit_set::squair_point; i++) {
        
      
        //頂点へのベクトル
        Vector2D to_point_(other->x_ - point_[i].x_, other->y_ - point_[i].y_);

        //計算結果用
        int result_ = vectol_[i].x_ * to_point_.y_ - vectol_[i].y_ * to_point_.x_;
        int length = (result_ * result_) / vectol_[i].Length_2zyou(); //外積の絶対値が2ベクトルが作る平行四辺形であることを利用
        //外積が0未満(ベクトルの右側)なら当たり判定の外
        if (result_ < 0) {
            returner = false;
        }

        //距離
        int naiseki = vectol_[i].x_ * to_point_.x_ + vectol_[i].y_ * to_point_.y_;//角が近いかの判定用

        //斜め位置の場合は角からの距離をとる
        //内積が負の値か範囲内最大距離の内積より大きい
        if (naiseki< 0.0f || naiseki > vectol_[i].Length_2zyou()) {
            length = to_point_.Length_2zyou();
        }

        //近い距離かつ外側であるか
        if ( *dist_ > length || *dist_< 0) {
            *dist_ = length;
        }

    }
    return returner;
}

bool ObjectCommon::HitCheckToBox(ObjectCommon* other )
{
    distance_ = -1;
    bool returner = false;//当たり判定の返り値

    //頂点分繰り返す
    for (int i = 0; i < hit_set::squair_point; i++) {
        //当たり判定があるか
        if (HitCheckToPoint(&other->point_[i],&distance_)) {
            returner = true;
        }
    }
   
    return returner;
}

bool ObjectCommon::IsHit(ObjectCommon* other)
{
    //当たり判定を扱えるか
    if (hit_use_ && other->IsObject()) {

        return HitCheckToBox(other);
        
    }
    return false;
    
}
