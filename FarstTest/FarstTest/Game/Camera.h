#pragma once
#include"../Geometry.h"
struct Rect;

class Camera
{
private:
	Position2 m_pos;
	Size m_stageSize;//�J�����̓�����͈�
	Rect m_range;//�J�����̌����Ă�͈�
public:
	Camera();
	/// <summary>
	/// �J�����̌��݈ʒu��ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(const Position2& pos);
	const Rect& GetRange()const;


};




