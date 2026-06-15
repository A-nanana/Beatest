//-----------------------------
// @name   maker.h
// @brief  譜面作成 クラス
// @auther A.namami
// @date   2026/6/8  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <random>
#include "maker.h"
#include "read_music.h"


bool Maker::Init()
{
    buffer_ = 0;
    buffer_count_ = 0;
    count_time_ = 0;//拍子間カウント
    bunkatu_ = 0;//チャンネルカウント
    sec_count_ = 0;//セクションカウント
    hakusuu_ = 4;
    return false;
}

bool Maker::SetData(int diff)
{
	//取り出し位置の乱数
	serch_time_ = new int[hakusuu_];//取り出しタイミング
	//配列初期化
	{
		for (int i = 0; i < hakusuu_; i++) {
			serch_time_[i] = i;
		}
	}
	//入れ替え
	{
		std::random_device seed;//入れ替え乱数
		std::mt19937 randomer(seed());//入れ替え乱数
		for (int i = 0; i < (diff * 2 + 1); i++) {
			int sub1, sub2;//計算補助
			int rands = randomer() % hakusuu_;//入れ替え位置
			sub1 = serch_time_[rands];
			sub2 = hakusuu_ - 1 - rands;//入れ替え先位置
			serch_time_[rands] = serch_time_[sub2];
			serch_time_[sub2] = sub1;
		}
	}
	return true;
}

bool Maker::GetTopData(WavData* datas, int tag_time)
{
	//データ解析
	for (int i = 0; i < datas->datas.size(); i++) {
		//バッファに加える
		buffer_ |= datas->datas[i] << (8 * buffer_count_);
		++buffer_count_;


		//集まったら出す
		if (buffer_count_ * 8 == datas->format.bitsPerSample) {

			//秒数頭なら記録する
			if (count_time_ == 0 && bunkatu_ == 0) {
				sec_top_.push_back((int)buffer_);
			}
			else if (count_time_ == 0 && bunkatu_ == 1) {
				sec_top_[sec_count_] += ((unsigned int)buffer_);
				++sec_count_;
			}
			memset(&buffer_, 0, sizeof(uint32_t));

			buffer_count_ = 0;

			++bunkatu_;
			if (bunkatu_ == datas->format.channels) {
				++count_time_;
			}
			//秒数末なら次に
			if (count_time_ == tag_time) {
				count_time_ = 0;
			}
			if (bunkatu_ >= datas->format.channels) {
				bunkatu_ = 0;
			}

		}


	}return true;
}

std::string* Maker::MakeHumen(WavData* datas, int bpm, int diff, int hakusuu, int tag_time)
{
	std::string* reslt = new std::string();
	Init();
	SetData(diff);
	GetTopData(datas, tag_time);

	//譜面変換
	for (int i = 0; i < sec_top_.size(); i++) {
		int checker = abs((sec_top_[i]) / 2 - 32768);
		int j;
		//乱数確認
		for (j = 0; j < diff; j++) {
			if (serch_time_[j] == i % hakusuu_) {
				break;
			}
		}
		//乱数に当てはまればこっち
		if (j < diff) {
			//音の大きさとタイミングで変更
			if (checker > 28000) {
				reslt->append("3");
			}
			else if (checker > 20000 && i % 2 == 0) 
			{
				reslt->append("4");
			}
			else if (i % diff == 0) {
				reslt->append("0");
			}
			else {
				reslt->append("1");

			}
		}
		else if (checker > 11000)//乱数外なら音の大きさ 
		{
			reslt->append("1");

		}
		else {
			reslt->append("0");


		}
		if (i % hakusuu_ == hakusuu_ - 1) //小節末は改行
		{
			reslt->append("\n");

		}
	}

    return reslt;
}
