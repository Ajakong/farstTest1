#pragma once
#include "Charactor.h"

class Input;

class ControllerCharactor : public Charactor
{
public:
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase);
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, const Position2& pos, float scale = 1.0f);

	void Operate(const Input& input);
	void Move(const Vector2& vec);
};

