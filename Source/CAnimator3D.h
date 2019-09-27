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
	float m_fDelay; // 딜레이
	bool m_bLoop;	// 루프인지
	UINT m_iPlayCount; // 재생 시작 횟수 
	bool m_bEnable; // 애니메이션 활성화 상태인지
	
	string m_Key;   // Animation 컴포넌트에서 등록되어있는 Key값
	
	BYTE m_iCurFrame = 0;	// 인덱스 기준 현재 프레임
	BYTE m_iMaxFrame; // 인덱스 기준 최대 프레임

	vector<CModel*> m_Models; // 프레임 모델
	
	CTimer * m_pTimer = nullptr; // 타이머

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

