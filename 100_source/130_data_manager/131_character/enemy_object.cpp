//-----------------------------
// @name   enemy_object.cpp
// @brief  敵オブジェクト クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "enemy_object.h"
#include "..\132_shots\shot_manager.h"
#include "..\132_shots\shot_booker.h"
#include "..\132_shots\shot_object.h"
#include "..\..\110_drawing_tools\defining.h"
#include "..\..\110_drawing_tools\tool.h"

EnemyObject::EnemyObject(ShotManager* shot_manager, std::vector<ShotBooker>* shot_booker)
	:shot_manager_(shot_manager),shot_booker_(shot_booker),ObjectCommon("..\\200_resource\\enemy.png", 1.0f, 1.0f, 180.0f, 180.0f)
{
	
}

void EnemyObject::SetAngle(float to_x, float to_y)
{
	//算出用座標
	float dy = to_y - world_position_.y_;
	float dx = to_x - world_position_.x_;
	//算出用角度
	float angle;
	//0がらみの安定化
	if (AlmostEqual(dx, 0) && AlmostEqual(dy, 0)) {
		angle = system_set::repair_rad;
	}
	else {
		angle = atan2(dy, dx);
	}

	rotate_ = angle;
}

void EnemyObject::Update(float delta_time) {
	//角度設定
	SetAngle(shot_manager_->GetPlayerObjectPos().x_, shot_manager_->GetPlayerObjectPos().x_);
	//予約確認
	int n = 0;
	for (n = 0; n < shot_booker_->size(); n++) {

		//時間合わせ(前回からの差)
		int check = shot_booker_->operator[](n).bool_time;

		
		//std::cout << boder << std::endl;
		if (check > delta_time - system_set::border_time && check < delta_time + system_set::border_time
			&& shot_booker_->operator[](n).shooted == false) {
			break;
		}

	}
	//譜面なしで終了
	if (shot_booker_->size() <= n) return;
	//それ以外なら打ち出す
	for (int i = 0; i < shot_booker_->operator[](n).rooper; i++) {
		float angle = rotate_ + (system_set::angle_per_time * i /shot_booker_->operator[](n).rooper);


		shot_manager_->AddShot(world_position_.x_ + size_x_/2, world_position_.y_ + size_y_ / 2,
			shot_booker_->operator[](n).speed, angle);

	}

}

