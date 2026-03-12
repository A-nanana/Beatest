//-----------------------------
// @name   circle_node.cpp
// @brief  ‰~ƒm[ƒh ƒNƒ‰ƒX
// @auther A.namami
// @date   2026/3/12  V‹Kì¬
// @memo   ƒGƒ‰[Œ^‚ª—ˆ‚½ê‡‚Í-1‚Å•Ô‚µ‚Ü‚·
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "circle_node.h"
#include "camera.h"
#include "defining.h"
void CircleNode::Draw(int screen_handle,Camera* camera)
{
	DrawCircleAA(camera->DrawPositionX(world_position_.x_), camera->DrawPositionY(world_position_.y_), size_, size_/hit_set::size_per_point, color_code_, is_full_, thick_, angle_);
}

CircleNode::CircleNode(Vector2D pos, float r, bool is_full, unsigned int color, float thick,float angle)
	:size_(r), is_full_(is_full), color_code_(color), thick_(thick),angle_(angle)
{
	SetPosition(pos);
}
