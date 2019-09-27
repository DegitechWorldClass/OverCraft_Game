#include "DXUT.h"
#include "CMainScene.h"
#include "CPlayerMovement.h"

CMainScene::CMainScene()
{
	
}


CMainScene::~CMainScene()
{
}

void CMainScene::Init()
{
	
	auto Test = OBJECT.AddObject();
	Test->AddComponent<CMeshRenderer>();
	Test->AddComponent<CAnimation3D>();
	Test->GetComponent<CAnimation3D>()->AddAnimator("IDLE", "PLAYER_IDLE", 0.01f, true);
	Test->GetComponent<CAnimation3D>()->AddAnimator("RUN", "PLAYER_RUN", 0.01f, true);
	Test->GetComponent<CAnimation3D>()->AddAnimator("SWINGA", "PLAYER_SWINGA", 0.014f, false);
	Test->GetComponent<CAnimation3D>()->AddAnimator("SWINGB", "PLAYER_SWINGB", 0.014f, false);
	Test->GetComponent<CAnimation3D>()->AddAnimator("SWINGC", "PLAYER_SWINGC", 0.014f, false); 
		Test->GetComponent<CAnimation3D>()->AddAnimator("DASH", "PLAYER_DASH", 0.012f, false); 
		Test->GetComponent<CAnimation3D>()->SetHandleAnimator("IDLE");
		Test->AddComponent<CRigidBody3D>();

	Test->AddComponent<CPlayerMovement>();


	Test->GetComponent<CMeshRenderer>()->SetModel(MODEL["PLAYER_IDLE (1)"]);


	auto Test2 = OBJECT.AddObject();
	Test2->Transform->SetPosition(Vector3(0, 0, 1));
	Test2->AddComponent<CMeshRenderer>();
	Test2->AddComponent<CAnimation3D>();
	Test2->GetComponent<CAnimation3D>()->AddAnimator("IDLE", "PLAYER_IDLE", 0.025f, true);
	Test2->GetComponent<CAnimation3D>()->AddAnimator("RUN", "PLAYER_RUN", 0.01f, true);
	Test2->GetComponent<CAnimation3D>()->SetHandleAnimator("IDLE");
	Test2->GetComponent<CMeshRenderer>()->SetModel(MODEL["PLAYER_IDLE (1)"]);

	auto Test3 = OBJECT.AddObject("Map");
	Test3->Transform->SetPosition(Vector3(0, 0, 0));
	Test3->AddComponent<CTerrain>()->CreateHeightMap("./resource/Map/coastMountain64.raw", 64, 64, 20, 1.f);
	Test3->GetComponent<CTerrain>()->genTextrue(Vector3(0, 1, 0));
	


// 	Test3->GetComponent<CTerrain>()->


}

void CMainScene::Update()
{
}

void CMainScene::Render()
{
}

void CMainScene::Release()
{
}
