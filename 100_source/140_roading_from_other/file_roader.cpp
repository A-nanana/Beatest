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
#include "..\110_drawing_tools\tool.h"
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
	std::string inser_msg_f = "SELECT * FROM " + table_name + " LEFT OUTER JOIN " + file_set::defficult_data_base_table
		+ " ON " + table_name + ".MusicKey =" + file_set::defficult_data_base_table + ".MusicKey" + " LEFT OUTER JOIN " + file_set::score_data_base_table
		+ " ON " + table_name + ".MusicKey =" + file_set::score_data_base_table + ".MusicKey;";
	sqlite3_stmt* stmt = NULL; //状態格納ハンドル.

	//確認できるか
	if (use_lib_
		&&(sqlite3_prepare_v2(db_,inser_msg_f.c_str(),inser_msg_f.size(),&stmt,NULL) != SQLITE_OK)) {
		use_lib_ = false;
		sqlite3_close(db_);
	}
	//ライブラリ使用確認
	if (use_lib_) {
		int r = window_setting::null_param;//行設定用
		//JOIN中
		while (SQLITE_ROW == (r = sqlite3_step(stmt))) {
			LineUp DBresult;// データ入れの箱
			//初期化関係
			DBresult.defficalt_flg_ = NULL;
			for (int i = 0;i < system_set::defficulter_max;i++) {
				DBresult.high_score[i] = std::nullopt;
			}

			DBresult.music_key = sqlite3_column_int(stmt, 0);
	

			//文字型に変換
			const unsigned char* name = sqlite3_column_text(stmt, 1);
			//存在確認
			if (name != NULL) {
				DBresult.title = ToShiftJis((const char*)name);
			}
			else DBresult.title = string_set::unknown;
			

			//今度は難易度情報の処理

			//それぞれの真偽値をとる
			if (sqlite3_column_int(stmt, 7) != 0) {
				DBresult.defficalt_flg_ |= system_set::k_music_easy;
			}
			if (sqlite3_column_int(stmt, 8) != 0) {
				DBresult.defficalt_flg_ |= system_set::k_music_nomal;
			}
			if (sqlite3_column_int(stmt, 9) != 0) {
				DBresult.defficalt_flg_ |= system_set::k_music_hard;
			}
			if (sqlite3_column_int(stmt, 10) != 0) {
				DBresult.defficalt_flg_ |= system_set::k_music_beyond;
			}

			//最後にスコア情報
			for (int i = 0;i < system_set::defficulter_max;i++) {
				DBresult.high_score[i] = sqlite3_column_int(stmt, 11 + i);
			}
			title->push_back(DBresult);
		};
		
		sqlite3_finalize(stmt);

			
		

	}
	if(!use_lib_) {
		//ポインタつくる
		std::ifstream lineup_p("200_resource/220_music/Lineup.txt");
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
	std::string file_name = file_set::music_data_file_pass + music_data->title_ + "/" + music_data->title_ + ".wav";
	music_data->handle_ = LoadSoundMem(file_name.c_str());
	//wavファイルでエラーならmp3に
	if (music_data->handle_ == -1) {
		std::string file_name = file_set::music_data_file_pass + music_data->title_ + "/" + music_data->title_ + ".mp3";
		music_data->handle_ = LoadSoundMem(file_name.c_str());
	}

	//プロパティ読み込み
	std::string table_name = file_set::music_data_base_table;//stringに変換
	std::string inser_msg = "select * from " + table_name + " WHERE MusicKey = ? ;"; //クエリ文
	sqlite3_stmt* stmt = NULL; //状態格納ハンドル.
	//確認できるか
	if (use_lib_
		&& (sqlite3_prepare_v2(db_, inser_msg.c_str(), inser_msg.size(), &stmt, NULL) != SQLITE_OK)) {
		use_lib_ = false;
		sqlite3_close(db_);
	}
	//ライブラリ使用確認
	if (use_lib_) {
		sqlite3_bind_int(stmt, 1, music_data->music_key_);

		//Sqliteが動く間は処理
		while (SQLITE_ROW == sqlite3_step(stmt) ){

			music_data->bpm_ = sqlite3_column_int(stmt, 2);

			music_data->time_ = sqlite3_column_int(stmt, 3);
			music_data->hyousi_ = sqlite3_column_int(stmt, 4);
		}
		sqlite3_finalize(stmt);

	}
	else {
		file_name = file_set::music_data_file_pass + music_data->title_ + "/propaty.txt";
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
	std::string table_name = file_set::score_data_base_table;//stringに変換
	std::string inser_msg = "update " + table_name + " set " + string_set::defficult[ChangeBitToNum(music_data.defficult)] + " = ? WHERE MusicKey = ? ;"; //クエリ文
	std::string inser_msg_2 = "insert into " + table_name + "(MusicKey ,"+ string_set::defficult[ChangeBitToNum(music_data.defficult)]  +") values( ? , ? );"; //クエリ文
	
	sqlite3_stmt* stmt = NULL; //状態格納ハンドル.
	//確認できるか
	if (use_lib_
		&& (sqlite3_prepare_v2(db_, inser_msg.c_str(), inser_msg.size(), &stmt, NULL) != SQLITE_OK)) {
	}
	else {
		sqlite3_bind_int(stmt, 1, music_data.high_score_);
		sqlite3_bind_int(stmt, 2, music_data.music_key_);

		//処理確認用
		int r = NULL;
		//Sqliteが動く間は処理
		while (SQLITE_ROW == (r = sqlite3_step(stmt))) {

		}
		//存在の確認
		if (r != NULL) {

			sqlite3_finalize(stmt);
		}
		return;
	}
	
	//文章確認
	if (use_lib_
		&& (sqlite3_prepare_v2(db_, inser_msg_2.c_str(), inser_msg_2.size(), &stmt, NULL) != SQLITE_OK)) {
		use_lib_ = false;
		sqlite3_close(db_);
		return;
	}
	//ここまできた場合そもそもデータがないので挿入する
	//ライブラリ使用確認
	if (use_lib_) {
		sqlite3_bind_int(stmt, 2, music_data.high_score_);
		sqlite3_bind_int(stmt, 1, music_data.music_key_);

		//処理確認用
		int r = NULL;
		//Sqliteが動く間は処理
		while (SQLITE_ROW == (r = sqlite3_step(stmt))) {

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
	std::string file_name = file_set::music_data_file_pass + title + "/" + string_set::defficult[music_data.defficult] + ".txt";
	
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
	bool is_lazer_bottom = false; //レーザーのトップ判定
	int lazer_top_time = NULL; //レーザーのトップの時間

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
					float in_time = (((setu + (float)j / retu) + 1.0f) * music_data.hyousi_ ); //時間

					booked.bool_time = in_time * music_data.ms_per_hyousi_;//差分時間で予約
					booked.type = system_set::k_enemy_nomal;

					booker->push_back(booked);
				}
				else if (humen_2[i - retu + j] == '3') //全体に撒く
				{
					float in_time = (((setu + (float)j / retu) + 1.0f) * music_data.hyousi_ ); //時間

					booked.bool_time = in_time * music_data.ms_per_hyousi_;
					booked.type = system_set::k_enemy_all_renge;
					//角度計算
					booked.rooper = M_PI * 2/ system_set::angle_per_time;

					booker->push_back(booked);
				}
				else if (humen_2[i - retu + j] == '4') //時間差でまく
				{
					float in_time = (((setu + (float)j / retu) + 1.0f) * music_data.hyousi_); //時間

					booked.bool_time = in_time * music_data.ms_per_hyousi_;
					booked.type = system_set::k_enemy_later_renge;
					//角度計算
					booked.rooper = system_set::shot_later_roop_param;

					booker->push_back(booked);
				}
				else if (humen_2[i - retu + j] == '5') //レーザー
				{
					float in_time = (((setu + (float)j / retu) + 1.0f) * music_data.hyousi_); //時間
					
					//偶数カウントならレーザーの終了端
					if (is_lazer_bottom) {
						booked.bool_time = lazer_top_time - music_data.ms_per_hyousi_;
						booked.speed =	in_time * music_data.ms_per_hyousi_ - lazer_top_time;
						booked.type = system_set::k_enemy_lazer;
						//角度計算
						booked.rooper = system_set::shot_later_roop_param;
						booker->push_back(booked);
						is_lazer_bottom ^= 1;

					}
					else {
						lazer_top_time = in_time * music_data.ms_per_hyousi_;
						is_lazer_bottom ^= 1;
					}
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
	//もしレーザーが残っているなら処理


	humen_p.close();

	return booker;
}

void FileRoader::RoadSyutten(std::string& syutten, const char* file_name)
{
	//ファイル読み込み
	std::ifstream file_p(file_name, std::ios::binary);

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

