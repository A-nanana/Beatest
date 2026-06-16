//-----------------------------
// @name   manager_tenplate.h
// @brief  マネージャーテンプレート クラス
// @auther A.namami
// @date   2026/6/5  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once
#include <mutex>
template <typename T>

class Singleton
{
	//複製防止措置
	Singleton operator= (const Singleton&) = delete;
	Singleton& operator= (Singleton&) = delete;

public: 
	
	//インスタンスアクセス
	static T* GetInstance() {
		static T instance_; //実体
	
		return &instance_;
	}

};
