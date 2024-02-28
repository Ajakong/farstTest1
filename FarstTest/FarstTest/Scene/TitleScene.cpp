#include <DxLib.h>
#include <cassert>
#include "../Input.h"
#include "../Application.h"

#include "SceneManager.h"
#include "TitleScene.h"
#include "GamePlayingScene.h"
#include "../FileSystem/FileManager.h"
#include "../FileSystem/File.h"

// �f�o�b�O���O�֌W
#include <sstream>
#include <iomanip>

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager)
{
	auto& fileMgr = m_manager.GetFileManager();
	m_titleImg = fileMgr.LoadGraphic(L"./Data/Image/title.png");
	m_buttonsImg = fileMgr.LoadGraphic(L"./Data/Image/UI/xbox_buttons.png", true);
	m_coinSE = fileMgr.LoadSound(L"./Data/Sound/coin.wav");
	m_explosionImg = fileMgr.LoadGraphic(L"./Data/Image/Effect/explosion.png");
	m_fadeFrame = 60;
	m_updateFunc = &TitleScene::FadeInUpdate;
	m_drawFunc = &TitleScene::FadeDraw;

	// output string stream
	// Debug���O�̕\��
	std::ostringstream oss;
	oss << "TitleScene handle=" << std::hex << m_titleImg->GetHandle() <<
		" , frame=" << std::dec << std::setw(4) << std::setfill('0') << m_fadeFrame <<
		" , FPS=" << std::fixed << std::setprecision(2) << GetFPS() << std::endl;
	OutputDebugStringA(oss.str().c_str());
}

TitleScene::~TitleScene()
{
	OutputDebugString(L"�^�C�g���V�[����delete����܂���\n");
}

void TitleScene::Update(Input& input)
{
	(this->*m_updateFunc)(input);
}

void TitleScene::Draw()
{
	(this->*m_drawFunc)();
}

void TitleScene::FadeInUpdate(Input&)
{
	m_fadeFrame--;
	if (m_fadeFrame <= 0) // �J�ڏ���
	{
		// ���̑J�ڐ�
		m_updateFunc = &TitleScene::NormalUpdate;
		m_drawFunc = &TitleScene::NormalDraw;

		upperSetter.pos = downSetter.pos = {320.0f, 240.0f};
		upperSetter.vel = { 0.0f, -4.0f };
		downSetter.vel = { 0.0f, 4.0f };
		upperSetter.rotDir = RotateDir::CLOCK_WISE;
		downSetter.rotDir = RotateDir::COUNTER_CLOCK_WISE;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		m_updateFunc = &TitleScene::FadeOutUpdate;
		m_drawFunc = &TitleScene::FadeDraw;
		PlaySoundMem(m_coinSE->GetHandle(), DX_PLAYTYPE_BACK);
		m_fadeFrame = 0;
	}
	m_fadeFrame = m_fadeFrame + 8;
	m_frame++;
	GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (upperSetter.pos == downSetter.pos)
	{
		m_isBigBomb = true;
		m_bigBombFrame = 0;
		m_bigBombPos = upperSetter.pos;
	}

	upperSetter.CheckWall();
	downSetter.CheckWall();
	upperSetter.pos += upperSetter.vel;
	downSetter.pos += downSetter.vel;

	if (m_frame % 10 == 0)
	{
		m_bombs.emplace_back(m_explosionImg->GetHandle(), upperSetter.pos);
		m_bombs.emplace_back(m_explosionImg->GetHandle(), downSetter.pos);
	}

	for (auto& b : m_bombs)
	{
		b.frame++;
		if (b.frame >= 45)
		{
			b.isDead = true;
		}
	}
	// isDead��true�̕��̂ݏ���
	m_bombs.remove_if(
		[](const Bomb& bomb) 
		{ 
			return bomb.isDead; 
		});

	m_bigBombFrame++;
	if (m_bigBombFrame >= 45)
	{
		m_isBigBomb = false;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	m_fadeFrame++;
	if (60 <= m_fadeFrame)
	{
		m_manager.ChangeScene(std::make_shared<GamePlayingScene>(m_manager));
	}
}

void TitleScene::FadeDraw()
{
	// �ʏ�̕`��
	DrawString(10, 100, L"TitleScene", 0xffffff);
	DrawGraph(100, 100, m_titleImg->GetHandle(), true);

	// �t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * (static_cast<float>(m_fadeFrame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawString(10, 100, L"TitleScene", 0xffffff);
	DrawGraph(100, 100, m_titleImg->GetHandle(), true);
	int dx = abs((m_fadeFrame + 640) % (640 * 2) - 640);
	int num = 200;
	float dy = abs((m_fadeFrame + num) % (num * 2) - num) * 0.1f;
	dy = dy * dy;
	DrawCircle(dx, static_cast<int>(dy), 10, 0xffaaaa, true);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_frame / 10 % 3;
	constexpr int kButtonSize = 16;
	DrawRectRotaGraph(size.w / 2, size.h / 2,// ��ʂ̐^��
		idx * kButtonSize, 0,// ���摜�؂��荶��
		kButtonSize, kButtonSize,// �؂���T�C�Y
		3.0, //�g�嗦
		0.0,
		m_buttonsImg->GetHandle(), true);

	for (const auto& bomb : m_bombs)
	{
		int expIdx = (bomb.frame / 5) % 9;
		int idxX = expIdx % 3;	// ��ԍ�
		int idxY = expIdx / 3;	// �s�ԍ�
		constexpr int kExpSize = 32;
		DrawRectRotaGraph(bomb.pos.x, bomb.pos.y,// ��ʂ̐^��+�E100
			idxX * kExpSize,
			idxY * kExpSize,
			kExpSize, kExpSize,
			2.0,
			0.0,
			bomb.handle,
			true
		);
	}

	if (m_isBigBomb)
	{
		int expIdx = (m_bigBombFrame / 5) % 9;
		int idxX = expIdx % 3;	// ��ԍ�
		int idxY = expIdx / 3;	// �s�ԍ�
		constexpr int kExpSize = 32;
		DrawRectRotaGraph(m_bigBombPos.x, m_bigBombPos.y,// ��ʂ̐^��+�E100
			idxX * kExpSize,
			idxY * kExpSize,
			kExpSize, kExpSize,
			8.0,
			0.0,
			m_explosionImg->GetHandle(),
			true
		);
	}
}

void TitleScene::BombSetter::CheckWall()
{
	if (vel.x > 0 && pos.x >= 640)
	{
		Rotate();
		CheckWall();
		return;
	}
	if (vel.x < 0 && pos.x <= 0)
	{
		Rotate();
		CheckWall();
		return;
	}
	if (vel.y > 0 && pos.y >= 480)
	{
		Rotate();
		CheckWall();
		return;
	}
	if (vel.y < 0 && pos.y <= 0)
	{
		Rotate();
		CheckWall();
		return;
	}
}

void TitleScene::BombSetter::Rotate()
{
	if (rotDir == RotateDir::CLOCK_WISE)
	{
		// ���v���
		vel = { -vel.y, vel.x };
	}
	else
	{
		// �����v���
		vel = { vel.y, -vel.x };
	}
}
