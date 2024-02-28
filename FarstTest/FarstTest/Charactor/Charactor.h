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
	using CutTable_t = std::map<std::string, CutRect>;
public:
	// digits : 桁 →これによってアニメーションのお尻を何桁にするのか決める
	Charactor(FileManager& fileManager,const Camera& camera, std::wstring fileNameBase, int digitsNum,Position2& pos);
	Charactor(FileManager& fileManager, const Camera& camera, std::wstring fileNameBase, int digitsNum, const Position2& pos, float scale = 1.0f);
	virtual ~Charactor();

	void ChangeAnimation(const std::string& animName, bool isLoop = true);
	virtual void Update();
	virtual void Draw();
	void LoadCutData(const wchar_t* dataPath, CutTable_t& cutTable);

	/// <summary>
	/// オリジンが違うので後から変更できるように
	/// </summary>
	/// <param name="origin">スタートオリジン</param>
	void SetOrigin(int origin);
	/// <summary>
	/// アニメーションスピードを設定
	/// </summary>
	/// <param name="interval">1枚当たり何フレーム使うか</param>
	void SetAnimationSpeed(int interval);
	void SetTurn(bool isTurn);

protected:

	void Init(const std::wstring& fileNameBase);
	/// <summary>
	/// 指定したカットデータをロードしてカットテーブルに
	/// コピーする
	/// </summary>
	/// <param name="dataPath"></param>
	/// <param name="cutTable"></param>
	bool IsAnimationEnd() const;

private:
	/// <summary>
	/// アニメーション文字列を得る
	/// </summary>
	/// <param name="baseName">ベース名</param>
	/// <param name="index"></param>
	/// <returns></returns>
	std::string GetAnimationString(const std::string& baseName, int index);


protected:
	// 左右フリップするか
	bool m_isTurn = false;
	// アニメーションをループするか
	bool m_isLoop = true;
	// アニメーションの最後か(ループの時は使わない)
	bool m_isAnimEnd = false;

	// 切り抜き情報
	CutTable_t m_cutTable;
	// 元の画像ファイル
	std::shared_ptr<File> m_imgFile;

	// 現在のアニメーションフレーム
	int m_frame = 0;
	// 現在のアニメーション1枚当たりのフレーム数
	int m_currentAnimInterval = 10;

	std::string m_currentAnimatingName = "";
	CutRect m_currentCut = {};
	int m_digits;
	//何オリジンか(0から始まるか1から始まるか)
	int m_origin = 0;

	// スケール値
	const float m_drawScale;
};

