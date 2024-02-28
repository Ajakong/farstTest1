#pragma once
#include"../Geometry.h"
struct Rect;

class Camera
{
private:
	Position2 m_pos;
	Size m_stageSize;//カメラの動ける範囲
	Rect m_range;//カメラの見えてる範囲
public:
	Camera();
	/// <summary>
	/// カメラの現在位置を設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(const Position2& pos);
	const Rect& GetRange()const;


};




