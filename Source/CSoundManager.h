#pragma once
#include "CSingleton.h"

class CSoundManager :
	public CSingleton< CSoundManager>
{
public:
	CSoundManager();
	~CSoundManager();
	void AddSound(CRString _Key, CRString _Path, SoundType _sndType);

	CSound * FindSound(CRString _Key);

	void Stop(CSound * _Key);
	void Stop(CRString _Key);

	void Play(CSound * _Key, bool _bRepeat);
	void Play(CRString _Key, bool _bRepeat);

	void SetTypeAllVolume(SoundType _Type, float _fVolume);

	void Update();
private:
	System * m_pSystem;

	map<string, CSound*> m_mapSound;
	

};

#define SOUND (*CSoundManager::GetInstance())


