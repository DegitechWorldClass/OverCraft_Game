#pragma once
#include "CScene.h"
class CMainScene :
	public CScene
{
public:
	CMainScene();
	~CMainScene();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

