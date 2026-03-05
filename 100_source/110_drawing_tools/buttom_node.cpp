//-----------------------------
// @name   buttom_node.cpp
// @brief  ボタンノード クラスの実装部
// @auther A.namami
// @date   2026/2/17  新規作成
//		   2026/2/26 Tagを追加(ラベリングできるようにしたかった)
//         2026/3/4  Cameraに対応
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <iostream>

#include "tool.h"
#include "inputer.h"
#include "buttom_node.h"

//  コンストラクタ
ButtomNode::ButtomNode(int size_x, int size_y,float x, float y, std::function<void()> call_back_func ,bool is_need_convert )
{
	size_.cx = size_x;
	size_.cy = size_y;
	is_need_convert_ = is_need_convert;
	call_back_func_ = call_back_func;
	pushed_down_ = false;
	pushed_ = false;
	SetPosition(x, y);
}

ButtomNode::ButtomNode(int size_x, int size_y, float x, float y, Tag tag, std::function<void()> call_back_func, bool is_need_convert)
{
	size_.cx = size_x;
	size_.cy = size_y;
	is_need_convert_ = is_need_convert;
	call_back_func_ = call_back_func;
	pushed_down_ = false;
	pushed_ = false;
	SetPosition(x, y);
	tag_ = tag;
}

//  セッター
void ButtomNode::SetIsNeedConvert(bool is_need_convert)
{
	is_need_convert_ = is_need_convert;
}

void ButtomNode::AddConvertChild(Node* node)
{
	//子側に親ノードとして追加
	//間に入れたいとき用、階層構造わかりやすく
	node->SetParent(this);

	//子ノードの追加
	this->convert_children_.push_back(node);
}

//マウス対応関係
bool ButtomNode::InnerMouse()
{
	int point_x = 0, point_y = 0;//カーソル位置
	Inputer::GetInstance()->GetMousePointer(&point_x, &point_y);
	//カーソル位置が判定の中にあるか
	if (InRenge(point_x, (int)world_position_.x_, (int)world_position_.x_ + size_.cx)
		&& InRenge(point_y, (int)world_position_.y_, (int)world_position_.y_ + size_.cy)) {
		return true;
	}
	return false;
}

void ButtomNode::PushMouseLeft()
{
	//範囲内でのクリック判定
	if (Inputer::GetInstance()->GetDownMouse(MOUSE_INPUT_LEFT)) {
		pushed_down_ = InnerMouse();

	}
	pushed_ = false;
	//ボタンが範囲内で離されているか
	if (pushed_down_ && Inputer::GetInstance()->GetUpMouse(MOUSE_INPUT_LEFT)) {
		pushed_down_ = false;
		pushed_ = InnerMouse();
	}

}

//ロード
void ButtomNode::Load()
{
	for (Node* child : convert_children_) {
		child->LoadResourceAll();
	}
}

//リリース
void ButtomNode::Release()
{
	for (Node* child : convert_children_) {
		child->ReleaseResourceAll();
	}
}

void ButtomNode::Update(float delta_time)
{
	PushMouseLeft();
	//押された & 関数が存在するならその関数を使う
	if (pushed_ && call_back_func_) {
		call_back_func_();
		Inputer::GetInstance()->SetGettingTag(tag_.tag_);

	}
}

//描画
void ButtomNode::Draw(int screen_handle,Camera* camera)
{
}

void ButtomNode::DrawAll(int screen_handle,Camera* camera) {
	this->Draw(screen_handle,camera);
	//カーソル位置が判定の中にあるか
	if (is_need_convert_ && InnerMouse()) {
		for (Node* child : convert_children_) {
			child->DrawAll(screen_handle,camera);
		}
	}
	else {
		for (Node* child : children_) {
			child->DrawAll(screen_handle,camera);
		}
	}

	
}

void ButtomNode::SetWorldPositionAll()
{
	this->SetWorldPosition();
	for (Node* child : convert_children_) {
		child->SetWorldPositionAll();
	}
	for (Node* child : children_) {
		child->SetWorldPositionAll();
	}
}
