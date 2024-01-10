#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <list>

class File;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene : public Scene
{
public:
	TitleScene(SceneManager& manager);
	~TitleScene();
	virtual void Update(Input& input);
	virtual void Draw();

private:
	// ���e
	struct Bomb
	{
		int handle;
		Position2 pos;
		int frame = 0;
		bool isDead = false;
		Bomb(int h, const Position2& p) :
			handle(h), pos(p) {}
	};
	std::list<Bomb> m_bombs;
	enum class RotateDir
	{
		CLOCK_WISE,	// ���v���
		COUNTER_CLOCK_WISE	// �����v���
	};
	// ���e�g��
	struct BombSetter
	{
		Position2 pos;
		Vector2 vel;
		RotateDir rotDir;
		void CheckWall();
		void Rotate();
	};
	BombSetter upperSetter;
	BombSetter downSetter;
	int m_bigBombFrame = 0;
	bool m_isBigBomb = false;
	Position2 m_bigBombPos;

	std::shared_ptr<File> m_titleImg;
	std::shared_ptr<File> m_buttonsImg;
	std::shared_ptr<File> m_explosionImg;
	std::shared_ptr<File> m_coinSE;
	int m_frame = 0;

	int m_fadeFrame = 0;

	// �X�V�����o�֐��|�C���^
	void(TitleScene::* m_updateFunc)(Input& input);
	// �`�惁���o�֐��|�C���^
	using DrawFunc_t = void (TitleScene::*)();
	DrawFunc_t m_drawFunc;

	// �X�V�֐�
	void FadeInUpdate(Input&);	// �t�F�[�h�C�����
	void NormalUpdate(Input&);	// �ʏ���
	void FadeOutUpdate(Input&);	// �t�F�[�h�A�E�g���

	// �`��֐�
	void FadeDraw();	// �t�F�[�h���`��
	void NormalDraw();	// ��t�F�[�h�`��
};

