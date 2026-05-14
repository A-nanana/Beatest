//-----------------------------
// @name   shot_object.cpp
// @brief  弾オブジェクトクラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   
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

ShotObject::ShotObject(const int graph_handle, float x, float y, float speed,  Vector2D target, int type)
	:used_(true), target_(target), type_(type),cool_time_(0), ObjectCommon(graph_handle, x, y) {


	speed_size_ = speed;
	SetAngle(target_.x_, target_.y_);
	hit_use_ = true;
	GraphNode::Load();
	SetWorldPosition();
}

ShotObject::ShotObject(const char* graph_, float x, float y, float speed,  Vector2D target, int type)
	:used_(true),target_(target), type_(type), cool_time_(0) , ObjectCommon(graph_, x, y) {
	
	
	speed_size_ = speed;
	SetAngle(target_.x_, target_.y_);	
	hit_use_ = true;
	GraphNode::Load();
	SetWorldPosition();

}

ShotObject::~ShotObject()
{
	
}


//  ワールド座標で見た端を返す
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
	
	Vector2D speed_; //速度


	// 角度込みで計算

	speed_.x_ = cosf(rotate_) * speed_size_;
	speed_.y_ = sin(rotate_) * speed_size_;
	

	// 位置更新
	SetPosition(position_.x_ + speed_.x_, position_.y_ + speed_.y_);
	ObjectCommon::SetWorldPosition();
	//スコア加算用タイム加算
	cool_time_ += delta_time;

}

void ShotObject::Release()
{
	
}

LongShot::LongShot(const int graph_handle, float x, float y, float keep,  Vector2D target, int type)
	:ShotObject(graph_handle, x, y, keep,  target, type)
{

	//カウントセット
	pre_count_ = system_set::border_time;

	//初期設定
	pre_count_ = MusicManager::GetInstance()->GetMsPerHyousi();
	inner_count_ = keep;

	SetAngle(target_.x_, target_.y_);

	extender_ = WindowManager::GetInstance()->GetWindowLength() / size_x_;

	size_x_ = WindowManager::GetInstance()->GetWindowLength();
	SetHitSize(size_x_, system_set::lazer_width);
	hit_use_ = false;

}

LongShot::LongShot(const char* graph_, float x, float y, float keep,  Vector2D target, int type)
	:ShotObject(graph_, x, y, keep, target, type)
{
	pre_count_ = system_set::border_time;
	inner_count_ = keep;
	hit_use_ = false;
	SetAngle(target_.x_, target_.y_);
	
	extender_ = WindowManager::GetInstance()->GetWindowLength() / size_x_;
	size_x_ = WindowManager::GetInstance()->GetWindowLength();
	SetHitSize(size_x_ , system_set::lazer_width);
}

void LongShot::SetWorldPosition()
{

	 ObjectCommon::SetWorldPosition();
    //中心に合わせて頂点のローカル座標 作成
    point_[0].Set(0.0f, -hit_size_.y_ / 2);
    point_[1].Set(+hit_size_.x_ , -hit_size_.y_ / 2);
    point_[2].Set(+hit_size_.x_ , +hit_size_.y_ / 2);
    point_[3].Set(0.0f, +hit_size_.y_ / 2);
    //行列作成
    Matrix2 mat;//変換用
    mat.SetMatrixRotate(rotate_);
    for (int i = 0; i < hit_set::squair_point; i++) {
        point_[i].ChangeForMatrix(mat);
		point_[i].Add(GetWorldPosition().x_, GetWorldPosition().y_ ); // ワールド座標に戻す
    }

    //ベクトル作成
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
	//スコア加算用タイム加算
	cool_time_ += delta_time;

	//予備動作カウントの減少
	pre_count_ -= delta_time;

	//予備動作カウントを確認
	if (pre_count_ >= 0.0f) {
		hit_use_ = false;
		
	}
	else {
		hit_use_ = true;
		//カウント減らす
		inner_count_ -= delta_time;
	}
	
	// カウントを確認
	if (pre_count_ > 0.0f) {
		hit_use_ = false;
	}
	else {
		// 表示カウントを減らす
		inner_count_ -= delta_time;
		hit_use_ = true;
	}
	//表示カウントが負か
	if (inner_count_ <= 0.0f) {

		hit_use_ = false;
		used_ = false;
	}
	SetWorldPosition();

}



void LongShot::Draw(int screen_handle, Camera* camera)
{
	//描画できるか
	if (camera->IsDraw(GetWorldPosition(), size_x_, size_y_)) {
		//描画位置の計算
		Vector2D draw_pos_;
		Vector2D target_draw_pos_;
		draw_pos_.x_ = camera->DrawPositionX(world_position_.x_) ;

		draw_pos_.y_ = camera->DrawPositionY(world_position_.y_) - size_y_ / 2;
		//カウントが切れるまでは予告線のみ出す
		if (!hit_use_) {
			draw_pos_.y_ = camera->DrawPositionY(world_position_.y_) + size_y_ / 2;
			
			target_draw_pos_.x_ = camera->DrawPositionX(target_.x_);
			target_draw_pos_.y_ = camera->DrawPositionY(target_.y_);
		}
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
