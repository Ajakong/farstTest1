#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <list>

class File;

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public Scene
{
public:
	TitleScene(SceneManager& manager);
	~TitleScene();
	virtual void Update(Input& input);
	virtual void Draw();

private:
	// 爆弾
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
		CLOCK_WISE,	// 時計回り
		COUNTER_CLOCK_WISE	// 反時計回り
	};
	// 爆弾使い
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

	// 更新メンバ関数ポインタ
	void(TitleScene::* m_updateFunc)(Input& input);
	// 描画メンバ関数ポインタ
	using DrawFunc_t = void (TitleScene::*)();
	DrawFunc_t m_drawFunc;

	// 更新関数
	void FadeInUpdate(Input&);	// フェードイン状態
	void NormalUpdate(Input&);	// 通常状態
	void FadeOutUpdate(Input&);	// フェードアウト状態

	// 描画関数
	void FadeDraw();	// フェード中描画
	void NormalDraw();	// 非フェード描画
};

