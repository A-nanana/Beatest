//-----------------------------
// @name   file_roader.cpp
// @brief  ファイル読み込み クラス
// @auther A.namami
// @date   2026/3/6  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <fstream>
#include <iostream>
#include <functional>
#include <iterator>
#include "DxLib.h"
// SQLite用ヘッダー
#include "sqlite3.h" 
// ソースと同じ場所にあるライブラリの読み込み指定   
#pragma comment(lib, "sqlite3.lib")

#include "..\130_data_manager\133_music\music_manager.h"
#include "..\130_data_manager\132_shots\shot_booker.h"
#include "..\110_drawing_tools\defining.h"
#include "file_roader.h"

FileRoader* FileRoader::roader_ = nullptr;


int FileRoader::CallbackTableCheck(void* param, int col_int, char** row_text, char** col_name)
{
	//atoi関数を利用して先頭の文字を数に変換
	*(int*)param = atoi(row_text[0]);
	return 0;
}

FileRoader::FileRoader()
{
	db_ = nullptr;
	int count = 0;//データベースのカウント
	//Sqlite3を起動できるか
	if (sqlite3_open(file_set::music_data_base_pass, &db_) != SQLITE_OK) {
		use_lib_ = false;
		sqlite3_close(db_);
		return;
	}
	std::string table_name = file_set::music_data_base_table;//stringに変換
	std::string qel_text = "select count(*) from sqlite_master where type= 'table' and name='" + table_name + "'; ";//命令文
	//テーブルが確認できるか
	if (sqlite3_exec(db_, qel_text.c_str(), CallbackTableCheck, (void*)(&count), &err_message_) != SQLITE_OK) {
		use_lib_ = false;
		sqlite3_close(db_);
		return;
	}
	//テーブルが存在するか
	if (count  < 0) {
		use_lib_ = false;
		sqlite3_close(db_);
		return;
	}
	use_lib_ = true;
}

FileRoader::~FileRoader()
{
	if (use_lib_ = true) {
		sqlite3_close(db_);
	}
	use_lib_ = false;

}


FileRoader* FileRoader::GetInstance() {
	//インスタンスの確認
	if (roader_ == nullptr) {
		roader_ = new FileRoader();
	}
	return roader_;
}

void FileRoader::RoadLineup(std::vector<LineUp>* title)
{
	std::string table_name = file_set::music_data_base_table;//stringに変換
	std::string inser_msg = "select * from "+ table_name +" ;"; //クエリ文
	LineUp DBresult;// データ入れの箱
	sqlite3_stmt* stmt = NULL; //状態格納ハンドル.

	//確認できるか
	if (use_lib_
		&&(sqlite3_prepare_v2(db_,inser_msg.c_str(),inser_msg.size(),&stmt,NULL) != SQLITE_OK)) {
		use_lib_ = false;
		sqlite3_close(db_);
	}
	//ライブラリ使用確認
	if (use_lib_) {
		int r = window_setting::null_param;//行設定用
		//Sqliteが動く間の処理
		while (SQLITE_ROW ==(r = sqlite3_step(stmt)))
		{
			//文字型に変換
			const unsigned char* name = sqlite3_column_text(stmt, 0);
			//存在確認
			if (name != NULL) {
				DBresult.title = std::string((char*)name);
			}
			else DBresult.title = string_set::unknown;
			DBresult.high_score = sqlite3_column_int(stmt, 4);

			title->push_back(DBresult);
		}
		sqlite3_finalize(stmt);

	}
	else {
		//ポインタつくる
		std::ifstream lineup_p("200_resource\\music\\Lineup.txt");
		//ファイルが開くか
		if (lineup_p.is_open()) {
			std::string name;
			//取得できる間繰り返す
			while (std::getline(lineup_p, name)) {
				title->push_back({ name ,NULL});
			}
		}

		lineup_p.close();
	}
}

void FileRoader::RoadMusic(MusicData* music_data)
{
	//曲ハンドル
	std::string file_name = "200_resource\\music\\" + music_data->title_ + "\\" + music_data->title_ + ".wav";
	music_data->handle_ = LoadSoundMem(file_name.c_str());
	//wavファイルでエラーならmp3に
	if (music_data->handle_ == -1) {
		std::string file_name = "200_resource\\music\\" + music_data->title_ + "\\" + music_data->title_ + ".mp3";
		music_data->handle_ = LoadSoundMem(file_name.c_str());
	}

	//プロパティ読み込み
	std::string table_name = file_set::music_data_base_table;//stringに変換
	std::string inser_msg = "select * from " + table_name + " WHERE Title = ? ;"; //クエリ文
	sqlite3_stmt* stmt = NULL; //状態格納ハンドル.
	//確認できるか
	if (use_lib_
		&& (sqlite3_prepare_v2(db_, inser_msg.c_str(), inser_msg.size(), &stmt, NULL) != SQLITE_OK)) {
		use_lib_ = false;
		sqlite3_close(db_);
	}
	//ライブラリ使用確認
	if (use_lib_) {
		sqlite3_bind_text(stmt, 1, music_data->title_.c_str(), -1, SQLITE_TRANSIENT);

		//Sqliteが動く間は処理
		while (SQLITE_ROW == sqlite3_step(stmt) ){

			music_data->bpm_ = sqlite3_column_int(stmt, 1);

			music_data->time_ = sqlite3_column_int(stmt, 2);
			music_data->hyousi_ = sqlite3_column_int(stmt, 3);
			music_data->high_score_ = sqlite3_column_int(stmt, 4);
		}
		sqlite3_finalize(stmt);

	}
	else {
		file_name = "200_resource\\music\\" + music_data->title_ + "\\propaty.txt";
		std::ifstream propaty_p(file_name.c_str());
		if (propaty_p.is_open()) {
			propaty_p >> music_data->bpm_;
			propaty_p >> music_data->time_;
			propaty_p >> music_data->hyousi_;
		}

		propaty_p.close();
	}
	//1拍当たりの秒数計算
	music_data->ms_per_hyousi_ = system_set::ms_per_s * 60.0f / music_data->bpm_;
}

