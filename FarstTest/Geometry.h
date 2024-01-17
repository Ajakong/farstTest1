#pragma once

/// <summary>
/// �x�N�g���N���X
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
	/// �x�N�g���̑傫����Ԃ�
	/// </summary>
	/// <returns>�x�N�g���̑傫��</returns>
	float Length() const;
	/// <summary>
	/// �x�N�g���̑傫����2���Ԃ�
	/// </summary>
	/// <returns>�x�N�g���̑傫����2��</returns>
	float SqLength() const;
	/// <summary>
	/// ���̃x�N�g���𐳋K������
	/// </summary>
	void Normalize();
	/// <summary>
	/// ���̃x�N�g���𐳋K�������x�N�g����Ԃ�
	/// </summary>
	/// <returns>���K���ς݃x�N�g��</returns>
	Vector2 Normalized() const;
};

/// <summary>
/// ���ς�Ԃ��@A�EB
/// </summary>
/// <param name="lVal">���Ӓl</param>
/// <param name="rVal">�E�Ӓl</param>
/// <returns>���ϒl</returns>
float Dot(const Vector2& lVal, const Vector2& rVal);

// �ς��ƌ��ŕ�����₷���悤�ɕʖ�(���W)
using Position2 = Vector2;