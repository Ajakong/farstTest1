#pragma once
#include "Charactor.h"
#include"../Input.h"

class Input;

enum class PlayerType
{
	hero,
	monk,
};

//����ł���L�����N�^�[�@
class ControllerCharactor : public Charactor
{

	
	Vector2 m_vel = {};//���x
	Vector2 m_accel = {};//�����x
	void Jump();//�W�����v�C�x���g
	void StartWalk();//�����o���C�x���g
	void ReturnNeutral();
	void Fall();
	void Attack();//�U���C�x���g
	void AerialAttack();//�󒆍U���C�x���g
	bool CheckGround();

	PlayerType m_type;
	float m_jumpSpeed;
	Input m_currentInput;
	int m_jumpFrame = 0;

	//��ԑJ�ڂ̂��߂̃����o�֐�
	using UpdateFunc_t = void(ControllerCharactor::*)();
	UpdateFunc_t m_updateFunc;//���t���[�����s�����Ԋ֐�
	//��Ԋ֐�
	void NeutralUpdate();//�ʏ���
	void WalkUpdate();//����(����)
	void JumpUpdate();//�W�����v��
	void AerialUpdate();//��(�㏸)
	void LandingUpdate();//��(���~)
	void FallUpdate();//���n
	void AttackUpdate();//�n��U�����
	void AerialAttackUpdate();//�󒆍U�����

public:
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase,PlayerType type, int digits);
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, PlayerType type, int digits, const Position2& pos, float scale = 1.0f);

	
	void Move(const Vector2& vec);
	void SetPosition(const Position2& mov);
	virtual void Operate(const Input& input);
	virtual void Update();
	virtual void Draw();
};

