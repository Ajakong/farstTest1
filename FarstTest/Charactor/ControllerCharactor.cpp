#include "ControllerCharactor.h"
#include "../Input.h"

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase) :
	Charactor(fileManager, fileNameBase)
{
}

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, const Position2& pos, float scale) :
	Charactor(fileManager, fileNameBase, pos, scale)
{
}

void ControllerCharactor::Operate(const Input& input)
{
	// 左右のところから始める
}

void ControllerCharactor::Move(const Vector2& vec)
{
	m_pos += vec;
}
