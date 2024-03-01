#include "ControllerCharactor.h"
#include "../Application.h"
#include "../Input.h"
#include <cmath>
#include<algorithm>
#include"../Game/Camera.h"

namespace
{
	constexpr float kJumpSpeed = -10.0f;
	constexpr int kGroundLine = 400;
	constexpr float g = 1.0f;
	constexpr int kJumpLimitFrame = 20;
}

ControllerCharacter::ControllerCharacter(FileManager& fileManager, const Camera& camera, std::wstring fileNameBase, PlayerType type, int digits,const Position2& pos) :
	Charactor(fileManager,camera, fileNameBase, digits,pos),
	m_type(type),
	m_jumpSpeed(kJumpSpeed),
	m_jumpFrame(0)
{
	// 望む高さからジャンプスピードを計算する
	m_jumpSpeed = -sqrtf(2.0f * Application::GetInstance().GetGravity() * 200.0f);

	m_updateFunc = &ControllerCharacter::NeutralUpdate;
}

ControllerCharacter::ControllerCharacter(FileManager& fileManager, const Camera& camera, std::wstring fileNameBase, PlayerType type, int digits, const Position2& pos, float scale) :
	Charactor(fileManager,camera, fileNameBase, digits, pos, scale),
	m_type(type),
	m_jumpSpeed(kJumpSpeed),
	m_jumpFrame(0)
{
	// 望む高さからジャンプスピードを計算する
	m_jumpSpeed = -sqrtf(2.0f * Application::GetInstance().GetGravity() * 200.0f);

	m_updateFunc = &ControllerCharacter::NeutralUpdate;
}

void ControllerCharacter::Operate(const Input& input)
{
	m_currentInput = input;
}

void ControllerCharacter::Move(const Vector2& vec)
{
	m_pos += vec;
}

void ControllerCharacter::SetPosition(const Position2& pos)
{
}

void ControllerCharacter::Update()
{
	(this->*m_updateFunc)();

	m_pos.x = std::clamp(m_pos.x, static_cast<float>(m_camera.GetRange().Left()), static_cast<float>(m_camera.GetRange().Right()));

	Charactor::Update();
}

void ControllerCharacter::Draw()
{
	// 子クラスから親クラスの関数を呼び出す
	Charactor::Draw();
}

void ControllerCharacter::ReturnNetural()
{
	switch (m_type)
	{
	case PlayerType::hero:
		ChangeAnimation("adventurer-idle-");
		break;
	case PlayerType::monk:
		ChangeAnimation("idle");
		break;
	default:
		break;
	}
	SetAnimationSpeed(10);
	// 0で初期化
	m_vel = {};
	m_accel = {};
	m_updateFunc = &ControllerCharacter::NeutralUpdate;
}

void ControllerCharacter::Jump()
{
	
	m_vel.y = m_jumpSpeed;
	m_accel.y = g;
	m_jumpFrame = kJumpLimitFrame;
	switch (m_type)
	{
	case PlayerType::hero:
		ChangeAnimation("adventurer-jump-");
		break;
	case PlayerType::monk:
		ChangeAnimation("jump");
		break;
	default:
		break;
	}
	m_updateFunc = &ControllerCharacter::JumpUpdate;
}

void ControllerCharacter::StartWalk()
{
	switch (m_type)
	{
	case PlayerType::hero:
		ChangeAnimation("adventurer-run-");
		break;
	case PlayerType::monk:
		ChangeAnimation("walk");
		break;
	default:
		break;
	}
	m_updateFunc = &ControllerCharacter::WalkUpdate;
}

void ControllerCharacter::Attack()
{
	switch (m_type)
	{
	case PlayerType::hero:
		ChangeAnimation("adventurer-attack1-", false);
		break;
	case PlayerType::monk:
		ChangeAnimation("punch", false);
		break;
	default:
		break;
	}
	SetAnimationSpeed(5);
	m_updateFunc = &ControllerCharacter::AttackUpdate;
}

