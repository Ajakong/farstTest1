#pragma once
#include "Charactor.h"

class Input;

//制御できるキャラクター　
class ControllerCharactor : public Charactor
{

	using UpdateFunc_t = void(ControllerCharactor::*)(const Input);
public:
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, int digits);
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, int digits, const Position2& pos, float scale = 1.0f);

	
	void Move(const Vector2& vec);
	void SetPosition(const Position2& mov);
	virtual void Operate(const Input& input);
	virtual void Update();
	virtual void Draw();
};

