//-----------------------------
// @name   chanks.h
// @brief  Wavデータ クラス
// @auther A.namami
// @date   2026/6/4  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once
#include <iostream>
#include <vector>
//Wavファイルチャンク

//Wavファイルの1チャンク
typedef struct _chunk
{
	char id[4];
	int size;
} ChunkHead;

//頭にあるriffチャンク
typedef struct _riffChunk {
	ChunkHead head;
	char format[4];
}RiffChunk;

//次にあるらしいWavフォーマット
typedef struct _wavFmt
{
	short audioFormat;
	short channels;
	int samplePerSecond;
	int bytesPerSecond;
	short blockAlign;
	short bitsPerSample;
} WaveFileFormat;

typedef struct _wavFmtChunk
{
	ChunkHead chunk;
	WaveFileFormat format;
} WaveFormatChunk;



typedef struct _wav_data {
	RiffChunk riff;//RIFFチャンク

	WaveFileFormat format;//フォーマットチャンク
	unsigned int data_size;//データサイズ
	std::vector<uint8_t> datas;//実データ

}WavData;

//時間管理用
class Time {
public:
	int sec_;//秒
	int min_;//分
	int hour_;//時間
	
	Time();
	Time(int sec);
	void ChangeTime(int sec);
};

//小さい方を返す
int minInt(int a, int b);