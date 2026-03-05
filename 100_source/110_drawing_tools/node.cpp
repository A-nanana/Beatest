//-----------------------------
// @name   node.cpp
// @brief  テスト用の実行部
// @auther A.namami
// @date   2026/2/2  新規作成
//		   2026/2/26 Tagを追加(ラベリングできるようにしたかった)
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "node.h"
#include "camera.h"

//-----------------------------
// @name   Tag
// @brief  中身処理
// @memo   セットしてから使うこと
//------------------------------
Tag Tag::ChangeTag(int tag)
{
	Tag returner;//返す値
	returner.tag_ = tag;
	return returner;
}



//-----------------------------
// @name   Node
// @brief  描画用ノード
// @memo   セットしてから使うこと
//------------------------------

void Node::SetPosition(const Vector2D& pos)
{
	this->position_ = pos;
	is_caliculate_ = false;
}

void Node::SetPosition(const float& x, const float& y) {

	this->position_.x_ = x;
	this->position_.y_ = y;
	is_caliculate_ = false;
}

void Node::SetWorldPosition()
{
	//計算前か
	if (!is_caliculate_) {
		//親を参照できるか
		if (parent_ != nullptr) {
			this->world_position_.x_ = parent_->GetWorldPosition().x_ + position_.x_;
			this->world_position_.y_ = parent_->GetWorldPosition().y_ + position_.y_;
		}
		else {
			this->world_position_.x_ = this->world_position_.x_ + position_.x_;
			this->world_position_.y_ = this->world_position_.y_ + position_.y_;
		}
		is_caliculate_ = true;
	}
}

void Node::AddChild(Node* node)
{
	//子側に親ノードとして追加
	//間に入れたいとき用、階層構造わかりやすく
	node->parent_ = this;

	//子ノードの追加
	this->children_.push_back(node);
}

//num番目の子ノードを取得(主にルートノードで使用)
Node* Node::GetChild(int num)
{
	int counter = 0;//位置カウンター
	for (std::list<Node*>::iterator i = children_.begin(); i != children_.end(); i++) {
		//現在位置が番号位置と一致するか
		if (counter == num) {
			return *i;
		}
		counter++;
	}
	return nullptr;
}

void Node::LoadResourceAll()
{
	this->Load();
	for (Node* child : children_) {
		child->LoadResourceAll();
	}
}

void Node::ReleaseResourceAll()
{
	this->Release();
	for (Node* child : children_) {
		child->ReleaseResourceAll();
	}
}

void Node::UpdateAll(float delta_time)
{
	this->Update(delta_time);
	for (Node* child : children_) {
		child->UpdateAll(delta_time);
	}
}

void Node::DrawAll(int screen_handle, Camera* camera)
{
	this->Draw(screen_handle,camera);
	for (Node* child : children_) {
		child->DrawAll(screen_handle,camera);
	}
}

void Node::SetWorldPositionAll()
{
	this->SetWorldPosition();
	for (Node* child : children_) {
		child->SetWorldPositionAll();
	}
}

Node::Node()
{
	parent_ = nullptr;
	children_.clear();
	position_.x_ = 0.0f;
	position_.y_ = 0.0f;
	world_position_.x_ = 0.0f;
	world_position_.y_ = 0.0f;
	is_caliculate_ = false;
}

Node::~Node()
{
	for (Node* child : children_) {
		delete child;
	}
	children_.clear();
}
