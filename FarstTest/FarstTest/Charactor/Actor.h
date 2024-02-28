#pragma once
#include "../Geometry.h"

class FileManager;
class Camera;

/// <summary>
/// ゲーム内に配置される表示物を表す基底クラス
/// </summary>
class Actor
{
public:
	Actor(FileManager& fileManager, const Camera& camera, const Position2& pos = {});
	virtual ~Actor();
	/// <summary>
	/// 内部状態の更新
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 現在のアクターを表示する
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 座標を指定する
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const Position2& pos);

	const Position2& GetPosition();

protected:
	FileManager& m_fileManager;
	Position2 m_pos;	// 表示する現在の座標
	const Camera& m_camera;
};

