//-----------------------------
// @name   shot_object.cpp
// @brief  ?e?I?u?W?F?N?g ?N???X
// @auther A.namami
// @date   2026/3/5  ?V?K??
// @memo   ?G???[?^??????????-1???????
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <iostream>
#include "shot_object.h"
#include "../131_character/player_object.h"
#include "../../110_drawing_tools/camera.h"
#include "../../110_drawing_tools/defining.h"
#include "../133_music/music_manager.h"
#include "../134_other/window_manager.h"

ShotObject::ShotObject(const int graph_handle, float x, float y, float speed, float angle, Vector2D target, int type)
	:used_(true), target_(target), type_(type), ObjectCommon(graph_handle, x, y) {


	speed_size_ = speed;
	SetRotate(angle);
	hit_use_ = true;
	GraphNode::Load();
}

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

//?[????????n
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



//?X?V
void ShotObject::Update(float delta_time) {
	
	Vector2D speed_; //???x.


	// ???x??X

	speed_.x_ = cosf(rotate_) * speed_size_;
	speed_.y_ = sin(rotate_) * speed_size_;
	

	// ???
	SetPosition(position_.x_ + speed_.x_, position_.y_ + speed_.y_);
	ObjectCommon::SetWorldPosition();
	

}

void ShotObject::Release()
{

}

LongShot::LongShot(const int graph_handle, float x, float y, float keep, float angle, Vector2D target, int type)
	:ShotObject(graph_handle, x, y, keep, angle, target, type)
{
	//?J?E???g?Z?b?g
	pre_count_ = MusicManager::GetInstance()->GetMsPerHyousi();
	inner_count_ = keep;
	hit_use_ = false;

	SetAngle(target_.x_, target_.y_);


	extender_ = WindowManager::GetInstance()->GetWindowLength() / size_x_;

	size_x_ = WindowManager::GetInstance()->GetWindowLength();
	SetHitSize(size_x_, size_y_ * window_setting::graph_extender_);
}

LongShot::LongShot(const char* graph_, float x, float y, float keep, float angle, Vector2D target, int type)
	:ShotObject(graph_, x, y, keep, angle, target, type)
{
	pre_count_ = MusicManager::GetInstance()->GetMsPerHyousi();
	inner_count_ = keep;
	hit_use_ = false;
	
	SetAngle(target_.x_, target_.y_);
	
	extender_ = WindowManager::GetInstance()->GetWindowLength() / size_x_;
	size_x_ = WindowManager::GetInstance()->GetWindowLength();
	SetHitSize(size_x_ , size_y_ * window_setting::graph_extender_);
}

void LongShot::SetWorldPosition()
{

	 ObjectCommon::SetWorldPosition();
    //???_(??]????S??}?`????S????????)???
    point_[0].Set(0.0f, -hit_size_.y_ / 2);
    point_[1].Set(+hit_size_.x_ , -hit_size_.y_ / 2);
    point_[2].Set(+hit_size_.x_ , +hit_size_.y_ / 2);
    point_[3].Set(0.0f, +hit_size_.y_ / 2);
    //??]?s?????
    Matrix2 mat;//????p?}?g???N?X
    mat.SetMatrixRotate(rotate_);
    for (int i = 0; i < hit_set::squair_point; i++) {
        point_[i].ChangeForMatrix(mat);
        point_[i].Add(GetWorldPosition().x_ , GetWorldPosition().y_ + hit_size_.y_ / 2.0f); //???[???h???W????
    }

    //?x?N?g???v?Z
    for (int i = 0; i < hit_set::squair_point; i++) {
        vectol_[i].Set(point_[(i + 1) % hit_set::squair_point]);
        vectol_[i].Sub(point_[i]);
    }

}

void LongShot::ChangeUsed()
{
}

void LongShot::Update(float delta_time)
{
	// 予告線カウント
	pre_count_ -= delta_time;
	// 予告中は常に無判定
	if (pre_count_ > 0.0f) {
		hit_use_ = false;
	}
	else {
		// レーザー本体カウント
		inner_count_ -= delta_time;
		hit_use_ = true;
	}
	//?J?E???g?????????
	if (inner_count_ < 0) {
		hit_use_ = false;
		used_ = false;
	}
	SetWorldPosition();

}



void LongShot::Draw(int screen_handle, Camera* camera)
{
	//?J????????
	if (camera->IsDraw(GetWorldPosition(), size_x_, size_y_)) {
		//??u????
		Vector2D draw_pos_;
		draw_pos_.x_ = camera->DrawPositionX(world_position_.x_) ;
		draw_pos_.y_ = camera->DrawPositionY(world_position_.y_) + size_y_ / 2;
		Vector2D target_draw_pos_;
		target_draw_pos_.x_ = camera->DrawPositionX(target_.x_);
		target_draw_pos_.y_ = camera->DrawPositionY(target_.y_);
		// 予告線カウントに合わせて表示を切り替える
		if (pre_count_ > 0.0f) {
			DrawLine(draw_pos_.x_, draw_pos_.y_, target_draw_pos_.x_, target_draw_pos_.y_, GetColor(0,255,255));
		}
		else {
			DrawRotaGraph3(draw_pos_.x_, draw_pos_.y_, NULL, size_y_ / 2, extender_, window_setting::graph_extender_
				, rotate_, graph_handle_, TRUE);
		}

	}
}

void LongShot::Release()
{
}
