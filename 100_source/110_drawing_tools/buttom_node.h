//-----------------------------
// @name   buttom_node.h
// @brief  ボタンノード クラスの宣言部
// @auther A.namami
// @date   2026/2/17  新規作成
//		   2026/2/26 Tagを追加(ラベリングできるようにしたかった)
//         2026/3/4  Cameraに対応
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once

#include <functional>
#include "node.h"
class ButtomNode:public Node
{
protected:
	bool is_need_convert_;//変化があるか
	bool pushed_down_;//カーソルが中にいるか
	bool pushed_;//押されたか
	SIZE size_;//ボタン判定の大きさ
	std::list<Node*> convert_children_; //変化後の子ノードのポインタ

	std::function<void()> call_back_func_; //反応させたい場合の関数
	Tag tag_;//タグ

public:
	

	//  コンストラクタ(x,yは相対位置)
	ButtomNode(int size_x,int size_y,float x, float y, std::function<void()> call_back_func = nullptr ,bool is_need_convert = false);
	ButtomNode(int size_x, int size_y, float x, float y, Tag tag, std::function<void()> call_back_func = nullptr, bool is_need_convert = false);

	//  セッター
	void SetIsNeedConvert(bool is_need_convert);
	void AddConvertChild(Node* node);
	
	//マウス対応関係
	bool InnerMouse();//中にマウスがあるか
	void PushMouseLeft(); //押されたか


	//  オーバーライド系列
		//ロード
	void Load() override;
	//リリース
	void Release() override;
	//更新(更新するときの時間)
	void Update(float delta_time) override;
	//描画
	void Draw(int screen_handle,Camera* caera) override;
	//これと全て子の描画(描画先)
	virtual void DrawAll(int screen_handle,Camera* camera);
	//これと全て子の座標をワールド座標に
	void SetWorldPositionAll();
};

