#pragma once
#include "Scene.h"
class File;
class GameOverScene : public Scene
{
public:
    GameOverScene(SceneManager& mgr);
    ~GameOverScene();
    virtual void Update(Input& input);
    virtual void Draw();

private:
    std::shared_ptr<File> m_imgFile;
    std::shared_ptr<File> m_btnImg;
    int m_btnFrame = 0;
    int m_frame;

    // メンバ関数ポインタの宣言
    using UpdateFunc_t = void (GameOverScene::*)(Input&);
    using DrawFunc_t = void (GameOverScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // 更新状態を表す関数
    void FadeInUpdate(Input&);
    void NormalUpdate(Input& input);
    void FadeOutUpdate(Input&);

    // 描画状態を表す関数
    void FadeDraw();
    void NormalDraw();
};

