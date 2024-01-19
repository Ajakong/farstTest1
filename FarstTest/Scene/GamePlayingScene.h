#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <map>


class Charactor;
class ControllerCharactor;
class Actor;
class File;

enum class PlayerType;

class GamePlayingScene : public Scene
{
public:
    GamePlayingScene(SceneManager& manager);
    ~GamePlayingScene();
    virtual void Update(Input& input);
    virtual void Draw();

private:
    std::shared_ptr<File> m_imgFile;
    std::shared_ptr<File> m_btnImg;
    std::shared_ptr<ControllerCharactor> m_hero;
    std::shared_ptr<ControllerCharactor> m_monk;

    std::vector<std::shared_ptr<Actor>> m_actors;

    int m_btnFrame = 0;
    int m_frame = 0;
    int m_digits;
    float m_fps = 0.0f;

    // メンバ関数ポインタの宣言
    using UpdateFunc_t = void (GamePlayingScene::*)(Input&);
    using DrawFunc_t = void (GamePlayingScene::*)();
    UpdateFunc_t m_updateFunc = nullptr;
    DrawFunc_t m_drawFunc = nullptr;

    // 更新関数
    void FadeInUpdate(Input& input);
    void NormalUpdate(Input& input);
    void FadeOutUpdate(Input& input);

    // 描画関数
    void FadeDraw();
    void NormalDraw();
};

