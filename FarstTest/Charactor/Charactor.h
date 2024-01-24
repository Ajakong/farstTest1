#pragma once
#include "Actor.h"
#include <string>
#include <map>
#include <memory>

class File;


/// <summary>
/// 画像の切り抜き矩形情報
/// </summary>
struct CutRect
{
	int x, y;   // 切り取り左上
	int w, h;   // 切り取りサイズ
	int offsetX, offsetY;   // 切り取りオフセット
};

/// <summary>
/// 命令されてアニメーションや移動などを行うクラス
/// </summary>
class Charactor : public Actor
{
public:
	//アニメーションのお尻を何桁にするのか決める
	Charactor(FileManager& fileManager, std::wstring fileNameBase,int digitsNum);
	Charactor(FileManager& fileManager, std::wstring fileNameBase, int digitsNum, const Position2& pos, float scale = 1.0f);
	virtual ~Charactor();

	void SetOrigin(int origin);

	void ChangeAnimation(const std::string& animName,bool isLoop=true);
	void SetAnimationSpeed(int interval);
	void SetTurn(bool isTurn);
	virtual void Update();
	virtual void Draw();
	
	
	

protected:
	bool m_isLoop = true;
	bool m_isAnimEnd = false;//アニメーションの最後か(ループの時は使わない)
	using CutTable_t = std::map<std::string, CutRect>;

	std::string m_currentAnimatingName = "";
	CutRect m_currentCut = {};


	void Init(const std::wstring& fileNameBase);
	/// <summary>
	/// 指定したカットデータをロードしてカットテーブルに
	/// コピーする
	/// </summary>
	/// <param name="dataPath"></param>
	/// <param name="cutTable"></param>
	void LoadCutData(const wchar_t* dataPath, CutTable_t& cutTable);
	

	
	/// <summary>
	/// ０オリジンか１オリジンかがファイルによって違うので
	/// 
	/// </summary>
	/// <param name="basename"></param>
	/// <param name="index"></param>
	/// <returns></returns>
	
	
	std::string GetAnimationString(const std::string& basename, int index);
	bool IsAnimationEnd();
protected:
	// 左右フリップするか
	bool m_isTurn = false;

	// 切り抜き情報
	CutTable_t m_cutTable;
	// 元の画像ファイル
	std::shared_ptr<File> m_imgFile;

	// 現在のアニメーションフレーム
	int m_frame = 0;
	int m_origin = 0;
	// 現在のアニメーション1枚当たりのフレーム数
	int m_currentAnimInterval = 10;
	// スケール値
	const float m_drawScale = 3.0f;

	int m_digits = 1;//キャラクターによってアニメーション画像の名前の後ろ番号の桁数が違うため桁数指定
};

