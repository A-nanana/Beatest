//-----------------------------
// @name   top_scene.h
// @brief  冒頭シーン クラス
// @auther A.namami
// @date   2026/3/9  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __TOP_SCENE_H__
#define __TOP_SCENE_H__ 

#include "..\110_drawing_tools\scene.h"

class Node;
class TextNode;
//-----------------------------
// @name   TopScene
// @brief  表紙
// @memo   セットしてから使うこと
//------------------------------
class TopScene:public Scene
{

	Scene* next_scene_;//次のシーン
	Node* root_;//根ノード作成
	
public:

	//キーの押し確認
	void PushCheck();

	//コンストラクタ
	TopScene() {};
	//  デストラクタ
	~TopScene() {};

	//  初期化
	void Init();
	//  準備
	void SetUp();
	//  終了
	void Finalize();
	//  更新
	Scene* Update(float delta_time);
	//  描画
	void Draw(int screen_handle);

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

	int selecter_;//選択番号
	int last_select_;//直前の番号

public:

	//キーの押し確認
	void PushCheck();
	//テキストの更新
	void TextUpdate();
	//コンストラクタ
	SelectScene():selecter_(0),last_select_(0),text_(nullptr) {};
	//  デストラクタ
	~SelectScene() {};

	//  初期化
	void Init();
	//  準備
	void SetUp();
	//  終了
	void Finalize();
	//  更新
	Scene* Update(float delta_time);
	//  描画
	void Draw(int screen_handle);

};



#endif // !__TOP_SCENE_H__


