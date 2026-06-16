//-----------------------------
// @name   add_music_scene.h
// @brief  描画基礎 クラス
// @auther A.namami
// @date   2026/6/11  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once
#include <future>
#include <vector>
#include "../110_drawing_tools/scene.h"
#include "../110_drawing_tools/node.h"
#include "../130_data_manager/133_music/data_manager.h"

//------------------------------
//ファイル名入力
//------------------------------
class FileInScene:public Scene
{
protected:
	Camera* camera_;//カメラ
	Node* root_;//UI根ノード
	Scene* next_;//次のスクリーン待ち
	int input_handle_;//入力ハンドル

public:
	void Init() override;//初期化
	void SetUp() override;//設定
	void Contact() ;//入力確認
	Scene* Update(float delta_time) override;//更新
	void Draw(int window_handle) override;//描画
	void Finalize();
};


//------------------------------
//待機シーン
//------------------------------
class WaitScene :public Scene
{
protected:
	Camera* camera_;//カメラ
	Node* root_;//UI根ノード
	Scene* next_;//次のスクリーン待ち

	std::vector<std::string> show_text_;//表示
public:
	WaitScene(std::vector<std::string> texts);
	void Init() override;//初期化
	void SetUp() override;//設定
	void Contact() {};//入力確認
	Scene* Update(float delta_time) override;//更新
	void Draw(int window_handle) override;//描画
	void Finalize();
};


//------------------------------
//変換内容入力シーン
//------------------------------
class InputDataScene :public Scene
{
public:
	//状況で変化
	enum Fase {
		k_input_bpm,//bpm
		k_input_hakusuu,//拍数
		k_max
	};
protected:
	Camera* camera_;//カメラ
	Node* root_[k_max];//UI根ノード
	Scene* next_;//次のスクリーン待ち
	
	int fase_;//状況管理
	int input_handle_;//入力管理ハンドル
	MusicMakerWant* input_data_;//入力データ

public:
	void Init() override;//初期化
	void SetUp() override;//設定
	void Contact();//入力確認
	Scene* Update(float delta_time) override;//更新
	void Draw(int window_handle) override;//描画
	void Finalize();
};


//------------------------------
//終了シーン
//------------------------------
class EndScene :public Scene
{
protected:
	Camera* camera_;//カメラ
	Node* root_;//UI根ノード
	Scene* next_;//次のスクリーン待ち
public:
	void Init() override;//初期化
	void SetUp() override;//設定
	void Contact();//入力確認
	Scene* Update(float delta_time) override;//更新
	void Draw(int window_handle) override;//描画
	void Finalize();
};


//------------------------------
//待機シーン派生
//------------------------------
class WaitForReadScene :public WaitScene
{
protected:
	std::future<int> updata_sub_thred_;//サブスレッド

public:
	WaitForReadScene() :WaitScene({ "Wait For Reading","読込中......" }) {};
	void Init() override;//初期化

	void Contact();//入力確認
	Scene* Update(float delta_time) override;//更新
};

class WaitForWriteScene : public WaitScene 
{
protected:
	
	std::future<int> updata_sub_thred_;//サブスレッド

public:
	WaitForWriteScene() :WaitScene({ "Wait For Writing","書込中......" }) {};
	void Init() override;//初期化

	void Contact();//入力確認
	Scene* Update(float delta_time) override;//更新
};

class ErrScene:public WaitScene
{
	Node* root_;//UI根ノード
	Scene* next_;//次のスクリーン待ち

	int err_nun_;
public:
	enum ErrId {
		k_input_err,//入力エラー
		k_read_err,//読込エラー
		k_write_err,//書き込みエラー
	};
	ErrScene(int err_nun) :err_nun_(err_nun),WaitScene({ "エラーが発生しました"}) {};

	void Init() override;//初期化
	void Contact();//入力確認
	Scene* Update(float delta_time) override;//更新
};