#include <DxLib.h>
#include <cassert>
#include "Charactor.h"
#include "../FileSystem/FileManager.h"
#include "../FileSystem/File.h"
#include <sstream>// coutの書き込み先を文字列にするようなもん
#include <iomanip>// 桁数をそろえたりするのに使う

#include"../Game/Camera.h"

Charactor::Charactor(FileManager& fileManager,const Camera& camera, std::wstring fileNameBase, int digitsNum,Position2& pos) :
	Actor(fileManager,camera,pos),
	m_drawScale(1.0f),
	m_digits(digitsNum)
{
	Init(fileNameBase);
}

Charactor::Charactor(FileManager& fileManager, const Camera& camera, std::wstring fileNameBase, int digitsNum, const Position2& pos, float scale) :
	Actor(fileManager,camera, pos),
	m_drawScale(scale),
	m_digits(digitsNum)
{
	Init(fileNameBase);
}

Charactor::~Charactor()
{
}

void Charactor::ChangeAnimation(const std::string& animName, bool isLoop)
{
	m_isLoop = isLoop;
	m_isAnimEnd = false;
	m_currentAnimatingName = animName;
	// アニメーションが切り替わるとリセット
	m_frame = 0;
}

void Charactor::Update()
{
	if (m_currentAnimatingName != "")
	{
		auto idx = (m_frame / m_currentAnimInterval) + m_origin;
		
		auto animName = GetAnimationString(m_currentAnimatingName, idx);

		// もしカウントアップの結果アニメーション枚数がない場合
		// またアニメーション番号を0にしてやり直す
		auto it = m_cutTable.find(animName);
		if (it == m_cutTable.end())
		{
			if (m_isLoop)
			{
				m_frame = 0;
				idx = (m_frame / m_currentAnimInterval) + m_origin;

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
				m_isAnimEnd = true;
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
	int x = m_pos.x + rc.offsetX * m_drawScale;
	if (m_isTurn)
	{
		x = m_pos.x - rc.offsetX * m_drawScale;
	}

	DrawRectRotaGraph2(x-m_camera.GetRange().Left(), m_pos.y + rc.offsetY * m_drawScale,
		rc.x, rc.y, rc.w, rc.h,
		rc.w / 2, rc.h,
		m_drawScale, 0,
		m_imgFile->GetHandle(), true, m_isTurn);
}


void Charactor::SetAnimationSpeed(int interval)
{
	m_currentAnimInterval = interval;
}

void Charactor::SetTurn(bool isTurn)
{
	m_isTurn = isTurn;
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
		// 文字列の長さを調査
		byte strLen = 0;
		FileRead_read(&strLen, sizeof(strLen), handle);
		// 文字列の調査
		std::string orgName;
		orgName.resize(strLen);
		FileRead_read(orgName.data(), sizeof(char) * orgName.size(), handle);
		// カット情報の調査
		CutRect cutRect = {};
		FileRead_read(&cutRect, sizeof(cutRect), handle);

		// 情報の読み込み
		cutTable[orgName] = cutRect;
	}

	FileRead_close(handle);
}

void Charactor::SetOrigin(int origin)
{
	m_origin = origin;
}

std::string Charactor::GetAnimationString(const std::string& baseName, int index)
{
	// 出力用文字列ストリーム
	std::ostringstream oss;
	// 元になるアニメーション名を追加
	oss << m_currentAnimatingName;
	// アニメーション番号のフォーマットを指定(何桁の0埋めか)
	oss << std::setw(m_digits) << std::setfill('0') << index;
	// 拡張の追加
	oss << ".png";

	// 文字列として返すためにstr()関数で返す
	return oss.str();
}

bool Charactor::IsAnimationEnd() const
{
	return m_isAnimEnd;
}
