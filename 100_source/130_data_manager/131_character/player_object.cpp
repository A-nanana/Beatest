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

	//移動値を加算
	position_.Add(move_vector);
	world_position_.Add(move_vector);
}
