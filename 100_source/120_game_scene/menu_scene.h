//-----------------------------
// @name   menu_scene.h
// @brief  メニューシーン クラス
// @auther A.namami
// @date   2026/3/18  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "../110_drawing_tools/defining.h"
#include "..\110_drawing_tools\scene.h"

class Node;
class TextNode;

//-----------------------------
// @name   MenuScene
// @brief  メニューシーン
// @memo   セットしてから使うこと
//------------------------------

class MenuScene:public Scene
{

	Scene* next_scene_;//次のシーン
	Node* root_;//根ノード作成

	Node* text_;//テキストノード(テキスト親ノード)
	Node* selecter_node_;//選択用のノード

	int selecter_;//選択番号
	int last_select_;//直前の番号

public:
	//メニューの項目
	enum MenuItem {
		k_play, //曲を選ぶ
		k_config,//設定
		k_credit, //クレジットを出す
		k_about, //説明

		k_menu_item_max //最大
	};
	//キーの押し確認
	void PushCheck();
	//テキストの更新
	void TextUpdate();
	//コンストラクタ
	MenuScene() :selecter_(NULL), last_select_(NULL), text_(nullptr) {};
	//  デストラクタ
	~MenuScene() {};

	//  初期化
	void Init()override;
	//  準備
	void SetUp()override;
	//  終了
	void Finalize()override;
	//  更新
	Scene* Update(float delta_time)override;
	//  描画
	void Draw(int screen_handle)override;
};

//-----------------------------
// @name   SelectScene
// @brief  選択シーン
// @memo   セットしてから使うこと
//------------------------------
class SelectScene :public Scene
{

	Scene* next_scene_;//次のシーン
	Node* root_;//根ノード作成

	Node* text_;//テキストノード(テキスト親ノード)
	TextNode* defficult_[system_set::defficulter_max];//難易度毎のノード

	enum Selecters {
		k_music, //
		k_defficult,
		k_max
	};//選択番号の保存配列
	int selecter_[k_max];//選択番号
	int last_select_[k_max];//直前の番号

public:

	//キーの押し確認
	void PushCheck();
	//テキストの更新
	void TextUpdate();
	//コンストラクタ
	SelectScene();
	//  デストラクタ
	~SelectScene() {};

	//  初期化
	void Init()override;
	//  準備
	void SetUp()override;
	//  終了
	void Finalize()override;
	//  更新
	Scene* Update(float delta_time)override;
	//  描画
	void Draw(int screen_handle)override;

};



#endif // !__MENU_SCENE_H__


