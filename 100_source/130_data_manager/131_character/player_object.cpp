#include <iostream>
#include "player_object.h"
#include "..\..\110_drawing_tools\inputer.h"
#include "..\..\110_drawing_tools\defining.h"
#include "..\..\110_drawing_tools\tool.h"

PlayerObject* PlayerObject::player_ = nullptr;
PlayerObject::PlayerObject():ObjectCommon("..\\200_resource\\aruku.png", 1.0f, 1.0f, 180.0f, 180.0f)
{
}

PlayerObject* PlayerObject::GetInstance()
{
	if (player_ == nullptr) {
		player_ = new PlayerObject();
	}
	return player_;
}

void PlayerObject::Update(float delta_time)
{
	//加算用
	Vector2D move_vector(NULL,NULL);
	//直前位置の記憶
	Vector2D last_pos(world_position_);

	//Wキーで上に
	if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_W)) {
		move_vector.Add(NULL, -system_set::player_walk_speed);
	}
	//Sキーで下に
	if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_S)) {
		move_vector.Add(NULL, system_set::player_walk_speed);
	}
	//Aキーで左に
	if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_A)) {
		move_vector.Add(-system_set::player_walk_speed, NULL);
	}
	//Dキーで右に
	if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_D)) {
		move_vector.Add(system_set::player_walk_speed, NULL);
	}
	//ノルム化
	move_vector.Normalize();
	move_vector.Scale(system_set::player_walk_speed);
	//端の場合はクランプ
	CrampDouble(move_vector.x_, -last_pos.x_, window_setting::size_x - size_x_ - last_pos.x_);
	CrampDouble(move_vector.y_, -last_pos.y_, window_setting::size_y -size_y_ - last_pos.y_);
	//位置の加算
	SetPosition(position_.x_ + move_vector.x_, position_.y_ + move_vector.y_);
	ObjectCommon::SetWorldPosition();


}
