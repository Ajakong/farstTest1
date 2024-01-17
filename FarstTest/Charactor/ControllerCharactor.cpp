#include "ControllerCharactor.h"
#include "../Input.h"

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase,int digits) :
	Charactor(fileManager, fileNameBase,digits )
{
	/*if (digits == 1)
	{
		std::string str = "walk";
		this->ChangeAnimation(str);
		this->SetOrigin(1);
	}
	else if (digits == 2)
	{
		std::string str = "adventurer-run-";
		this->ChangeAnimation(str);

	}*/
}

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, int digits, const Position2& pos, float scale) :
	Charactor(fileManager, fileNameBase, digits, pos, scale)
{
	/*if (digits == 1)
	{
		std::string str = "walk";
		this->ChangeAnimation(str);
		this->SetOrigin(1);
	}
	else if (digits == 2)
	{
		std::string str = "adventurer-run-";
		this->ChangeAnimation(str);
		
	}*/
}


void ControllerCharactor::Move(const Vector2& vec)
{
	m_pos += vec;
}

void ControllerCharactor::SetPosition(const Position2& mov)
{
	 
}

void ControllerCharactor::Operate(const Input& input)
{
	if (input.IsTriggered("jump"))
	{
		if (m_digits == 2)
		{
			this->ChangeAnimation("adventurer-jump-");
		}
		else if (m_digits = 1)
		{
			this->ChangeAnimation("jump");
		}
	}
	if (input.IsTriggered("attack"))
	{
		if (m_digits == 2)
		{
			this->ChangeAnimation("adventurer-attack1-");
			//this->SetAnimationSpeed(5);
		}
		else if (m_digits = 1)
		{
			this->ChangeAnimation("punch");
			//this->SetAnimationSpeed(5);
		}
	}

}

void ControllerCharactor::Update()
{
	Charactor::Update();
}

void ControllerCharactor::Draw()
{
	Charactor::Draw();

}
