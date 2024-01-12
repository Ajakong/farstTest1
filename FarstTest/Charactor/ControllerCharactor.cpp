#include "ControllerCharactor.h"
#include "../Input.h"

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase,int digits) :
	Charactor(fileManager, fileNameBase,digits )
{

}

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, int digits, const Position2& pos, float scale) :
	Charactor(fileManager, fileNameBase, digits, pos, scale)
{
	if (digits == 1)
	{
		std::string str = "walk";
		this->ChangeAnimation(str);
		this->SetOrigin(1);
	}
	else if (digits == 2)
	{
		std::string str = "adventurer-run-";
		this->ChangeAnimation(str);
		
	}
}

void ControllerCharactor::Operate(const Input& input)
{
	// ç∂âEÇÃÇ∆Ç±ÇÎÇ©ÇÁénÇﬂÇÈ
}

void ControllerCharactor::Move(const Vector2& vec)
{
	m_pos += vec;
}

void ControllerCharactor::Update(const Input& input)
{
	Charactor::Update();

}

void ControllerCharactor::Draw()
{
	Charactor::Draw();

}
