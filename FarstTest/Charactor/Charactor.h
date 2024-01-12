#pragma once
#include "Actor.h"
#include <string>
#include <map>
#include <memory>

class File;


/// <summary>
/// �摜�̐؂蔲����`���
/// </summary>
struct CutRect
{
	int x, y;   // �؂��荶��
	int w, h;   // �؂���T�C�Y
	int offsetX, offsetY;   // �؂���I�t�Z�b�g
};

/// <summary>
/// ���߂���ăA�j���[�V������ړ��Ȃǂ��s���N���X
/// </summary>
class Charactor : public Actor
{
public:
	//�A�j���[�V�����̂��K�������ɂ���̂����߂�
	Charactor(FileManager& fileManager, std::wstring fileNameBase,int digitsNum);
	Charactor(FileManager& fileManager, std::wstring fileNameBase, int digitsNum, const Position2& pos, float scale = 1.0f);
	virtual ~Charactor();

	void ChangeAnimation(const std::string& animName);
	virtual void Update();
	virtual void Draw();
	

protected:
	using CutTable_t = std::map<std::string, CutRect>;

	std::string m_currentAnimatingName = "";
	CutRect m_currentCut = {};


	void Init(const std::wstring& fileNameBase);
	/// <summary>
	/// �w�肵���J�b�g�f�[�^�����[�h���ăJ�b�g�e�[�u����
	/// �R�s�[����
	/// </summary>
	/// <param name="dataPath"></param>
	/// <param name="cutTable"></param>
	void LoadCutData(const wchar_t* dataPath, CutTable_t& cutTable);
	void SetOrigin(int origin);


protected:
	// ���E�t���b�v���邩
	bool m_isTurn = false;

	// �؂蔲�����
	CutTable_t m_cutTable;
	// ���̉摜�t�@�C��
	std::shared_ptr<File> m_imgFile;

	// ���݂̃A�j���[�V�����t���[��
	int m_frame = 0;
	int m_origin = 0;
	// ���݂̃A�j���[�V����1��������̃t���[����
	int m_currentAnimInterval = 5;
	// �X�P�[���l
	const float m_drawScale = 3.0f;

	int m_digits = 1;
};

