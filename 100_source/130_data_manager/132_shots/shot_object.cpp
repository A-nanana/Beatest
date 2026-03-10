//-----------------------------
// @name   shot_object.cpp
// @brief  弾オブジェクト クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <iostream>
#include "shot_object.h"
#include "..\131_character\player_object.h"
#include "..\..\110_drawing_tools\defining.h"
#include "..\133_music\music_manager.h"

ShotObject::ShotObject(const int graph_handle, float x, float y, float speed, float angle, Vector2D target)
	:used_(true),target_(target), ObjectCommon(graph_handle, x, y) {
	
	speed_.x_ = speed * cos(angle);
	speed_.y_ = speed * sin(angle);
	SetRotate(angle);
	hit_use_ = true;
}

ShotObject::~ShotObject()
{
	
}

//端っこ返す系
int ShotObject::XLeft(void)
{
	return world_position_.x_;
}

int ShotObject::XRight(void)
{
	return world_position_.x_ + size_x_;
}

int ShotObject::YTop(void)
{
	return  world_position_.y_;
}

int ShotObject::YBottom(void)
{
	return  world_position_.y_ + size_y_;
}

//作成
int ShotObject::Shoot(int _speed, double angle)
{
	{
		//未使用品なら使用.
		if (used_ == true) return 0;


		//セット処理.
		
		SetPosition(NULL, NULL);
		speed_.x_ = _speed * cos(angle);
		speed_.y_ = _speed * sin(angle);
		rotate_ = angle;
		used_ = true;

		return 1;
	}
}


//更新
void ShotObject::Update(float delta_time) {
	
	//今の位置がターゲット位置より奥か
	if ((target_.x_ - world_position_.x_ < system_set::shot_speed_def) && (target_.y_ - world_position_.y_ < system_set::shot_speed_def)) {
	}
	else {
		SetAngle(target_.x_, target_.y_);

	}


	// 速度変更
	float last_length = speed_.Length();

	speed_.x_ = cosf(rotate_) * last_length;
	speed_.y_ = sin(rotate_) * last_length;
	

	// 移動
	SetPosition(position_.x_ + speed_.x_, position_.y_ + speed_.y_);
	ObjectCommon::SetWorldPosition();
	

}

void ShotObject::Release()
{

}


