//-----------------------------
// @name   score_manager.h
// @brief  スコア管理 クラス
// @auther A.namami
// @date   2026/3/10  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__

#include <string>

//------------------------------
// @name   ScoreData
// @brief  スコアデータ 構造体
// @memo   
//------------------------------
struct ScoreData{
	
	int score;//スコア
	int max_conbo;//最大コンボ
	int critical;//ギリギリの避け
	int avoiding;//次にギリギリの避け
};

//------------------------------
// @name   HitType
// @brief  判定結果のデータ 構造体
// @memo   
//------------------------------
enum HitType {
	k_critical,//クリティカル
	k_avoid,//避け
	k_miss,//当たった
	k_none,//何事もなく場外
};

//------------------------------
// @name   ScoreManager
// @brief  スコア管理 クラス
// @memo   エラー型が来た場合は-1で返します
//------------------------------
class ScoreManager
{
	static ScoreManager* instance_;//実体
	ScoreData score_;//スコアデータ
	int count_conbo_;//コンボカウンター
	int count_conbo_max_;//譜面コンボ数カウンター

//  コンストラクタ
	ScoreManager();
//  デストラクタ
	~ScoreManager() {};
public:
//  複製防止
	ScoreManager operator= (const ScoreManager&) = delete;
	ScoreManager& operator= (ScoreManager&) = delete;

//  インスタンスアクセス
	static ScoreManager* GetInstance();

//  更新
	void ComboUpdate(bool is_conbo);//コンボ
	void ScoreUpdate(HitType type);//スコア
	
//  表示用char切り替えゲッター
	std::string GetScore() { return std::to_string(score_.score); }; //スコア
	std::string GetMaxConbo() { return std::to_string(score_.max_conbo); }; //最大コンボ
	std::string GetNowConbo() { return std::to_string(count_conbo_); };//今のコンボ数

//  結果確定
	void ResultLock();

//  スコアリセット
	void Reset();


};


#endif // !__SCORE_MANAGER_H__
