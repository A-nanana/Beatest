//-----------------------------
// @name   shot_object.h
// @brief  弾オブジェクト クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __SHOT_OBJECT_H__
#define __SHOT_OBJECT_H__

#include "..\..\110_drawing_tools\Vector2.h"
#include "..\131_character\object_common.h"
//-----------------------------
// @name   ShotObject
// @brief  通常弾
// @memo   
//------------------------------
class ShotObject:public ObjectCommon
{
protected:
	float speed_size_;//速度ベクトルの長さ
	int type_;//タイプデータ
	Vector2D target_;//対象方向
	bool used_; //有効か
public:
//  コンストラクタ
	ShotObject(const int graph_handle, float x, float y, float speed, float angle, Vector2D target, int type) ;
	ShotObject(const char* graph_, float x, float y, float speed, float angle,Vector2D target, int type);
//  デストラクタ
	~ShotObject();

//  ワールド座標で見た端を返す
	//左端を返す
	int XLeft(void);
	// XLeftの右端版
	int XRight(void);

	//上端を返す
	int YTop(void);
	//YTop 下端版
	int YBottom(void);

	//タイプを取得する
	int GetType() { return type_; }

	//有効か返す
	bool IsUsed() { return used_; };
	//有効かの切り替え
	void ChangeUsed() { used_ = false; };

	//ロード
	void Load() override;
	//更新(更新するときの時間)
	void Update(float delta_time)override;
	//解放
	void Release() override;
	
	
};

//-----------------------------
// @name   LongShot
// @brief  ビーム弾
// @memo   
//------------------------------
class LongShot :public ShotObject {
protected:
	int pre_count_;//表示前カウント
	int inner_count_;//表示カウント
	float extender_; //専用のx拡大率
public:
	//  コンストラクタ
	LongShot(const int graph_handle, float x, float y, float keep, float angle, Vector2D target, int type) ;
	LongShot(const  char* graph_, float x, float y, float keep, float angle, Vector2D target, int type);
	//  デストラクタ
	~LongShot() {};

	//位置計算が替わるので使用
	void SetWorldPosition();
	//有効かの切り替え(判定しないようにする)
	void ChangeUsed() { };

	//更新(更新するときの時間)
	void Update(float delta_time)override;
	//ロード
	void Load() override;
	//描画
	void Draw(int screen_handle, Camera* camera) override;
	//解放
	void Release() override;
};

#endif // !__SHOT_OBJECT_H__


