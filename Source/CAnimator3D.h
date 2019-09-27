#pragma once
class CTimer;
class CAnimator3D
{
	friend class CAnimation3D;
public:
	CAnimator3D();
	~CAnimator3D();

private:
	void Init(const string& _Key, float _fDelay, bool _bLoop);
	void Update();
	void Render();
	void Release();

private:
	float m_fDelay; // ������
	bool m_bLoop;	// ��������
	UINT m_iPlayCount; // ��� ���� Ƚ�� 
	bool m_bEnable; // �ִϸ��̼� Ȱ��ȭ ��������
	
	string m_Key;   // Animation ������Ʈ���� ��ϵǾ��ִ� Key��
	
	BYTE m_iCurFrame = 0;	// �ε��� ���� ���� ������
	BYTE m_iMaxFrame; // �ε��� ���� �ִ� ������

	vector<CModel*> m_Models; // ������ ��
	
	CTimer * m_pTimer = nullptr; // Ÿ�̸�

public:
	UINT GetPlayCount()
	{
		return m_iPlayCount;
	}
	float GetNormalizedTime()
	{
		return ((m_iCurFrame + 1)  / (m_iMaxFrame + 1));
	}
	bool operator ==(const string& _comp)
	{
		return _comp == this->m_Key;
	}
	string GetKey()
	{
		return m_Key;
	}
	float	GetDelay()
	{
		return m_fDelay;
	}
	void	SetDelay(float _fDelay)
	{
		m_fDelay = _fDelay;
	}

	bool	GetLoop()
	{
		return m_bLoop;
	}
	bool	SetLoop(bool _bLoop)
	{
		m_bLoop = _bLoop;
	}

	bool	GetEnable()
	{
		return m_bEnable;
	}
	bool	SetEnable(bool _bEnable)
	{
		m_bLoop = m_bEnable;
	}

	BYTE	GetCurFrame()
	{
		return m_iCurFrame;
	}
	void	SetCurFrame(BYTE _iCurFrame)
	{
		m_iCurFrame = _iCurFrame;
	}

	BYTE	GetMaxFrame()
	{
		return m_iMaxFrame;
	}

	CModel * GetFrameModel()
	{
		return m_Models[m_iCurFrame];
	}

};

