//-----------------------------
// @name   splite_node.h
// @brief  スプライトノード クラスの宣言部
// @auther A.namami
// @date   2026/3/11  新規作成
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once

#include <string>
#include "node.h"
#include "Vector2.h"

class SpliteNode:public Node
{
protected:
	int graph_handle_;//画像ハンドル
	std::string name_;//画像名

	int all_indix_;//最大タイル数
	int now_index_;//今のタイル番号
	Vector2D pos_num_;//タイルの各列番号
	Vector2D separate_size_;//1タイルあたりの大きさ

	int time_count_;//変換用カウンタ
	bool is_loop_;//ループの有無
	const int step_time_ms = 40; //切り替え時間

	//ロード
	void Load() ;
	//リソース解放
	void Release() ;
	//更新(更新するときの時間)
	void Update(float delta_time);
	//描画(描画先)
	void Draw(int screen_handle);
public:
//  コンストラクタ
	SpliteNode(const char* name);
	SpliteNode(const char* name,Vector2D pos);
	SpliteNode(const char* name, Vector2D pos, Vector2D separate_size,bool is_loop = false);

};

