#include <DxLib.h>
#include <cassert>
#include "Charactor.h"
#include "../FileSystem/FileManager.h"
#include "../FileSystem/File.h"
#include<sstream>
#include<iomanip>

Charactor::Charactor(FileManager& fileManager, std::wstring fileNameBase,int digitsNum) :
	Actor(fileManager),
	m_digits(digitsNum)
{
	Init(fileNameBase);
}

Charactor::Charactor(FileManager& fileManager, std::wstring fileNameBase, int digitsNum, const Position2& pos, float scale) :
	Actor(m_fileManager),
	m_digits(digitsNum)
{
	Init(fileNameBase);
}

Charactor::~Charactor()
{
}



void Charactor::ChangeAnimation(const std::string& animName,bool isLoop)
{
	m_isAnimEnd = false;
	m_isLoop = isLoop;
	m_currentAnimatingName = animName;
	m_frame = 0;//�A�j���[�V�������؂�ւ��ƃ��Z�b�g
}

void Charactor::SetAnimationSpeed(int interval)
{
	m_currentAnimInterval = interval;
}

void Charactor::SetTurn(bool isTurn)
{
	m_isTurn = isTurn;
}

void Charactor::Update()
{

	if (m_currentAnimatingName != "")
	{
		auto idx = (m_frame / m_currentAnimInterval) + m_origin;
		auto animName = GetAnimationString(m_currentAnimatingName, idx);
		//�����J�E���g�A�b�v�̌��ʂ����A�j���[�V�����������Ȃ��ꍇ
		//�܂��A�j���[�V�����ԍ���0�ɂ��Ă�蒼��
		
		auto it = m_cutTable.find(animName);
		if (it == m_cutTable.end())
		{
			if (m_isLoop)
			{
				m_frame = 0;
				auto idx = (m_frame / m_currentAnimInterval) + m_origin;
				animName = GetAnimationString(m_currentAnimatingName, idx);
				it = m_cutTable.find(animName);
				if (it == m_cutTable.end())
				{
					m_currentAnimatingName = "";
				return;
				}
			}
			else
			{
				
			}
		}
		m_currentCut = it->second;
		
	
	}
	m_frame++;
	
}

void Charactor::Draw()
{
	//Init���Ăяo����Ă˂�

	auto it = m_cutTable.begin();
	CutRect rc = {};
	if (m_currentAnimatingName == "")
	{
		
		for (int i = 0; i < (m_frame / m_currentAnimInterval) % m_cutTable.size(); i++)
		{
			it++;
		}
		

		
		rc = it->second;
	}
	else
	{
		rc = m_currentCut;
	}

	
	DrawRectRotaGraph2(m_pos.x + rc.offsetX * m_drawScale, m_pos.y + rc.offsetY * m_drawScale,
		rc.x, rc.y, rc.w, rc.h,rc.w/2,rc.h,
		m_drawScale, 0,
		m_imgFile->GetHandle(), true,m_isTurn);
		
	//DrawCircle(m_pos.x + rc.offsetX * m_drawScale, m_pos.y, 3, 0x00ff00);
}



void Charactor::SetOrigin(int origin)
{
	m_origin = origin;

}

std::string Charactor::GetAnimationString(const std::string& basename, int index)
{
	std::ostringstream oss;
	oss << m_currentAnimatingName;
	oss << std::setw(m_digits) << std::setfill('0') << index;
	oss << ".png";
	return oss.str();//������Ƃ��ĕԂ����߂�str()�֐��ŕԂ�
}

bool Charactor::IsAnimationEnd()
{
	return m_isAnimEnd;
}


void Charactor::Init(const std::wstring& fileNameBase)
{
	m_imgFile = m_fileManager.LoadGraphic(fileNameBase + L".png");
	auto cutDataName = fileNameBase + L".dat";
	LoadCutData(cutDataName.c_str(), m_cutTable);
}

void Charactor::LoadCutData(const wchar_t* dataPath, CutTable_t& cutTable)
{
	int handle = FileRead_open(dataPath);
	assert(handle != 0);
	int cutNum = 0;
	FileRead_read(&cutNum, sizeof(cutNum), handle);
	cutTable.clear();

	for (int i = 0; i < cutNum; i++)
	{
		// ������̒����𒲍�
		byte strLen = 0;
		FileRead_read(&strLen, sizeof(strLen), handle);
		// ������̒���
		std::string orgName;
		orgName.resize(strLen);
		FileRead_read(orgName.data(), sizeof(char) * orgName.size(), handle);
		// �J�b�g���̒���
		CutRect cutRect = {};
		FileRead_read(&cutRect, sizeof(cutRect), handle);

		// ���̓ǂݍ���
		cutTable[orgName] = cutRect;
	}

	FileRead_close(handle);
}
