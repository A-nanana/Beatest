//-----------------------------
// @name   enemy_object.cpp
// @brief  敵オブジェクト クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include <iostream>
#include "enemy_object.h"

#include "..\132_shots\shot_manager.h"
#include "..\132_shots\shot_booker.h"
#include "..\132_shots\shot_object.h"
#include "..\..\110_drawing_tools\defining.h"
#include "..\..\110_drawing_tools\tool.h"

EnemyObject::EnemyObject(ShotManager* shot_manager, std::vector<ShotBooker>* shot_booker)
	:shot_manager_(shot_manager),shot_booker_(shot_booker),ObjectCommon(file_set::enemy, 1.0f, 1.0f, 90.0f, 120.0f)
{
	time_ = NULL;
}

void EnemyObject::Update(float delta_time) {
	//角度設定
	SetAngle(shot_manager_->GetPlayerCenter().x_, shot_manager_->GetPlayerCenter().y_);
	time_ += delta_time;

	//予約確認
	int n = 0;
	for (n = 0; n < shot_booker_->size(); n++) {

		//時間合わせ
		int check = shot_booker_->operator[](n).bool_time ;
		check -= shot_manager_->GetPlayerObjectPos().Length() / shot_booker_->operator[](n).speed;
		
		//猶予時間中なら発射
		if (check >  time_- (window_setting::sec_per_frame)  && check <=  time_
			&& shot_booker_->operator[](n).shooted == false) {
			break;
		}

	}
	//譜面なしで終了
	if (shot_booker_->size() <= n) return;
	float speed = shot_booker_->operator[](n).speed; //速度
	//それ以外なら打ち出す
	for (int i = 0; i < shot_booker_->operator[](n).rooper; i++) {
		float angle = rotate_ + (system_set::angle_per_time * i );
		//角度正規化
		//2PIこえたら戻す
		if (angle > M_PI * 2) {
			angle -= M_PI * 2;
		}
		//0こえたら戻す
		if (angle < NULL) {
			angle += M_PI * 2;
		}
		//もし時差打ちが必要なら速度を変える
		if (shot_booker_->operator[](n).type == system_set::k_enemy_later_renge) {
			speed -= system_set::shot_speed_down;
		}
		shot_manager_->AddShot(world_position_.x_ + size_x_ / 2, world_position_.y_ + size_y_ / 2,
			speed, angle, shot_booker_->operator[](n).type);

	}
	shot_booker_->operator[](n).shooted = true;

}

