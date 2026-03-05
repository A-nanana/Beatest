//-----------------------------
// @name   Vector3.h
// @brief  3次元ベクトル クラスの宣言部
// @auther A.namami
// @date   2026/3/2 新規作成
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once
#include "Vector2.h"
class Vector3D
{
public:
	float x_;
	float y_;
	float z_;
//  コンストラクタ
	Vector3D(float x, float y, float z) :x_(x), y_(y), z_(z) {};
	Vector3D() :x_(0.0f), y_(0.0f), z_(0.0f) {};
//  セッター
	void Set(const Vector2D& other);
//  差
	Vector3D Sub(const Vector3D& other);
	Vector3D Sub(const Vector2D& other);

//  外積算出
	Vector3D Cross(const Vector3D& other);
};

