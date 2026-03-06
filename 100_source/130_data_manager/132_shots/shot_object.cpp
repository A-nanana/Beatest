//-----------------------------
// @name   shot_object.cpp
// @brief  弾オブジェクト クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "shot_object.h"
#include "..\131_character\player_object.h"
#include "..\..\110_drawing_tools\defining.h"

ShotObject::ShotObject(const int graph_handle, float x, float y, float speed, float angle)
	:used_(true), ObjectCommon(graph_handle, x, y) {
	
	speed_.x_ = speed * cos(angle);
	speed_.y_ = speed * sin(angle);
	SetRotate(angle);
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
		used_ = true;

		return 1;
	}
}


//更新
void ShotObject::Update(float delta_time) {
	//方向の各成分入れ
	Vector3D a, b;
	//今の向き
	double m_angle = atan2(world_position_.y_, world_position_.x_);

	// 今進んでいる方向
	b.Set(cosf(m_angle), sinf(m_angle));
	//  本来進むべき方向
	a.Set(PlayerObject::GetInstance()->GetWorldPosition().x_ - world_position_.x_,
		PlayerObject::GetInstance()->GetWorldPosition().y_ - world_position_.y_);

	// 外積を利用し向きを照準側に向ける
	a.Cross(b);
	//反時計回りか
	if (a.x_ < 0.0f) {
		m_angle += -system_set::angle_per_time;
	}
	else {
		m_angle += system_set::angle_per_time;
	}

	//向き計算のマトリクスを作成
	Matrix2 mat;
	mat.SetMatrixRotate(m_angle);
	// 速度変更
	speed_.ChangeForMatrix(mat);
	

	// 移動
	position_.Add(speed_);
	is_caliculate_ = false;

}

void ShotObject::Release()
{

}


