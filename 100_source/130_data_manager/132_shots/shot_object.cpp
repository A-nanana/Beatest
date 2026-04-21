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
#include "../131_character/player_object.h"
#include "../../110_drawing_tools/camera.h"
#include "../../110_drawing_tools/defining.h"
#include "../133_music/music_manager.h"

ShotObject::ShotObject(const char* graph_, float x, float y, float speed, float angle, Vector2D target, int type)
	:used_(true),target_(target), type_(type), ObjectCommon(graph_, x, y) {
	
	
	speed_size_ = speed;
	SetRotate(angle);
	hit_use_ = true;
	GraphNode::Load();
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



void ShotObject::Load()
{
}

//更新
void ShotObject::Update(float delta_time) {
	
	Vector2D speed_; //速度.

	//今の位置がターゲット位置より奥か
	if ((target_.x_ - world_position_.x_ < NULL) && (target_.y_ - world_position_.y_ < NULL)) {
	}
	else if(type_ != system_set::k_enemy_all_renge) //全体に撒くものではないか
	{

	}


	// 速度変更

	speed_.x_ = cosf(rotate_) * speed_size_;
	speed_.y_ = sin(rotate_) * speed_size_;
	

	// 移動
	SetPosition(position_.x_ + speed_.x_, position_.y_ + speed_.y_);
	ObjectCommon::SetWorldPosition();
	

}

void ShotObject::Release()
{

}

LongShot::LongShot(const char* graph_, float x, float y, float keep, float angle, Vector2D target, int type)
	:ShotObject(graph_, x, y, keep, angle, target, type)
{
	pre_count_ = NULL;
	inner_count_ = keep;
	
	SetAngle(target_.x_, target_.y_);

	
	extender_ = size_x_ / window_setting::length;
	
}

void LongShot::Update(float delta_time)
{
	//カウント減らす
	inner_count_ -= delta_time;
	//カウントが切れているか
	if (inner_count_ < NULL) {
		used_ = false;
	}
	ObjectCommon::SetWorldPosition();

}

void LongShot::Load()
{
	size_x_ = window_setting::length;
	SetHitSize(size_x_, size_y_ * window_setting::graph_extender_);
}

void LongShot::Draw(int screen_handle, Camera* camera)
{
	//カメラ内か
	if (camera->IsDraw(GetWorldPosition(), size_x_, size_y_)) {
		Vector2D draw_pos_;
		draw_pos_.x_ = camera->DrawPositionX(world_position_.x_) ;
		draw_pos_.y_ = camera->DrawPositionY(world_position_.y_) - size_y_ / 2;
		DrawRotaGraph3(draw_pos_.x_, draw_pos_.y_, NULL, size_y_ / 2,extender_,window_setting::graph_extender_
			, rotate_, graph_handle_, TRUE);
		DrawLine(draw_pos_.x_, draw_pos_.y_, target_.x_,target_.y_, GetColor(255,0,255));
	}
}

void LongShot::Release()
{
}
