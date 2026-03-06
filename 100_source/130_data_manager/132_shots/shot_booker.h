//-----------------------------
// @name   shot_booker.h
// @brief  弾の発射予約 クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __SHOT_BOOKER_H__
#define __SHOT_BOOKER_H__

class ShotBooker
{
public:
	int size; //大きさ.
	int speed; //速度.
	int bool_time; //予約時間(ショットを変えるボーダー,直前との拍子差でとる).
	int type; //打つ種類
	int rooper; //個数(何回それをするか　,　SHOT_SPRIT　のみ分割個数を入れること).
	bool shooted; //発射済

};


#endif // !__SHOT_BOOKER_H__
