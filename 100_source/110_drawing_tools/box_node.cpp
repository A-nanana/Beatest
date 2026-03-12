//-----------------------------
// @name   box_node.cpp
// @brief  箱ノード クラス
// @auther A.namami
// @date   2026/3/12  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "box_node.h"
#include "camera.h"

void BoxNode::Draw(int screen_handle,Camera* camera)
{
	DrawBoxAA(camera->DrawPositionX(world_position_.x_), camera->DrawPositionY(world_position_.y_),
		camera->DrawPositionX(world_position_.x_ + size_.x_), camera->DrawPositionY(world_position_.y_ + size_.y_),
		color_code_, is_full_, thick_);
}

BoxNode::BoxNode(Vector2D pos, Vector2D size, unsigned int color, float thick, bool is_full)
	:size_(size), is_full_(is_full),color_code_(color),thick_(thick)
{
	SetPosition(pos);
}

void BoxNode::AddSize(Vector2D add)
{
	SetPosition(GetPosition().x_ - add.x_ / 2, GetPosition().y_ - add.y_ / 2);
	size_.Add(add);
}

void BoxNode::SubSize(Vector2D sub)
{
	SetPosition(GetPosition().x_ + sub.x_ / 2, GetPosition().y_ + sub.y_ / 2);
	size_.Sub(sub);
}
