#pragma once
class   CRenderer2D abstract :
	public CComponent 
{
public:
	CRenderer2D();
	virtual ~CRenderer2D();

	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual void OnCollisionEnter(CObject * _pObject)	PURE;
	virtual void OnCollisionStay(CObject * _pObject)	PURE;
	virtual void OnCollisionExit(CObject * _pObject)	PURE;

protected:
	SortingLayer m_SortingLayer;
	int m_iOrderInLayer;
	bool  m_bIsInterFace;

public:
	bool GetIsInterFace() { return m_bIsInterFace; }
	void SetIsInterFace(bool _bIsInterFace) { m_bIsInterFace = _bIsInterFace; }

};

