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

    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = void (GameOverScene::*)(Input&);
    using DrawFunc_t = void (GameOverScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // �X�V��Ԃ�\���֐�
    void FadeInUpdate(Input&);
    void NormalUpdate(Input& input);
    void FadeOutUpdate(Input&);

    // �`���Ԃ�\���֐�
    void FadeDraw();
    void NormalDraw();
};

