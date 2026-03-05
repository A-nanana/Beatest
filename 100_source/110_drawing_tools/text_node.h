//-----------------------------
// @name   text_node.h
// @brief  文字ノード クラスの宣言部
// @auther A.namami
// @date   2026/2/17  新規作成
//         2026/3/4  Cameraに対応
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once

#include <string>
#include "tool.h"
#include "node.h"

//-----------------------------
// @name   TextNode
// @brief  文字ノード クラスの宣言部
// @memo   フォント指定ができないので注意
//------------------------------
class TextNode:public Node
{
protected:
	std::string text_;//文字
	unsigned int text_color_; //文字の色

public:
	//  コンストラクタ(x,yは相対位置)
	TextNode(const char* text, unsigned int text_color, float x, float y);
	TextNode(const char* text, unsigned int red, unsigned int green, unsigned int blue, float x, float y);

	//  セッター
	void SetText(const char* text); //文字
	void SetColor(unsigned int text_color); //文字の色
	void SetColor(unsigned int red, unsigned int green, unsigned int blue); //文字の色

	//  オーバーライド系列
		//ロード
	void Load() override;
	//リリース
	void Release() override;
	//描画
	void Draw(int screen_handle,Camera* camera) override;

};


//-----------------------------
// @name   FontSet
// @brief  フォント クラスの宣言部
// @memo   フォントの設計用
//         これを使って作ること
//         Dxライブラリ準拠
//------------------------------
class FontSet {
protected:
	std::string font_name_;//フォントの名前
	int size_;//大きさ
	int thick_;//太さ
	int type_;//フォントタイプ

	int handle_;//このフォントのハンドル
public:
	//  コンストラクタ
	FontSet(const char* font_name, int size, int thick, int type);

	//  セッター
	void SetFontName(const char* font_name); //フォントの名前
	void SetFontSize(int size); //サイズ
	void SetFontThick(int thick); //太さ
	void SetFontType(int type); //フォントタイプ

	//  ゲッター
	int GetFontHandle(); //フォントハンドル

	//ロード
	void Load();
	//解放
	void Release();
};


//-----------------------------
// @name   TextFormatNode
// @brief  文字ノード クラスの宣言部
// @memo   フォント指定ができるタイプ
//         事前に作ったものを使用すること
//------------------------------
class TextFormatNode :public Node
{
protected:
	std::string text_;//文字
	unsigned int text_color_; //文字の色
	int font_handle_;//フォントハンドル

public:
	//  コンストラクタ(x,yは相対位置)
	TextFormatNode(const char* text, unsigned int text_color,int font_handle ,float x, float y);
	TextFormatNode(const char* text, unsigned int red, unsigned int green, unsigned int blue, int font_handle, float x, float y);

	//  セッター
	void SetText(const char* text); //文字
	void SetColor(unsigned int text_color); //色
	void SetColor(unsigned int red, unsigned int green, unsigned int blue);//色
	void SetFontHandle(int handle); //フォントハンドル

	//  オーバーライド系列
		//ロード
	void Load() override;
	//リリース
	void Release() override;
	//描画
	void Draw(int screen_handle, Camera* camera) override;

};


