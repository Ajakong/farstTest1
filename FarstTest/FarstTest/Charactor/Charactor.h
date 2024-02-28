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
	using CutTable_t = std::map<std::string, CutRect>;
public:
	// digits : �� ������ɂ���ăA�j���[�V�����̂��K�������ɂ���̂����߂�
	Charactor(FileManager& fileManager,const Camera& camera, std::wstring fileNameBase, int digitsNum,Position2& pos);
	Charactor(FileManager& fileManager, const Camera& camera, std::wstring fileNameBase, int digitsNum, const Position2& pos, float scale = 1.0f);
	virtual ~Charactor();

	void ChangeAnimation(const std::string& animName, bool isLoop = true);
	virtual void Update();
	virtual void Draw();
	void LoadCutData(const wchar_t* dataPath, CutTable_t& cutTable);

	/// <summary>
	/// �I���W�����Ⴄ�̂Ōォ��ύX�ł���悤��
	/// </summary>
	/// <param name="origin">�X�^�[�g�I���W��</param>
	void SetOrigin(int origin);
	/// <summary>
	/// �A�j���[�V�����X�s�[�h��ݒ�
	/// </summary>
	/// <param name="interval">1�������艽�t���[���g����</param>
	void SetAnimationSpeed(int interval);
	void SetTurn(bool isTurn);

protected:

	void Init(const std::wstring& fileNameBase);
	/// <summary>
	/// �w�肵���J�b�g�f�[�^�����[�h���ăJ�b�g�e�[�u����
	/// �R�s�[����
	/// </summary>
	/// <param name="dataPath"></param>
	/// <param name="cutTable"></param>
	bool IsAnimationEnd() const;

private:
	/// <summary>
	/// �A�j���[�V����������𓾂�
	/// </summary>
	/// <param name="baseName">�x�[�X��</param>
	/// <param name="index"></param>
	/// <returns></returns>
	std::string GetAnimationString(const std::string& baseName, int index);


protected:
	// ���E�t���b�v���邩
	bool m_isTurn = false;
	// �A�j���[�V���������[�v���邩
	bool m_isLoop = true;
	// �A�j���[�V�����̍Ōォ(���[�v�̎��͎g��Ȃ�)
	bool m_isAnimEnd = false;

	// �؂蔲�����
	CutTable_t m_cutTable;
	// ���̉摜�t�@�C��
	std::shared_ptr<File> m_imgFile;

	// ���݂̃A�j���[�V�����t���[��
	int m_frame = 0;
	// ���݂̃A�j���[�V����1��������̃t���[����
	int m_currentAnimInterval = 10;

	std::string m_currentAnimatingName = "";
	CutRect m_currentCut = {};
	int m_digits;
	//���I���W����(0����n�܂邩1����n�܂邩)
	int m_origin = 0;

	// �X�P�[���l
	const float m_drawScale;
};

