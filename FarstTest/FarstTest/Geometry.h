#pragma once

struct Size
{
	int w;
	int h;
};

/// <summary>
/// ベクトルクラス
/// </summary>
struct Vector2
{
	float x;
	float y;
	
	Vector2 operator+(const Vector2& val) const;
	Vector2 operator-(const Vector2& val) const;
	Vector2 operator*(float scale) const;
	Vector2 operator/(float div) const;
	void operator+=(const Vector2& val);
	void operator-=(const Vector2& val);
	void operator*=(float scale);
	void operator/=(float div);
	bool operator==(const Vector2& val)const;
	/// <summary>
	/// ベクトルの大きさを返す
	/// </summary>
	/// <returns>ベクトルの大きさ</returns>
	float Length() const;
	/// <summary>
	/// ベクトルの大きさの2乗を返す
	/// </summary>
	/// <returns>ベクトルの大きさの2乗</returns>
	float SqLength() const;
	/// <summary>
	/// このベクトルを正規化する
	/// </summary>
	void Normalize();
	/// <summary>
	/// このベクトルを正規化したベクトルを返す
	/// </summary>
	/// <returns>正規化済みベクトル</returns>
	Vector2 Normalized() const;
};

/// <summary>
/// 内積を返す　A・B
/// </summary>
/// <param name="lVal">左辺値</param>
/// <param name="rVal">右辺値</param>
/// <returns>内積値</returns>
float Dot(const Vector2& lVal, const Vector2& rVal);

// ぱっと見で分かりやすいように別名(座標)
using Position2 = Vector2;

///矩形構造体
struct Rect
{
	Position2 pos;//矩形の中心
	Size size;
	/// <summary>
	/// 矩形の左位置Xを返す
	/// </summary>
	/// <returns>矩形の左位置X</returns>
	int Left()const;
	/// <summary>
	/// 矩形の右位置Xを返す
	/// </summary>
	/// <returns>矩形の右位置X</returns>
	int Right()const;
	/// <summary>
	/// 矩形の上位置Yを返す
	/// </summary>
	/// <returns>矩形の上位置Y</returns>
	int Top()const;
	/// <summary>
	/// 矩形の下位置Yを返す
	/// </summary>
	/// <returns>矩形の下位置Y</returns>
	int Bottom()const;

	/// <summary>
	/// デバッグ用関数:矩形を線で表示する
	/// </summary>
	void Draw(int color = 0xffffff);
};