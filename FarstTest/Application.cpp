#include "Application.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "FileSystem/FileManager.h"
#include "Input.h"

#include <DxLib.h>
#include <cassert>

namespace 
{
    constexpr int kScreenWidth = 640;
    constexpr int kScreenHeight = 480;
}

int MyLoadGraph(const wchar_t* path)
{
    int handle = LoadGraph(path);
    assert(handle != -1);
    return handle;
}

Application::Application()
{
    m_windowSize = Size{kScreenWidth, kScreenHeight};
}

void Application::Terminate()
{
    DxLib_End();
}

float Application::GetGravity() const
{
    return 0.5f;
}

bool Application::Init()
{
    ChangeWindowMode(true); // ウィンドウモードにします
    SetGraphMode(m_windowSize.w, m_windowSize.h, 1);
    SetWindowText(L"ごっついアクションゲーム");
    if (DxLib_Init() == -1)
    {
        return false;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    return true;
}

void Application::Run()
{
    {// スコープを強制的に作っている
        FileManager fileManager;
        SceneManager sceneManager(fileManager);
        sceneManager.ChangeScene(std::make_shared<TitleScene>(sceneManager));
        Input input;

        LONGLONG time;
        while (ProcessMessage() != -1)
        {
            // FPSの固定ように開始時の時間を取得
            time = GetNowHiPerformanceCount();

            ClearDrawScreen();
            input.Update(); // 入力を更新
            sceneManager.Update(input);
            sceneManager.Draw();
            ScreenFlip();

            // 60FPSに固定
            while (16667 > GetNowHiPerformanceCount() - time) {};
        }
    }
    Terminate();
}

const Size& Application::GetWindowSize() const
{
    return m_windowSize;
}
