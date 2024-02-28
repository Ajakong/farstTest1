#include "Actor.h"

Actor::Actor(FileManager& fileManager, const Camera& camera, const Position2& pos) :
	m_fileManager(fileManager),
	m_camera(camera),
	m_pos(pos)
{
}

Actor::~Actor()
{
}

void Actor::SetPosition(const Position2& pos)
{
	m_pos = pos;
}

const Position2& Actor::GetPosition()
{
	return m_pos;
	// TODO: return ステートメントをここに挿入します
}
