//-----------------------------
// @name   result_scene.h
// @brief  結果シーン クラス
// @auther A.namami
// @date   2026/3/10  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__


#include "..\110_drawing_tools\scene.h"

class Node;
class TextNode;
class Time;
//-----------------------------
// @name   ResultScene
// @brief  結果
// @memo   セットしてから使うこと
//------------------------------

class ResultScene:public Scene
{

	Scene* next_scene_;//次のシーン
	Node* root_;//根ノード作成
	//状態遷移用
	enum ResFase {
		k_fase_all_res_ , //最終結果
		k_fase_conbo_,//コンボ数出す
		k_fase_end_,//出し終わり

	};
	ResFase fase_;//結果出しの状態

	Node* root_res_[k_fase_end_];//結果のノード
	

	int time_hold_;//累計時間

public:

	//キーの押し確認
	void PushCheck();
	//テキストデータのアップデート
	void TextUpdate();

	//コンストラクタ
	ResultScene();
	//  デストラクタ
	~ResultScene() {};

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


#endif // !__RESULT_SCENE_H__

