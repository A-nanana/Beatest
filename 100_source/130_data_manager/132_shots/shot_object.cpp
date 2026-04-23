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

ShotObject::ShotObject(const int graph_handle, float x, float y, float speed, float angle, Vector2D target, int type)
	:used_(true), target_(target), type_(type), ObjectCommon(graph_handle, x, y) {


	speed_size_ = speed;
	SetRotate(angle);
	hit_use_ = false;
	GraphNode::Load();
}

ShotObject::ShotObject(const char* graph_, float x, float y, float speed, float angle, Vector2D target, int type)
	:used_(true),target_(target), type_(type), ObjectCommon(graph_, x, y) {
	
	
	speed_size_ = speed;
	SetRotate(angle);
	hit_use_ = false;
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



//更新
void ShotObject::Update(float delta_time) {
	
	Vector2D speed_; //速度.


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

LongShot::LongShot(const int graph_handle, float x, float y, float keep, float angle, Vector2D target, int type)
	:ShotObject(graph_handle, x, y, keep, angle, target, type)
{
	//カウントセット
	pre_count_ = MusicManager::GetInstance()->GetMsPerHyousi();
	inner_count_ = keep;

	SetAngle(target_.x_, target_.y_);


	extender_ = (float)window_setting::length / size_x_;

	size_x_ = window_setting::length;
	SetHitSize(size_x_, size_y_ * window_setting::graph_extender_);
}

LongShot::LongShot(const char* graph_, float x, float y, float keep, float angle, Vector2D target, int type)
	:ShotObject(graph_, x, y, keep, angle, target, type)
{
	pre_count_ = MusicManager::GetInstance()->GetMsPerHyousi();
	inner_count_ = keep;
	
	SetAngle(target_.x_, target_.y_);
	
	extender_ = (float)window_setting::length / size_x_;
	size_x_ = window_setting::length;
	SetHitSize(size_x_ , size_y_ * window_setting::graph_extender_);
}

void LongShot::SetWorldPosition()
{

	 ObjectCommon::SetWorldPosition();
    //頂点(回転の中心と図形の中心を合わせる)設定
    point_[0].Set(0.0f, -hit_size_.y_ / 2);
    point_[1].Set(+hit_size_.x_ , -hit_size_.y_ / 2);
    point_[2].Set(+hit_size_.x_ , +hit_size_.y_ / 2);
    point_[3].Set(0.0f, +hit_size_.y_ / 2);
    //回転行列で変換
    Matrix2 mat;//変換用マトリクス
    mat.SetMatrixRotate(rotate_);
    for (int i = 0; i < hit_set::squair_point; i++) {
        point_[i].ChangeForMatrix(mat);
        point_[i].Add(GetWorldPosition().x_ , GetWorldPosition().y_ + hit_size_.y_ / 2.0f); //ワールド座標に変換
    }

    //ベクトル計算
    for (int i = 0; i < hit_set::squair_point; i++) {
        vectol_[i].Set(point_[(i + 1) % hit_set::squair_point]);
        vectol_[i].Sub(point_[i]);
    }

}

void LongShot::Update(float delta_time)
{
	//予備動作カウントを減らす
	pre_count_ -= delta_time;
	//予備動作カウントを確認
	if (pre_count_ < NULL) {
		hit_use_ = true;
		//カウント減らす
		inner_count_ -= delta_time;
	}
	//カウントが切れているか
	if (inner_count_ < NULL) {
		used_ = false;
	}
	SetWorldPosition();

}



void LongShot::Draw(int screen_handle, Camera* camera)
{
	//カメラ内か
	if (camera->IsDraw(GetWorldPosition(), size_x_, size_y_)) {
		//位置測定
		Vector2D draw_pos_;
		draw_pos_.x_ = camera->DrawPositionX(world_position_.x_) ;
		draw_pos_.y_ = camera->DrawPositionY(world_position_.y_) - size_y_ / 2;
		//カウントで切り替え
		if (pre_count_ >= NULL) {
			DrawLine(draw_pos_.x_, draw_pos_.y_, target_.x_, target_.y_,GetColor(0,255,255));
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
