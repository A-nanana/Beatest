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

class MusicData;
class ShotBooker;
class FileRoader
{
	static FileRoader* roader_; //インスタンス確認用

//  コンストラクタ
	FileRoader();
//  デストラクタ
	~FileRoader();

public:
	//インスタンスアクセス
	static FileRoader* GetInstance();
	//ラインナップ読み込み
	void RoadLineup(std::vector<std::string>* title);
	//曲読み込み
	void RoadMusic(MusicData* music_data);
	//譜面読み込み
	std::vector<ShotBooker>* RoadHumen(const MusicData& music_data);
};

#endif // !__FILE_ROADER_H__
