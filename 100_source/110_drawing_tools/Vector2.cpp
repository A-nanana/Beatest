//-----------------------------
// @name   Vector2.cpp
// @brief  2次元ベクトル クラス
// @auther A.namami
// @date   2025(ゲーム数学の授業時)  新規作成
//		   2026/3/2 回転行列用のクラスを追加
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include"Vector2.h"
#include<iostream>

//数式系はメンバ変数もパブリックにすることもある

	//コンストラクタ
	Vector2D::Vector2D() {
		x_ = 0.0;
		y_ = 0.0;
	}
	Vector2D::Vector2D(double _x, double _y) {
		x_ = _x;
		y_ = _y;
	}
	//使い回し用リセット
	void Vector2D::Reset()
	{
		x_ = 0.0;
		y_ = 0.0;
	}
	//使い回し用一斉セット
	void Vector2D::Set(double _x, double _y)
	{
		x_ = _x;
		y_ = _y;
	}
	void Vector2D::Set(const Vector2D& other)
	{
		x_ = other.x_;
		y_ = other.y_;
	}
	//--------
	//和:核成分同士の足し算
	//--------

	Vector2D Vector2D::Add(double _x, double _y) {
		x_ += _x;
		y_ += _y;
		return { x_,y_ };
	}
	Vector2D Vector2D::Add(const Vector2D& other)
	{
		x_ += other.x_;
		y_ += other.y_;
		return { x_,y_ };
	}
	
	//--------
	//差;各成分同士の引き算
	//--------
	Vector2D Vector2D::Sub(double _x, double _y)
	{
		x_ -= _x;
		y_ -= _y;
		return { x_,y_ };


	}

	Vector2D Vector2D::Sub(const Vector2D& other)
	{
		x_ -= other.x_;
		y_ -= other.y_;
		return { x_,y_ };

	}
	
	//--------
	//スカラー倍
	//--------
	Vector2D Vector2D::Scale(const double scolor)
	{
		x_ *= scolor;
		y_ *= scolor;

		return { x_,y_ };
	}
	
	//--------
	//逆ベクトルを返却(計算なし)
	//--------
	Vector2D Vector2D::ReverseScale()
	{


		return { x_*(- 1),y_*(-1)};
	}
	//--------
	//ノルム出し(本体代入なし)
	//--------
	double Vector2D::Length()
	{   
		double kekka = sqrt(x_*x_ + y_*y_);
		

		return kekka;
	}
	//--------
	//内積.
	//--------
	double Vector2D::Dot(const Vector2D &_other) {
		
		return x_ * _other.x_ + y_ * _other.y_;
	}

	//--------
	//単位ベクトル出し(本体代入なし)
	//--------
	Vector2D Vector2D::PerLength1()
	{
		Vector2D kekka(x_, y_);
		const double len = Length();
		if (len > 0) {
			kekka.Scale(1.0 / len);
		}

		return kekka;
	}
	//--------
	//単位化
	//--------
	Vector2D Vector2D::Normalize()
	{
		const double len = Length();
		if (len > 0) {
			Scale(1.0 / len);
		}
		return {x_,y_};
	}

	//行列で変更
	Vector2D Vector2D::ChangeForMatrix(Matrix2 matrix_)
	{
		Vector2D last_(x_, y_);//直前のやつ
		x_ = last_.x_ * matrix_.matrix_[0][0] + last_.y_ * matrix_.matrix_[0][1];
		y_ = last_.x_ * matrix_.matrix_[1][0] + last_.y_ * matrix_.matrix_[1][1];
		return { x_,y_ };
	}

	//--------
	//図解デバック
	//--------
	void Vector2D::ZahyouDasi(void)
	{

		for (int y_l = 5; y_l >= -5; y_l--) {
			for (int x_l = -5; x_l <= 5; x_l++) {
				if (y_ >= y_l-0.5 && y_ < y_l + 0.5 && x_ >= x_l-0.5 && x_ < x_l + 0.5) {
					std::cout << " * ";
				}
				else if (y_l == 0 && x_l == 0) {
					std::cout << " . ";
				}
				else {  
					std::cout << "   ";

				}
			}
			std::cout << std::endl;
		}
	}

	//--------
	//デバック用表示
	//--------
	void Vector2D::Print() {
		std::cout << "( " << x_ << " , " << y_ << " )\n";
		std::cout << "長さ: " << Length() << " \n";
	}

//-----------------------------
// @name   Matrix2
// @brief  2次元用マトリクス
// @memo   セットしてから使うこと
//------------------------------

	Matrix2::Matrix2()
	{
		matrix_[0][0] = matrix_[1][1] = 1.0f;
		matrix_[0][1] = matrix_[1][0] = 0.0f;

	}

	void Matrix2::SetMatrixRotate(float rad)
	{
		matrix_[0][0] = matrix_[1][1] = cos(rad);
		matrix_[0][1] = -sin(rad);
		matrix_[1][0] = sin(rad);
	}

	double Dot(const Vector2D& _a, const Vector2D& _b)
	{
		return _a.x_ * _b.x_ + _a.y_ * _b.y_;

	}
