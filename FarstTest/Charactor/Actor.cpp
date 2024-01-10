#include "Actor.h"

Actor::Actor(FileManager& fileManager, const Position2& pos) :
	m_fileManager(fileManager),
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
