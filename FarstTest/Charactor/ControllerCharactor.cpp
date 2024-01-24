#include "ControllerCharactor.h"
#include "../Input.h"
#include"../Application.h"
#include<cmath>
#include"Dxlib.h"

namespace
{
	float jump_speed = -10.0f;
	int ground_line = 400;
}



void ControllerCharactor::NeutralUpdate()
{
	if (m_currentInput.IsTriggered("attack"))
	{
		Attack();
		return;
	}
	bool isLeft = m_currentInput.IsPressing("left");
	bool isRight = m_currentInput.IsPressing("right");
	if (isLeft)
	{
		m_vel.x -= 4.0f;
	}
	if (isRight)
	{
		m_vel.x += 4.0f;
	}
	if (m_currentInput.IsTriggered("jump"))
	{
		Jump();//イベント
		return;
	}
	if (isLeft || isRight)
	{
		if (isLeft)
		{
			SetTurn(true);
		}
		else
		{
			SetTurn(false);
		}
		StartWalk();
	}
}

void ControllerCharactor::WalkUpdate()
{
	bool isLeft = m_currentInput.IsPressing("left");
	bool isRight = m_currentInput.IsPressing("right");
	if (isLeft || isRight)
	{
		if (isLeft)
		{
			SetTurn(true);
			m_vel.x -= 4.0f;
		}
		else
		{
			SetTurn(false);
			m_vel.x += 4.0f;
		}
		return;
	}
	if(m_currentInput.IsTriggered("jump"))
	{
		Jump();//イベント
		return;
	}
	ReturnNeutral();//Neutralに戻る
}

void ControllerCharactor::JumpUpdate()
{
	m_jumpFrame++;
	if (m_currentInput.IsReleased("jump")||m_jumpFrame==20)
	{
		m_accel.y = m_vel.y / 10.0f;
	}
	m_updateFunc = &ControllerCharactor::AerialUpdate;
}

void ControllerCharactor::AerialUpdate()
{
	m_jumpFrame++;
	if (m_currentInput.IsReleased("jump"))
	{
		m_accel.y =- m_vel.y / 10.0f;
	}
	m_vel.y += m_accel.y;
	m_vel.y += Application::GetInstance().GetGravity();
	m_pos += m_vel;
	if (m_currentInput.IsTriggered("attack"))
	{
		AerialAttack();
		return;
	}

	//下向きの速度になったら「下降」へ移行
	if (m_vel.y - Application::GetInstance().GetGravity() > 0.0f)//(下向きがプラス)
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
	ReturnNeutral();
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
	if (m_currentInput.IsTriggered("attack"))
	{
		AerialAttack();
		return;
	}
}

void ControllerCharactor::AttackUpdate()
{
	if (IsAnimationEnd())
	{
		ReturnNeutral();
	}
}

void ControllerCharactor::AerialAttackUpdate()
{
	m_vel.y += Application::GetInstance().GetGravity();
	m_pos += m_vel;
	if (CheckGround())
	{
		m_pos.y = ground_line;
		ReturnNeutral();
		return;
	}
	//下向きの速度になったら「下降」へ移行
	if (IsAnimationEnd())//(下向きがプラス)
	{
		if (m_vel.y > 0)
		{
			Fall();
			return;
		}
		else
		{
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
	}

}

ControllerCharactor::ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, PlayerType type, int digits) :
	Charactor(fileManager, fileNameBase,digits ),
	m_type(type)
{
	m_jumpSpeed = jump_speed;
	//望む高さからジャンプスピードを計算する
	m_jumpSpeed = -sqrtf(2.0f * 200.0f - Application::GetInstance().GetGravity());
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
	
	//if (input.IsTriggered("attack"))
	//{
	//	if (m_type == PlayerType::hero)
	//	{
	//		this->ChangeAnimation("adventurer-attack1-");
	//		//this->SetAnimationSpeed(5);
	//	}
	//	else if (m_type == PlayerType::monk)
	//	{
	//		this->ChangeAnimation("punch");
	//		//this->SetAnimationSpeed(5);
	//	}

	//}
	m_currentInput = input;
}

void ControllerCharactor::Jump()
{
	m_jumpFrame = 0;
	m_vel.y = jump_speed;
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

void ControllerCharactor::StartWalk()
{
	
	if (m_type == PlayerType::hero)
	{
		this->ChangeAnimation("adventurer-run-");
	}
	else if (m_type == PlayerType::monk)
	{
		this->ChangeAnimation("walk");
	}
	m_updateFunc = &ControllerCharactor::WalkUpdate;
}

void ControllerCharactor::ReturnNeutral()
{
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
	SetAnimationSpeed(10);
	m_vel.x = 0.0f;
	m_accel.y = 0;
	m_updateFunc = &ControllerCharactor::NeutralUpdate;
}

void ControllerCharactor::Fall()
{

	switch (m_type)
	{
	case PlayerType::hero:
		this->ChangeAnimation("adventurer-fall-", false);
		SetAnimationSpeed(5);
		//this->SetAnimationSpeed(5);
		break;

	case PlayerType::monk:
		this->ChangeAnimation("fall", false);
		SetAnimationSpeed(5);
		//this->SetAnimationSpeed(5);
		break;
	}
	m_updateFunc = &ControllerCharactor::FallUpdate;
}

void ControllerCharactor::Attack()
{
	switch (m_type)
	{
	case PlayerType::hero:
		this->ChangeAnimation("adventurer-attack1-",false);
		SetAnimationSpeed(5);
		//this->SetAnimationSpeed(5);
		break;

	case PlayerType::monk:
		this->ChangeAnimation("punch",false);
		SetAnimationSpeed(5);
		//this->SetAnimationSpeed(5);
		break;
	}
	m_updateFunc = &ControllerCharactor::AttackUpdate;

}

void ControllerCharactor::AerialAttack()
{
	switch (m_type)
	{
	case PlayerType::hero:
		this->ChangeAnimation("adventurer-air-attack3-", false);
		SetAnimationSpeed(5);
		//this->SetAnimationSpeed(5);
		break;

	case PlayerType::monk:
		this->ChangeAnimation("flying-kick", false);
		SetAnimationSpeed(5);
		//this->SetAnimationSpeed(5);
		break;
	}
	SetAnimationSpeed(8);
	m_updateFunc = &ControllerCharactor::AerialAttackUpdate;
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
	DrawLineAA(0, 400, 640, 400, 0xffffff, 3.0f);
}
