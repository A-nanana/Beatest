//-----------------------------
// @name   node.h
// @brief  ノード クラスの宣言部
// @auther A.namami
// @date   2026/2/2  新規作成
//		   2026/2/26 Tagを追加(ラベリングできるようにしたかった)
//         2026/3/4  Cameraに対応
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once

#include <list>
#include "DxLib.h"
#include "Vector2.h"


//-----------------------------
// @name   Tag
// @brief  中身処理
// @memo   セットしてから使うこと
//------------------------------
class Tag {
public:
	int tag_;//タグ
	static Tag ChangeTag(int tag);
};

//-----------------------------
// @name   Node
// @brief  描画用ノード
// @memo   セットしてから使うこと
//------------------------------
class Camera;
class Node

{
protected:
	Node* parent_; //親ノードのポインタ
	std::list<Node*> children_; //子ノードのポインタ
	Vector2D world_position_; //ワールド位置
	Vector2D position_; //親との相対位置
	bool is_caliculate_; //座標をワールド座標にしたか

//  各自でオーバーライドする
	//ロード
	virtual void Load() {};
	//リソース解放
	virtual void Release() {};
	//セット
	virtual void SetUp() {};
	//更新(更新するときの時間)
	virtual void Update(float delta_time) {};
	//描画(描画先)
	virtual void Draw(int screen_handle,Camera* camera) {};


public:

//  親のセット
	void SetParent(Node* parent) { parent_ = parent; };

//  座標関係
	//相対位置取得
	Vector2D GetPosition() { return position_; };
	//ワールド位置取得
	Vector2D GetWorldPosition() { return world_position_; };

	//相対位置設定
	void SetPosition(const Vector2D& pos);
	void SetPosition(const float& x, const float& y);
	//ワールド位置設定
	void SetWorldPosition(const Vector2D& pos) { world_position_ = pos; };
	void SetWorldPosition();


//  追加
	//子の追加
	void AddChild(Node* node);
	//num番目の子ノードを取得(主にルートノードで使用)
	Node* GetChild(int num);
	//子の削除
	void DeleteChild(Node* node);

//  呼び出し
	//これと全て子のリソース読み込み
	virtual void LoadResourceAll() final; 
	//これと全て子のリソース解放
	virtual void ReleaseResourceAll() final;
	//これと全て子のリソースセット
	virtual void SetUpAll()final;
	//これと全て子のリソース更新(更新時間)
	virtual void UpdateAll(float delta_time) final;
	//これと全て子の描画(描画先)
	virtual void DrawAll(int screen_handle,Camera* camera);
	//これと全て子の座標をワールド座標に
	virtual void SetWorldPositionAll();

//  コンストラクタ
	Node();

//  デストラクタ
	virtual ~Node();
};

