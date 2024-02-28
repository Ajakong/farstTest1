#pragma once
#include "Charactor.h"
#include "../Input.h"

class Input;

enum class PlayerType
{
	hero,	// 忍者っぽい主人公
	monk,	// モンク
};

/// <summary>
/// 制御できるキャラクター
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
	void ReturnNetural();	// 待機イベント
	void Jump();		// ジャンプイベント
	void StartWalk();	// 歩きイベント
	void Attack();		// 攻撃イベント
	void AerialAttack();	// 空中攻撃イベント
	void Fall();			// 落下イベント
	bool CheckGraound() const;

	// 状態関数
	void NeutralUpdate();	// 通常状態(地上)
	void JumpUpdate();		// ジャンプ中(踏み込みから空中直前まで)
	void AerialUpdate();	// 空中(上昇)
	void FallUpdate();		// 空中(下降)
	void LandingUpdate();	// 着地
	void WalkUpdate();		// 歩き(走り)
	void AttackUpdate();	// 地上攻撃状態
	void AerialAttackUpdate();	// 空中攻撃状態

private:
	PlayerType m_type;
	float m_jumpSpeed;		// ジャンプスピード
	Vector2 m_vel = {};		// 速度
	Vector2 m_accel = {};	// 加速度
	Input m_currentInput;
	int m_jumpFrame;

	// 状態遷移のためのメンバ関数
	UpdateFunc_t m_updateFunc;
};

