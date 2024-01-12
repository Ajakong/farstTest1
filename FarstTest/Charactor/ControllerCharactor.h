#pragma once
#include "Charactor.h"

class Input;

class ControllerCharactor : public Charactor
{

	using UpdateFunc_t = void(ControllerCharactor::*)(const Input);
public:
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, int digits);
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, int digits, const Position2& pos, float scale = 1.0f);

	void Operate(const Input& input);
	void Move(const Vector2& vec);

	virtual void Update(const Input& input);
	virtual void Draw();
};

