//-----------------------------
// @name   text_node.h
// @brief  文字ノード クラスの宣言部
// @auther A.namami
// @date   2026/2/17  新規作成
//		   2026/3/18  DrawStringをDrawFormatStringに変更
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------


#include "text_node.h"
#include "camera.h"

//  コンストラクタ(x,yは相対位置)
TextNode::TextNode(const char* text, unsigned int text_color, float x, float y)
{
	text_ = text;
	text_color_ = text_color;
	SetPosition(x, y);
}

TextNode::TextNode(const char* text, unsigned int red, unsigned int green, unsigned int blue, float x, float y)
{
	text_ = text;
	text_color_ = GetColor(red, green, blue);
	SetPosition(x, y);
}


//  セッター
void TextNode::SetText(const char* text)
{
	text_ = text;
}

void TextNode::SetColor(unsigned int text_color)
{
	text_color_ = text_color;
}

void TextNode::SetColor(unsigned int red, unsigned int green, unsigned int blue)
{
	text_color_ = GetColor(red, green, blue);
}

//ロード
void TextNode::Load()
{

}
//リリース
void TextNode::Release()
{
	text_.clear();
	text_color_ = NULL;
}
//描画
void TextNode::Draw(int screen_handle,Camera* camera)
{
	//カメラ内か
	if (camera->IsDraw(GetWorldPosition())) {
		DrawFormatString(camera->DrawPositionX(world_position_.x_), camera->DrawPositionY(world_position_.y_), text_color_, text_.c_str());
	}
}

//-----------------------------
// @name   FontSet
// @brief  フォント クラスの宣言部
// @memo   フォントの設計用
//         これを使って作ること
//------------------------------

//  コンストラクタ
FontSet::FontSet(const char* font_name, int size, int thick, int type)
{
	font_name_ = font_name;
	size_ = size;
	thick_ = thick;
	type_ = type;
	handle_ = NULL;
	Load();
}

FontSet::~FontSet()
{
	Release();
}

//セッター
void FontSet::SetFontName(const char* font_name)
{
	font_name_ = font_name;
}

void FontSet::SetFontSize(int size)
{
	size_ = size;
}

void FontSet::SetFontThick(int thick)
{
	thick_ = thick;
}

void FontSet::SetFontType(int type)
{
	type_ = type;
}

//  ゲッター
int FontSet::GetFontHandle()
{
	return handle_;
}

//ロード
void FontSet::Load() {
	//ハンドルの確認
	if (handle_ != NULL) {
		DeleteFontToHandle(handle_);
		handle_ = NULL;
	}
	handle_ = CreateFontToHandle(font_name_.c_str(), size_, thick_, type_);
}

//解放
void FontSet::Release() {
	//ハンドルの確認
	if (handle_ != NULL) {
		DeleteFontToHandle(handle_);
		handle_ = NULL;
	}
}


//-----------------------------
// @name   TextFormatNode
// @brief  文字ノード クラスの宣言部
// @memo   フォント指定ができるタイプ
//         事前に作ったものを使用すること
//------------------------------
TextFormatNode::TextFormatNode(const char* text, unsigned int text_color, int font_handle, float x, float y)
{
	text_ = text;
	text_color_ = text_color;
	font_handle_ = font_handle;
	SetPosition(x, y);
}

TextFormatNode::TextFormatNode(const char* text, unsigned int red, unsigned int green, unsigned int blue, int font_handle, float x, float y)
{
	text_ = text;
	text_color_ = GetColor(red, green, blue);
	font_handle_ = font_handle;
	SetPosition(x, y);
}

//  セッター
void TextFormatNode::SetText(const char* text)
{
	text_ = text;
}

void TextFormatNode::SetColor(unsigned int text_color)
{
	text_color_ = text_color;
}

void TextFormatNode::SetColor(unsigned int red, unsigned int green, unsigned int blue)
{
	text_color_ = GetColor(red, green, blue);
}

void TextFormatNode::SetFontHandle(int handle)
{
	font_handle_ = handle;
}

void TextFormatNode::Load()
{
}

void TextFormatNode::Release()
{
}

void TextFormatNode::Draw(int screen_handle,Camera* camera)
{
	DrawFormatStringToHandle(camera->DrawPositionX(world_position_.x_), camera->DrawPositionY(world_position_.y_), text_color_, font_handle_, text_.c_str());
}

