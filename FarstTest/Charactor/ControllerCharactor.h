#pragma once
#include "Charactor.h"
#include"../Input.h"

class Input;

enum class PlayerType
{
	hero,
	monk,
};

//制御できるキャラクター　
class ControllerCharactor : public Charactor
{

	
	Vector2 m_vel = {};//速度
	Vector2 m_accel = {};//加速度
	void Jump();//ジャンプイベント
	void StartWalk();//歩き出しイベント
	void ReturnNeutral();
	void Fall();
	void Attack();//攻撃イベント
	void AerialAttack();//空中攻撃イベント
	bool CheckGround();

	PlayerType m_type;
	float m_jumpSpeed;
	Input m_currentInput;
	int m_jumpFrame = 0;

	//状態遷移のためのメンバ関数
	using UpdateFunc_t = void(ControllerCharactor::*)();
	UpdateFunc_t m_updateFunc;//毎フレーム実行する状態関数
	//状態関数
	void NeutralUpdate();//通常状態
	void WalkUpdate();//歩き(走り)
	void JumpUpdate();//ジャンプ中
	void AerialUpdate();//空中(上昇)
	void LandingUpdate();//空中(下降)
	void FallUpdate();//着地
	void AttackUpdate();//地上攻撃状態
	void AerialAttackUpdate();//空中攻撃状態

public:
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase,PlayerType type, int digits);
	ControllerCharactor(FileManager& fileManager, std::wstring fileNameBase, PlayerType type, int digits, const Position2& pos, float scale = 1.0f);

	
	void Move(const Vector2& vec);
	void SetPosition(const Position2& mov);
	virtual void Operate(const Input& input);
	virtual void Update();
	virtual void Draw();
};

