//-----------------------------
// @name   file_roader.h
// @brief  ファイル読み込み クラス
// @auther A.namami
// @date   2026/3/6  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __FILE_ROADER_H__
#define __FILE_ROADER_H__

#include <vector>
#include <string>
#include "./sqlite3.h" 


struct MusicData;
struct LineUp;
class ShotBooker;

//-----------------------------
// @name   FileRoader
// @brief  ゲームファイル読み込み
// @memo   
//------------------------------
class FileRoader
{
	static FileRoader* roader_; //インスタンス確認用
	bool use_lib_;//sqlite3を使用できるか
	sqlite3* db_;//データベース
	char* err_message_;//エラーメッセージ

//  コンストラクタ
	FileRoader();
//  デストラクタ
	~FileRoader();
//  コールバック関数
	static int CallbackTableCheck(void* param, int col_int, char** row_text, char** col_name);
public:
//  複製防止
	FileRoader operator= (const FileRoader&) = delete;
	FileRoader& operator= (FileRoader&) = delete;

	//インスタンスアクセス
	static FileRoader* GetInstance();
	//ラインナップ読み込み
	void RoadLineup(std::vector<LineUp>* title);
	//曲読み込み
	void RoadMusic(MusicData* music_data);
	//曲データ書き込み
	bool WriteData(MusicData* write_data, std::uint8_t flg);

	//スコア書き込み
	void WriteScore(const MusicData& music_data);

	//SE読み込み
	int RoadSe(int se_type);
	//bgm読み込み
	int RoadBgmDef();

	//譜面読み込み
	std::vector<ShotBooker>* RoadHumen(const MusicData& music_data);

	//文章読み込み
	void RoadTxt(std::string& txt, const char* file_name);
	
	//データベースが起動しているか
	bool CanUseDb() { return use_lib_; };

};


#endif // !__FILE_ROADER_H__
