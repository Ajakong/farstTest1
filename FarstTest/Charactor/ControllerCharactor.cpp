#include "ControllerCharactor.h"
#include "../Input.h"
#include"../Application.h"


namespace
{
	float jump_speed = -10.0f;
	int ground_line = 400;
}



void ControllerCharactor::NeutralUpdate()
{
	if (m_currentInput.IsTriggered("jump"))
	{
		Jump();
	}
}

void ControllerCharactor::JumpUpdate()
{
	m_updateFunc = &ControllerCharactor::AerialUpdate;
}

void ControllerCharactor::AerialUpdate()
{
	m_vel.y += Application::GetInstance().GetGravity();
	m_pos += m_vel;
	if (m_vel.y - Application::GetInstance().GetGravity() <= 0.0f)
	{
		switch (m_type)
		{
		case PlayerType::hero:
			ChangeAnimation("adventurer-fall-");
		case PlayerType::monk:
			ChangeAnimation("fall");
	
		}
		m_updateFunc = &ControllerCharactor::FallUpdate;
	}
}
void ControllerCharactor::LandingUpdate()
{
}
void ControllerCharactor::FallUpdate()
{
	if (CheckGround())
	{
	
		m_vel.y = 0;
		m_pos.y = ground_line;
		switch (m_type)
		{
		case PlayerType::hero:
			this->ChangeAnimation("adventurer-idle-");
			//this->SetAnimationSpeed(5);
			break;

		case PlayerType::monk:
			this->ChangeAnimation("idle");
			//this->SetAnimationSpeed(5);
			break;
		}
		
	}
}

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, PlayerType type, int digits) :
	Charactor(fileManager, fileNameBase,digits ),
	m_type(type)
{
	if (m_type==PlayerType::monk)
	{
		std::string str = "walk";
		this->ChangeAnimation(str);
		this->SetOrigin(1);
	}
	else if (m_type == PlayerType::hero)
	{
		std::string str = "adventurer-run-";
		this->ChangeAnimation(str);

	}
	m_updateFunc = &ControllerCharactor::NeutralUpdate;
}

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, PlayerType type, int digits, const Position2& pos, float scale) :
	Charactor(fileManager, fileNameBase, digits, pos, scale)
{
	if (m_type == PlayerType::monk)
	{
		std::string str = "walk";
		this->ChangeAnimation(str);
		this->SetOrigin(1);
	}
	else if (m_type == PlayerType::hero)
	{
		std::string str = "adventurer-run-";
		this->ChangeAnimation(str);
		
	}
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
	
	if (input.IsTriggered("attack"))
	{
		if (m_type == PlayerType::hero)
		{
			this->ChangeAnimation("adventurer-attack1-");
			//this->SetAnimationSpeed(5);
		}
		else if (m_type == PlayerType::monk)
		{
			this->ChangeAnimation("punch");
			//this->SetAnimationSpeed(5);
		}

	}
	m_currentInput = input;
}

void ControllerCharactor::Jump()
{
	m_vel.y += jump_speed;
	if (m_type == PlayerType::hero)
	{
		this->ChangeAnimation("adventurer-jump-");
	}
	else if (m_type == PlayerType::monk)
	{
		this->ChangeAnimation("jump");
	}
	m_updateFunc = &ControllerCharactor::JumpUpdate;
}

bool ControllerCharactor::CheckGround()
{
	return m_pos.y>ground_line;
}

void ControllerCharactor::Update()
{
	m_vel.y = Application::GetInstance().GetGravity();
	m_pos += m_vel;
	if (CheckGround())
	{
		m_vel.y = 0;
		m_pos.y = ground_line;
		if (m_type == PlayerType::hero)
		{
			ChangeAnimation("adventurer-idle-");
		}
		else if (m_type == PlayerType::monk)
		{
			ChangeAnimation("idle");
		}
	}
	Charactor::Update();
}

void ControllerCharactor::Draw()
{
	Charactor::Draw();

}