void FileRoader::WriteScore(const MusicData& music_data)
{
	//プロパティ読み込み
	std::string table_name = file_set::music_data_base_table;//stringに変換
	std::string inser_msg = "update " + table_name + " set HighScore = ? WHERE Title = ? ;"; //クエリ文
	sqlite3_stmt* stmt = NULL; //状態格納ハンドル.
	//確認できるか
	if (use_lib_
		&& (sqlite3_prepare_v2(db_, inser_msg.c_str(), inser_msg.size(), &stmt, NULL) != SQLITE_OK)) {
		use_lib_ = false;
		sqlite3_close(db_);
		return;
	}
	//ライブラリ使用確認
	if (use_lib_) {
		sqlite3_bind_int(stmt, 1, music_data.high_score_);
		sqlite3_bind_text(stmt, 2, music_data.title_.c_str(), -1, SQLITE_TRANSIENT);

		//Sqliteが動く間は処理
		while (SQLITE_ROW == sqlite3_step(stmt)) {

		}
		sqlite3_finalize(stmt);

	}
	
}

int FileRoader::RoadSe(int se_type)
{
	switch (se_type)
	{
	case k_play_critical:
		return LoadSoundMem(file_set::critical_se);
	case k_select:
		return LoadSoundMem(file_set::cursol_se);
	default:
		break;
	}
	return -1;
}

int FileRoader::RoadBgmDef()
{
	return LoadSoundMem(file_set::bgm_data_pass);
}

std::vector<ShotBooker>* FileRoader::RoadHumen(const MusicData& music_data)
{
	//ポインタつくる
	std::string title = music_data.title_;
	std::string file_name = "200_resource\\music\\" + title + "\\humen.txt";
	
	std::ifstream humen_p(file_name.c_str());
	//譜面
	std::string humen_2;
	//デフォルト
	ShotBooker booked_def = { 8,system_set::shot_speed_def , 3,0, 1, false };
	
	//返り値
	std::vector<ShotBooker>* booker = new std::vector<ShotBooker>();

	//譜面あける
	if (humen_p.is_open()) {
		char pt;
		while (humen_p.get(pt)) {
			humen_2.push_back(pt);
		}
		humen_p.close();
	}

	//譜面変換する
	int retu = 0;//ファイルの列
	int setu = 0;//曲の節数
	int i = 0;//ループカウント

	while (humen_2.size() > i) {
		switch (humen_2[i])
		{
		case  '\0': break;
		case '\n':
			//タイミング調整をば

			//カウント調整

			for (int j = 0; j <= retu; j++) {
				ShotBooker booked = booked_def;//予約カード

				if (humen_2[i - retu + j] == '1') //通常
				{
					float in_time = (float)(((setu + j / retu) + 1.0f) * music_data.hyousi_ * music_data.ms_per_hyousi_); //時間

					booked.bool_time = in_time;//差分時間で予約
					booked.type = system_set::k_enemy_nomal;

					booker->push_back(booked);
				}
				else if (humen_2[i - retu + j] == '3') //全体に撒く
				{
					float in_time = (float)(((setu + j / retu) + 1.0f) * music_data.hyousi_ * music_data.ms_per_hyousi_); //時間

					booked.bool_time = in_time;
					booked.type = system_set::k_enemy_all_renge;
					//角度計算
					booked.rooper = M_PI * 2/ system_set::angle_per_time;

					booker->push_back(booked);
				}
			}
			setu++;
			retu = 0;
			

			break;

			//インクリメント
		default:

			retu++;
			break;
		}

		i++;

	}
	

	humen_p.close();

	return booker;
}

void FileRoader::RoadSyutten(std::string& syutten)
{
	//ファイル読み込み
	std::ifstream file_p(file_set::syutten_memo, std::ios::binary);

	//ファイルを開いているか
	if (!file_p.is_open()) {
		return;
	}

	//ファイルから取り出す
	std::istreambuf_iterator<char> top(file_p.rdbuf());//はじめ
	std::istreambuf_iterator<char> last;//おわり
	//一気に初期化
	syutten = std::string(top, last);

	//終了
	file_p.close();

}
