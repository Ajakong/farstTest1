#pragma once
#include "Charactor.h"
#include "../Input.h"

class Input;

enum class PlayerType
{
	hero,	// �E�҂��ۂ���l��
	monk,	// �����N
};

/// <summary>
/// ����ł���L�����N�^�[
/// </summary>
class ControllerCharacter : public Charactor
{
	using UpdateFunc_t = void (ControllerCharacter::*)();

public:
	ControllerCharacter(FileManager& fileManager, const Camera& camera, std::wstring fileNameBase, PlayerType type, int digits,const Position2& pos);
	ControllerCharacter(FileManager& fileManager, const Camera& camera, std::wstring fileNameBase, PlayerType type, int digits, const Position2& pos, float scale = 1.0f);

	virtual void Operate(const Input& input);
	void Move(const Vector2& vec);
	void SetPosition(const Position2& pos);

	virtual void Update();
	virtual void Draw();

private:
	void ReturnNetural();	// �ҋ@�C�x���g
	void Jump();		// �W�����v�C�x���g
	void StartWalk();	// �����C�x���g
	void Attack();		// �U���C�x���g
	void AerialAttack();	// �󒆍U���C�x���g
	void Fall();			// �����C�x���g
	bool CheckGraound() const;

	// ��Ԋ֐�
	void NeutralUpdate();	// �ʏ���(�n��)
	void JumpUpdate();		// �W�����v��(���ݍ��݂���󒆒��O�܂�)
	void AerialUpdate();	// ��(�㏸)
	void FallUpdate();		// ��(���~)
	void LandingUpdate();	// ���n
	void WalkUpdate();		// ����(����)
	void AttackUpdate();	// �n��U�����
	void AerialAttackUpdate();	// �󒆍U�����

private:
	PlayerType m_type;
	float m_jumpSpeed;		// �W�����v�X�s�[�h
	Vector2 m_vel = {};		// ���x
	Vector2 m_accel = {};	// �����x
	Input m_currentInput;
	int m_jumpFrame;

	// ��ԑJ�ڂ̂��߂̃����o�֐�
	UpdateFunc_t m_updateFunc;
};

