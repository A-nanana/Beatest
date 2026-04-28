//-----------------------------
// @name   Vector2.h
// @brief  2次元ベクトル クラスの宣言部
// @auther A.namami
// @date   2025(ゲーム数学の授業時)  新規作成
//		   2026/3/2 回転行列用のクラスを追加
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once
//-----------------------------
// @name   Matrix2
// @brief  2次元用マトリクス
// @memo   セットしてから使うこと
//------------------------------
class Matrix2 {
public:
	float matrix_[2][2]; //2次元のマトリクス

	//コンストラクタ
	Matrix2();
	//回転行列の設定
	void SetMatrixRotate(float rad);
};


//数式系はメンバ変数もパブリックにすることもある
class Vector2D {
public:
	double x_, y_;
	//コンストラクタ
	Vector2D();
	Vector2D(double _x, double _y);
	//デバック用表示
	void Print();
	//使いまわし用リセット
	void Reset();
	//使い回し用一斉セット
	void Set(double _x, double _y);
	void Set(const Vector2D& other);

	//和
	Vector2D Add(double _x, double _y);
	Vector2D Add(const Vector2D& other);


	//差
	Vector2D Sub(double _x, double _y);
	Vector2D Sub(const Vector2D& other);

	//スカラー倍
	Vector2D Scale(const double scolor);


	//逆ベクトル取り出し専用(計算なし)
	Vector2D ReverseScale();
	//ノルム計算
	double Length();
	double Length_2zyou() { return x_ * x_ + y_ * y_; };
	//簡易内積計算
	double Dot(const Vector2D& _other);


	//単位ベクトル出し
	Vector2D PerLength1();
	//単位化(こっちは本体代入する)
	Vector2D Normalize();

	//行列で計算
	Vector2D ChangeForMatrix(const Matrix2 matrix_);

	//座標を図解
	void ZahyouDasi(void);

	//型変換
	operator int()const { return int(); };
	operator int() { return int(); };
};
