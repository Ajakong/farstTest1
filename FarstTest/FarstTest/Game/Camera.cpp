#include "Camera.h"
#include<algorithm>
#include"../Application.h"
#include"Dxlib.h"

//ÉJÉÅÉâÇÃìÆÇØÇÈîÕàÕ
//0+windowWidth/2~stageWidth-windowWidth/2;

Camera::Camera()
{
	m_range.size = Application::GetInstance().GetWindowSize();
	m_range.pos = { static_cast<float>(m_range.size.w) / 0.5f,static_cast<float>(m_range.size.h) };
	m_stageSize = { 1280,480 };
}

void Camera::SetPos(const Position2& pos)
{
	m_range.pos.x = std::clamp(pos.x, static_cast<float>(m_range.size.w)* 0.5f,
							static_cast<float>(m_stageSize.w) - static_cast<float>(m_range.size.w) * 0.5f);
	m_range.pos.y = std::clamp(pos.y, static_cast<float>(m_range.size.h) * 0.5f,
		static_cast<float>(m_stageSize.h) - static_cast<float>(m_range.size.h) * 0.5f);

}

const Rect& Camera::GetRange() const
{
	return m_range;
}

int Rect::Left() const
{
	return static_cast<int>(pos.x - size.w / 2);
}

int Rect::Right() const
{
	return static_cast<int>(pos.x + size.w / 2);
}

int Rect::Top() const
{
	return static_cast<int>(pos.y - size.h / 2);
}

int Rect::Bottom() const
{
	return static_cast<int>(pos.y + size.h / 2);
}

void Rect::Draw(int color)
{
	DrawBoxAA(Left(), Top(), Right(), Bottom(), color, false, 2.0f);
}
