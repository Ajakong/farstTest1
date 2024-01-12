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
}

Charactor::~Charactor()
{
}



void Charactor::ChangeAnimation(const std::string& animName)
{
	m_currentAnimatingName = animName;
	m_frame = 0;
}

void Charactor::Update()
{
	if (m_currentAnimatingName != "")
	{
		auto idx=(m_frame / m_currentAnimInterval)+m_origin;
		std::ostringstream oss;
		oss << m_currentAnimatingName;
		oss << std::setw(m_digits) << std::setfill('0') << idx;
		oss << ".png";
		auto it = m_cutTable.find(oss.str());
		if (it == m_cutTable.end())
		{
			idx = 0;
			m_frame = 0;
			auto idx = (m_frame / m_currentAnimInterval) + m_origin;
			std::ostringstream oss;
			oss << m_currentAnimatingName;
			oss << std::setw(m_digits) << std::setfill('0') << idx;
			oss << ".png";
			it = m_cutTable.find(oss.str());
			if (it == m_cutTable.end())
			{
				m_currentAnimatingName = "";
				return;
			}
		}
		m_currentCut = it->second;
	}
	m_frame++;
	
}

void Charactor::Draw()
{
	

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

	
	DrawRectRotaGraph(m_pos.x + rc.offsetX * m_drawScale, m_pos.y + rc.offsetY * m_drawScale,
		rc.x, rc.y, rc.w, rc.h,
		m_drawScale, 0,
		m_imgFile->GetHandle(), true,m_isTurn);
}

void Charactor::SetOrigin(int origin)
{
	m_origin = origin;

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
		// •¶Žš—ñ‚Ì’·‚³‚ð’²¸
		byte strLen = 0;
		FileRead_read(&strLen, sizeof(strLen), handle);
		// •¶Žš—ñ‚Ì’²¸
		std::string orgName;
		orgName.resize(strLen);
		FileRead_read(orgName.data(), sizeof(char) * orgName.size(), handle);
		// ƒJƒbƒgî•ñ‚Ì’²¸
		CutRect cutRect = {};
		FileRead_read(&cutRect, sizeof(cutRect), handle);

		// î•ñ‚Ì“Ç‚Ýž‚Ý
		cutTable[orgName] = cutRect;
	}

	FileRead_close(handle);
}
