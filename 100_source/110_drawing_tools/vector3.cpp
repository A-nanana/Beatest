//-----------------------------
// @name   Vector3.cpp
// @brief  3次元ベクトル クラス
// @auther A.namami
// @date   2026/3/2 新規作成
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "vector3.h"
//  セッター
void Vector3D::Set(const Vector2D& other)
{
    x_ = other.x_;
    y_ = other.y_;
}
void Vector3D::Set(const float x, const float y)
{
    x_ = x;
    y_ = y;
    z_ = 0.0f;
}
//  差
Vector3D Vector3D::Sub(const Vector3D& other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    z_ -= other.z_;
    return {x_,y_,z_};
}

Vector3D Vector3D::Sub(const Vector2D& other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    return { x_,y_,z_ };
}
//  外積算出
Vector3D Vector3D::Cross(const Vector3D& other)
{
    x_ = y_ * other.z_ - z_ * other.y_;
    y_ = z_ * other.x_ - x_ * other.z_;
    z_ = x_ * other.y_ - y_ * other.x_;

    return {x_,y_,z_};
}
