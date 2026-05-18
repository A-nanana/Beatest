//-----------------------------
// @name   score_manager.cpp
// @brief  スコア管理 クラス
// @auther A.namami
// @date   2026/3/10  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "score_manager.h"
#include "../133_music/music_manager.h"
#include "../../140_roading_from_other/file_roader.h"
#include "..\..\110_drawing_tools\defining.h"

//------------------------------
// @name   ScoreManager
// @brief  スコア管理 クラス
// @memo   エラー型が来た場合は-1で返します
//------------------------------

ScoreManager* ScoreManager::instance_ = nullptr;
//  コンストラクタ
ScoreManager::ScoreManager() {
	score_.max_conbo = window_setting::null_param;
	score_.score = window_setting::null_param;
	score_.critical = window_setting::null_param;
	score_.great = window_setting::null_param;
	score_.good = window_setting::null_param;
	score_.miss = window_setting::null_param;
	count_conbo_ = window_setting::null_param;
	count_conbo_max_ = window_setting::null_param;
}

//インスタンスアクセス
ScoreManager* ScoreManager::GetInstance() {
	if (instance_ == nullptr) {
		instance_ = new ScoreManager();
	}
	return instance_;
}

//更新
void ScoreManager::ComboUpdate(bool is_conbo)
{
	//コンボの成否
	if (is_conbo) {
		count_conbo_++;
	}
	else {
		//コンボは最高記録か
		if (score_.max_conbo < count_conbo_)
		{
			score_.max_conbo = count_conbo_;
		}

		//コンボリセット
		count_conbo_ = window_setting::null_param;
	}
	count_conbo_max_++;
}

void ScoreManager::ScoreUpdate(HitType type)
{
	//スコアが最大でなければ加算
	if (score_.score < score_set::conbo_max) {
		//当たり判定の結果で分岐
		switch (type)
		{
		case k_critical:
			score_.critical++;
			ComboUpdate(true);
			break;
		case k_great:
			score_.great++;
			ComboUpdate(true);
			break;
		case k_miss:
			score_.miss++;
			ComboUpdate(false);
			break;
		case k_none:
			score_.good++;
			break;
		case k_lazer_none:
			score_.critical++;
			break;
		default:
			break;
		}
	}
	//スコアが最大でなければ加算
	if (score_.score < score_set::score_max) {
		//当たり判定の結果で分岐
		switch (type)
		{
		case k_critical:
			score_.score += score_set::per_critical;
			break;
		case k_great:
			score_.score += score_set::per_avoiding;
			break;
		case k_none:
			score_.score += score_set::per_none;
			break;
		case k_lazer_none:
			score_.score += score_set::per_lazer;
			break;
		default:
			break;
		}
	}

}

//結果確定
void ScoreManager::ResultLock()
{
	//コンボは最高記録か
	if (score_.max_conbo < count_conbo_)
	{
		score_.max_conbo = count_conbo_;
	}
	//最大スコアか
	if (MusicManager::GetInstance()->GetMusicHighScore() < score_.score) {

		MusicManager::GetInstance()->SetHighScore(score_.score);
		FileRoader::GetInstance()->WriteScore(MusicManager::GetInstance()->GetMusicData());
		
	}

}

//リセット
void ScoreManager::Reset() {
	score_.max_conbo = window_setting::null_param;
	score_.score = window_setting::null_param;
	score_.critical = window_setting::null_param;
	score_.great = window_setting::null_param;
	score_.good = window_setting::null_param;
	score_.miss = window_setting::null_param;
	count_conbo_ = window_setting::null_param;
	count_conbo_max_ = window_setting::null_param;
}