//-----------------------------
// @name   config_scene.h
// @brief  設定シーン クラス
// @auther A.namami
// @date   2026/3/16  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __CONFIG_SCENE_H__
#define __CONFIG_SCENE_H__ 

#include "..\110_drawing_tools\scene.h"

class Node;
class TextNode;
//-----------------------------
// @name   ConfigScene
// @brief  設定
// @memo   セットしてから使うこと
//------------------------------
class ConfigScene :public Scene
{

	Scene* next_scene_;//次のシーン

	Node* root_;//根ノード作成

	Node* text_;//テキスト用根ノード
	Node* selecter_node_;//セレクター用ノード

	int selecter_;//設定の選択カーソル


public:

	//キーの押し確認
	void PushCheck();
	//テキスト更新
	void TextUpdate();

	//コンストラクタ
	ConfigScene() { tag_ = PositionTag::next_returner; };
	//  デストラクタ
	~ConfigScene() {};

	//  初期化
	void Init() override;
	//  準備
	void SetUp() override;
	//  終了
	void Finalize() override;
	//  更新
	Scene* Update(float delta_time) override;
	//  描画
	void Draw(int screen_handle) override;

};


//-----------------------------
// @name   CreditScene
// @brief  クレジット
// @memo   セットしてから使うこと
//------------------------------
class CreditScene :public Scene
{

	Scene* next_scene_;//次のシーン

	Node* root_;//根ノード作成

	Node* text_;//テキスト用根ノード
	Node* selecter_node_;//セレクター用ノード

	int selecter_;//設定の選択カーソル


public:

	//キーの押し確認
	void PushCheck();
	

	//コンストラクタ
	CreditScene() { tag_ = PositionTag::next_returner; };
	//  デストラクタ
	~CreditScene() {};

	//  初期化
	void Init() override;
	//  準備
	void SetUp() override;
	//  終了
	void Finalize() override;
	//  更新
	Scene* Update(float delta_time) override;
	//  描画
	void Draw(int screen_handle) override;

};


#endif // !__CONFIG_SCENE_H__