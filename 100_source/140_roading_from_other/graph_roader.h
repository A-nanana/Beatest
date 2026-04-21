//-----------------------------
// @name   graph_roader.h
// @brief  画像読み込み クラス
// @auther A.namami
// @date   2026/4/20  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __GRAPH_ROADER_H__
#define __GRAPH_ROADER_H__

#include <iostream>
#include <string>
#include <unordered_map>

//-----------------------------
// @name   GraphRoader
// @brief  画像読み込み
// @memo   
//------------------------------
class GraphRoader {

	static GraphRoader* roader_; //インスタンス確認用
    // 読み込み済画像 
	std::unordered_map<std::string, int> graph_;


//  コンストラクタ
	GraphRoader();
//  デストラクタ
	~GraphRoader();
	
public:
//  複製防止
	GraphRoader operator= (const GraphRoader&) = delete;
	GraphRoader& operator= (GraphRoader&) = delete;

	//インスタンスアクセス
	static GraphRoader* GetInstance();

	//画像読み込み
	int RoadingGraph(std::string& name);
	int RoadingGraph(const char* name);
	//画像の削除
	void DeletingGraph(std::string& name);

};
#endif // !__FILE_ROADER_H__
