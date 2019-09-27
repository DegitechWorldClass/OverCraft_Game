#include "DXUT.h"
#include "CLoadScene.h"

#include "CMainGame.h"
#include "CMainScene.h"


CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}

void CMainGame::Init()
{
	SCENE.AddScene("S_LOADING", new CLoadScene());

	SCENE.AddScene("S_MAIN", new CMainScene());

	SCENE.ChangeScene("S_LOADING");
}

void CMainGame::Update()
{
	INPUT.Update();

	CAMERA.Update();

	OBJECT.Update();

	TIME.Update();

	SCENE.Update();

	SOUND.Update();
}

void CMainGame::Render()
{
	CAMERA.SetTransform();

	IMAGE.Begin(FALSE);

	OBJECT.Render();
	
	SCENE.Render();

	IMAGE.End();

	IMAGE.Begin(TRUE);

	TCHAR FPS_MSG[50];

	swprintf(FPS_MSG, L"FPS : %.f",DXUTGetFPS());
	IMAGE.PrintText(FPS_MSG, Vector2(0, 0), 80, 0.f, false, D3DCOLOR_ARGB(255, 255, 255, 255));
	IMAGE.End();
}

void CMainGame::Release()
{
	CPhysic::ReleaseInstance();
	CInputManager::ReleaseInstance();
	CImageManager::ReleaseInstance();
	CObjectManager::ReleaseInstance();
	CSceneManager::ReleaseInstance();
	CTimeManager::ReleaseInstance();
	CCameraManager::ReleaseInstance();
	CSoundManager::ReleaseInstance();
	CModelManager::ReleaseInstance();
}

void CMainGame::OnResetDevice()
{
	IMAGE.OnResetDevice();
}

void CMainGame::OnLostDevice()
{
	IMAGE.OnLostDevice();
}
