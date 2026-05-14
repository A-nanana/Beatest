//-----------------------------
// @name   color_manager.h
// @brief  色管理 クラス
// @auther A.namami
// @date   2026/5/14  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __COLOR_MANAGER_H__
#define __COLOR_MANAGER_H__

#include <unordered_map>
#include <string>
#include "DxLib.h"
#include "../../110_drawing_tools\tool.h"

//-----------------------------
// @name   ColorSet
// @brief  色 クラス
// @memo   色の設計用
//         要素の一括保存にどうぞ
//         Dxライブラリ準拠
//------------------------------
class ColorSet
{
public:
	enum Color {
		k_red, //赤
		k_green,//緑
		k_blue,//青
		k_max//最大
	};
private:
	int rgb_[k_max];//色要素
public:
	//コンストラクタ
	ColorSet();
	ColorSet(int r, int g, int b);
	//色の一括変更(-1で変更なし)
	void SetColor3(int r, int g, int b);
	//色の取得
	int Color(Color youso) { return rgb_[youso]; };//各要素
	unsigned int ColorCode() { return GetColor(rgb_[k_red], rgb_[k_green], rgb_[k_blue]); };//色コード
};


//-----------------------------
// @name   ColorManager
// @brief  色 管理クラス
// @memo   色の管理用
//         Dxライブラリ準拠
//------------------------------
class ColorManager
{
	static ColorManager* instance_; // インスタンス
	
	std::unordered_map<std::string, ColorSet*> color_;//色

	//  コンストラクタ
	ColorManager();
	//  デストラクタ
	~ColorManager();

public:
	//  インスタンスアクセス
	static ColorManager* GetInstance();
	//  複製防止
	ColorManager operator= (const ColorManager&) = delete;
	ColorManager& operator= (ColorManager&) = delete;

	//  色追加
	void AddColor(int red, int green, int blue, const char* collect_name);//作成
	void AddColor(ColorSet* color, const char* collect_name);//あるものを登録
	//  色検索
	unsigned int SerchColor(const char* collect_name); //配列番号から検索


};


#endif // ! __COLOR_MANAGER_H__