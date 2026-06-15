//-----------------------------
// @name   read_music.h
// @brief  曲分析 クラス
// @auther A.namami
// @date   2026/6/5  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#define DR_MP3_IMPLEMENTATION
#include "../../140_roading_from_other/dr_mp3.h"

#include "read_music.h"

WavData* ReadWav::ReadIt(FILE* file)
{
    //返り値
    WavData* data = new WavData();
	fread(&data->riff, sizeof(RiffChunk), 1, file);

	//RIFFタグでないならフォーマットエラー
	if (strncmp(data->riff.head.id, "RIFF", 4) != 0) {
		fclose(file);
		data->data_size = -1;
		return data;
	}
	//Waveファイルフォーマットでないなら読み込みできないので除外
	if (strncmp(data->riff.format, "WAVE", 4) != 0) {
		fclose(file);
		data->data_size = -1;

		return data;
	}

	ChunkHead chunk;
	unsigned long cu_pos = ftell(file); // ファイル現在地

	while (cu_pos < data->riff.head.size + sizeof(ChunkHead))
	{
		// 一つのChunkHeadを読み込む
		std::memset(&chunk, 0, sizeof(ChunkHead));
		fread(&chunk, sizeof(ChunkHead), 1, file);

		// Chunkのサイズが0より小さい場合エラーとする
		// （ファイルフォーマットが正しくない場合）
		if (chunk.size < 0) break;

		//fmtならフォーマットチャンクを読み込む
		if (strncmp(chunk.id, "fmt ", 4) == 0)
		{
			// Wave Format Chunkを読み込み
			fread(&data->format, minInt(chunk.size, (unsigned int)sizeof(WaveFileFormat)), 1, file);

			// 先頭6つの要素以外の要素があれば、そのデータを無視してカーソルを移動させる
			fseek(file, chunk.size - sizeof(WaveFileFormat), SEEK_CUR);
		}
		else if (strncmp(chunk.id, "data", 4) == 0) //データならWavデータを読み込む
		{
			// Waveのデータを読み込む
			for (int i = 0; i < chunk.size; i++) {
				std::uint8_t buffer;
				fread(&buffer, 1, 1, file);
				data->datas.push_back(buffer);
			}
			data->data_size = chunk.size;
		}
		else
		{
			// 認識できないChunkをSkipしてカーソルを移動させる
			fseek(file, chunk.size, SEEK_CUR);
		}
		cu_pos = ftell(file);   // 現在のファイル位置取得
	}

	// ファイルを閉じる
	fclose(file);

    return data;
}

WavData* ReadMp3::ReadIt(drmp3* file)
{
	WavData* get_data = new WavData();//返り値

	//全フレームをデコード
	drmp3_uint64 total_frame = drmp3_get_pcm_frame_count(file);
	drmp3_int16* res = (drmp3_int16*)malloc(sizeof(drmp3_int16) * total_frame * file->channels);
	int resframe = drmp3_read_pcm_frames_s16(file, total_frame, res);
	drmp3_uninit(file);

	//データ変換
	for (int i = 0; i < (total_frame * file->channels * sizeof(drmp3_int16) / sizeof(uint8_t)) / 2; i++) {
		get_data->datas.push_back((uint8_t)(res[i] & 0xFF));
		get_data->datas.push_back((uint8_t)((res[i] >> 8) & 0xFF));
	}
	get_data->format.audioFormat = 1;
	get_data->format.channels = file->channels;
	get_data->format.samplePerSecond = file->sampleRate;
	get_data->format.bitsPerSample = 16;
	get_data->format.blockAlign = file->channels * (get_data->format.bitsPerSample / sizeof(uint8_t));
	get_data->format.bytesPerSecond = file->sampleRate * get_data->format.blockAlign;
	
	get_data->data_size = total_frame * get_data->format.blockAlign;
	free(res);

	return get_data;
}