void ControllerCharacter::AerialAttack()
{
	switch (m_type)
	{
	case PlayerType::hero:
		ChangeAnimation("adventurer-air-attack3-loop-", false);
		break;
	case PlayerType::monk:
		ChangeAnimation("flying-kick", false);
		break;
	default:
		break;
	}
	SetAnimationSpeed(10);
	m_updateFunc = &ControllerCharacter::AerialAttackUpdate;
}

void ControllerCharacter::Fall()
{
	switch (m_type)
	{
	case PlayerType::hero:
		ChangeAnimation("adventurer-fall-");
		break;
	case PlayerType::monk:
		ChangeAnimation("fall");
		break;
	default:
		break;
	}
	m_updateFunc = &ControllerCharacter::FallUpdate;
}

bool ControllerCharacter::CheckGraound() const
{
	return m_pos.y > kGroundLine;
}

void ControllerCharacter::NeutralUpdate()
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
		m_vel.x = -4.0f;
	}
	else if (isRight)
	{
		m_vel.x = 4.0f;
	}
	if (m_currentInput.IsTriggered("jump"))
	{
		Jump();	// イベント
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

void ControllerCharacter::JumpUpdate()
{
	m_jumpFrame++;
	m_accel.y = -m_vel.y / 10.0f;
	
	m_updateFunc = &ControllerCharacter::AerialUpdate;
}

void ControllerCharacter::AerialUpdate()
{
	
	if (m_currentInput.IsReleased("jump"))
	{
		m_jumpFrame = 0;
	}
	if (m_jumpFrame < 0)
	{
		m_vel.y += m_accel.y;//Application::GetInstance().GetGravity();
	}
	else
	{
		m_jumpFrame-=2;
	}
	m_pos += m_vel;
	
	// ジャンプ中攻撃
	if (m_currentInput.IsTriggered("attack"))
	{
		AerialAttack();
		return;
	}

	// 下向きの速度になったら「下降」へ移行する
	if (m_vel.y - Application::GetInstance().GetGravity() > 0.0f)
	{
		Fall();
	}
}

void ControllerCharacter::FallUpdate()
{
	m_vel.y +=m_accel.y;
	m_pos += m_vel;

	if (CheckGraound())
	{
		m_vel.y = 0.0f;
		m_pos.y = kGroundLine;
		m_updateFunc = &ControllerCharacter::LandingUpdate;
	}

	// ジャンプ中攻撃
	if (m_currentInput.IsTriggered("attack"))
	{
		AerialAttack();
	}
}

void ControllerCharacter::LandingUpdate()
{
	ReturnNetural();
}

void ControllerCharacter::WalkUpdate()
{
	if (m_currentInput.IsTriggered("jump"))
	{
		Jump();
		return;
	}

	bool isLeft = m_currentInput.IsPressing("left");
	bool isRight = m_currentInput.IsPressing("right");
	if (isLeft || isRight)
	{
		if (isLeft)
		{
			SetTurn(true);
			m_vel.x = -4.0f;
		}
		else
		{
			SetTurn(false);
			m_vel.x = 4.0f;
		}
		m_pos += m_vel;
		return;
	}

	ReturnNetural();
}

void ControllerCharacter::AttackUpdate()
{
	if (IsAnimationEnd())
	{
		ReturnNetural();
	}
}

void ControllerCharacter::AerialAttackUpdate()
{
	m_vel.y += Application::GetInstance().GetGravity();
	m_pos += m_vel;

	if (CheckGraound())
	{
		m_pos.y = kGroundLine;
		ReturnNetural();
		return;
	}

	if (IsAnimationEnd())
	{
		if (m_vel.y > 0.0f)
		{
			Fall();
			return;
		}
		else
		{
			switch (m_type)
			{
			case PlayerType::hero:
				ChangeAnimation("adventurer-jump-");
				break;
			case PlayerType::monk:
				ChangeAnimation("jump");
				break;
			default:
				break;
			}
			m_updateFunc = &ControllerCharacter::AerialUpdate;
		}
	}
}
