//-----------------------------
// @name   txt_font_manager.h
// @brief  テキストフォーマット管理 クラス
// @auther A.namami
// @date   2026/3/31  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __TXT_FONT_MANAGER_H__
#define __TXT_FONT_MANAGER_H__

#include <unordered_map>
#include <string>
#include "DxLib.h"
#include "..\..\110_drawing_tools\text_node.h"
#include "..\..\110_drawing_tools\defining.h"
#include "..\..\110_drawing_tools\tool.h"

class TxtFontManager
{
	static TxtFontManager* txt_manager_; // インスタンス
	std::unordered_map<std::string, FontSet*> fonts_;//フォント
	
//  コンストラクタ
	TxtFontManager();
//  デストラクタ
	~TxtFontManager();

public:
//  インスタンスアクセス
	static TxtFontManager* GetInstance();
//  複製防止
	TxtFontManager operator= (const TxtFontManager&) = delete;
	TxtFontManager& operator= (TxtFontManager&) = delete;

//  フォント追加
	void AddFont(const char* font_name, int size, int thick, int type,const char* collect_name); //中でポインタ作成
	void AddFont(FontSet* font, const char* collect_name); //既にあるポインタを読み込む
//  フォント検索
	int SerchFont(const char* collect_name); //配列番号から検索


};


#endif // !__TXT_FONT_MANAGER_H__
