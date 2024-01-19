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

	
	Vector2 m_vel = {};
	void Jump();
	bool CheckGround();
	PlayerType m_type;
	Input m_currentInput;

	//��ԑJ�ڂ̂��߂̃����o�֐�
	using UpdateFunc_t = void(ControllerCharactor::*)();
	UpdateFunc_t m_updateFunc;//���t���[�����s�����Ԋ֐�
	void NeutralUpdate();
	void JumpUpdate();
	void AerialUpdate();
	void LandingUpdate();
	void FallUpdate();

public:
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase,PlayerType type, int digits);
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, PlayerType type, int digits, const Position2& pos, float scale = 1.0f);

	
	void Move(const Vector2& vec);
	void SetPosition(const Position2& mov);
	virtual void Operate(const Input& input);
	virtual void Update();
	virtual void Draw();
};

