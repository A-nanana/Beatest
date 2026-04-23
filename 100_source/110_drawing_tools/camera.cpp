//-----------------------------
// @name   camera.cpp
// @brief  カメラ クラス
// @auther A.namami
// @date   2026/3/3  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "camera.h"
#include "..\130_data_manager\131_character\player_object.h"
#include "defining.h"
Camera::Camera(float x, float y) :position_(x, y)
{
	size_.x_ = window_setting::size_x;
	size_.y_ = window_setting::size_y;
	lock_ = false;
}
Camera::Camera():position_(NULL,NULL)
{
	size_.x_ = window_setting::size_x;
	size_.y_ = window_setting::size_y;
	lock_ = true;
}
void Camera::Init() {
	player_pos_.x_ = PlayerObject::GetInstance()->GetWorldPosition().x_ - position_.x_;
	player_pos_.y_ = PlayerObject::GetInstance()->GetWorldPosition().y_ - position_.y_;
}
void Camera::Update()
{
	if (lock_) {
		return;
	}
	position_.Set(PlayerObject::GetInstance()->GetWorldPosition());
	position_.x_ -= player_pos_.x_;
	position_.y_ -= player_pos_.y_;


}

bool Camera::IsDraw(Vector2D world_pos, int size_x, int size_y)
{
	//描画領域の外にあるなら描画しないとする
	if ((position_.x_ - size_x> world_pos.x_) || ((position_.x_ + size_.x_+ size_x) < world_pos.x_)
		|| (position_.y_ - size_y > world_pos.y_) || ((position_.y_ + size_.y_ + size_y) < world_pos.y_)) {
		return false;
	}
	return true;
}

bool Camera::IsDraw(Vector2D world_pos)
{
	//描画領域の外にあるなら描画しないとする
	if ((position_.x_ - window_setting::offset_shown > world_pos.x_ ) || ((position_.x_ + size_.x_ + window_setting::offset_shown) < world_pos.x_)
		|| (position_.y_ - window_setting::offset_shown > world_pos.y_) || ((position_.y_ + size_.y_ + window_setting::offset_shown) < world_pos.y_)) {
		return false;
	}
	return true;
}

Vector2D Camera::DrawPosition(const Vector2D& world_pos)
{
	return {world_pos - position_.x_,world_pos -position_.y_};
}

int Camera::DrawPositionX(float world_pos_x)
{
	return world_pos_x - position_.x_;
}

int Camera::DrawPositionY(float world_pos_y)
{
	return world_pos_y - position_.y_;
}
