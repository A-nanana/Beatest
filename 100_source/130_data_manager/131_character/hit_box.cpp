#include "hit_box.h"
HitBox::HitBox(float x_start, float y_start, float x_size, float y_size, float lotate_rad)
{
	//回転の設定
	lotate_rad_ = lotate_rad;
	Matrix2 matrix;
	matrix.SetMatrixRotate(lotate_rad);
	//頂点設定
	point_[0].Set(x_start, y_start);
	point_[1].Set(x_start + x_size, y_start);
	point_[2].Set(x_start + x_size, y_start + y_size);
	point_[3].Set(x_start, y_start + y_size);
	for (int i = 0; i < hit_set::squair_point; i++) {
		point_[i].ChangeForMatrix(matrix);
	}

	//ベクトル計算
	for (int i = 0; i < hit_set::squair_point; i++) {
		vectol_[i].Set( point_[(i + 1) % hit_set::squair_point]);
		vectol_[i].Sub(point_[i]);
	}
}

void HitBox::SetToSize(int x, int y)
{
	//回転の設定
	Matrix2 matrix;
	matrix.SetMatrixRotate(lotate_rad_);
	//頂点設定
	point_[1].Set(point_[0].x_ + x, point_[0].y_);
	point_[2].Set(point_[0].x_ + x, point_[0].y_ + y);
	point_[3].Set(point_[0].x_, point_[0].y_ + y);
	for (int i = 0; i < hit_set::squair_point; i++) {
		point_[i].ChangeForMatrix(matrix);
	}

	//ベクトル計算
	for (int i = 0; i < hit_set::squair_point; i++) {
		vectol_[i].Set(point_[(i + 1) % hit_set::squair_point]);
		vectol_[i].Sub(point_[i]);
	}
}

bool HitBox::HitCheckToPoint(Vector2D* other)
{
	for (int i = 0; i < hit_set::squair_point; i++) {
		Vector3D to_point_(other->x_ - point_[i].x_, other->y_ - point_[i].y_, 0.0f);
		to_point_.Cross(vectol_[i]);
		//外積が0より大きいなら当たり判定の外
		if (to_point_.x_ > 0 || to_point_.y_ > 0 || to_point_.z_ > 0) {
			return false;
		}

	}
	return true;
}

bool HitBox::HitCheckToBox(HitBox* other)
{
	for (int i = 0; i < hit_set::squair_point; i++) {
		if (!HitCheckToPoint(&other->point_[i])) {
			return false;
		}
	}
	return true;
}
