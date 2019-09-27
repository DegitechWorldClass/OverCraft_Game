#pragma once
class CScene abstract
{
	friend class CSceneManager;
public:
	CScene();
	virtual ~CScene();

protected:
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

