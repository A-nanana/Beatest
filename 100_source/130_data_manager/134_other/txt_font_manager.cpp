//-----------------------------
// @name   txt_font_manager.cpp
// @brief  テキストフォーマット管理 クラス
// @auther A.namami
// @date   2026/3/31  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "txt_font_manager.h"

TxtFontManager* TxtFontManager::txt_manager_ = nullptr;

//  コンストラクタ
TxtFontManager::TxtFontManager() {
	//最初に使うものを作っておく
	AddFont(font_set::midasi_font_name_1, font_set::midasi_size_1, font_set::midasi_thick_1, DX_FONTTYPE_EDGE, string_set::font_midasi1);
	AddFont(font_set::midasi_font_name_1,font_set::midasi_size_2,font_set::midasi_thick_1, DX_FONTTYPE_EDGE,string_set::font_midasi2);

}
//  デストラクタ
TxtFontManager::~TxtFontManager() {
	//ポインタ削除
	for (auto font : fonts_) {
		delete font.second;
	}
}

//  インスタンスアクセス
TxtFontManager* TxtFontManager::GetInstance() {
	//もしインスタンスがなかったら新規作成
	if (txt_manager_ == nullptr) {
		txt_manager_ = new TxtFontManager();
	}

	return txt_manager_;
}

void TxtFontManager::AddFont(const char* font_name, int size, int thick, int type, const char* collect_name)
{
	//既にあるなら返す
	if (fonts_.count(collect_name)) {
		return;
	}

	fonts_[std::string(collect_name)] = new FontSet(font_name, size, thick, type);

}

void TxtFontManager::AddFont(FontSet* font, const char* collect_name)
{
	fonts_[std::string(collect_name)] = font;
}

int TxtFontManager::SerchFont(const char* collect_name)
{
	
	return fonts_[collect_name]->GetFontHandle();
}
