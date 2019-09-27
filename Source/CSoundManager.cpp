#include "DXUT.h"
#include "CSoundManager.h"
const int MAX_PLAY_CHANNEL = 12;

CSoundManager::CSoundManager()
{
	System_Create(&m_pSystem);
	m_pSystem->init(MAX_PLAY_CHANNEL, FMOD_INIT_NORMAL, 0); // 동시 재생 채널 수

}


CSoundManager::~CSoundManager()
{
	for (auto iter : m_mapSound)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapSound.clear();
	m_pSystem->release();
}

void CSoundManager::AddSound(CRString _Key, CRString _Path,SoundType _sndType)
{
	auto find = m_mapSound.find(_Key);
	if (find == m_mapSound.end())
	{
		Sound * _pSound;
		Channel * _pChannel;

		m_pSystem->createSound(_Path.c_str(), FMOD_DEFAULT, 0, &_pSound);

		m_mapSound.insert(make_pair(_Key, new CSound(_pSound, _pChannel, _sndType)));
	}
}

CSound * CSoundManager::FindSound(CRString _Key)
{
	auto find = m_mapSound.find(_Key);

	if (find != m_mapSound.end())
	{
		return find->second;
	}
}

void CSoundManager::Stop(CSound * _Key)
{
	_Key->m_pChannel->stop();
}

void CSoundManager::Stop(CRString _Key)
{
	auto find = m_mapSound.find(_Key);

	if (find != m_mapSound.end())
	{
		find->second->m_pChannel->stop();
	}
}

void CSoundManager::Play(CSound * _Key, bool _bRepeat)
{
	_Key->m_pSound->setMode(_bRepeat == true ? FMOD_LOOP_NORMAL : FMOD_DEFAULT);
	m_pSystem->playSound(_Key->m_pSound, NULL, false, &_Key->m_pChannel);
}

void CSoundManager::Play(CRString _Key, bool _bRepeat)
{

	auto find = m_mapSound.find(_Key);

	if (find != m_mapSound.end())
	{
		find->second->m_pSound->setMode(_bRepeat == true ? FMOD_LOOP_NORMAL : FMOD_DEFAULT);
		m_pSystem->playSound(find->second->m_pSound, NULL, false, &find->second->m_pChannel);
	}

}

void CSoundManager::SetTypeAllVolume(SoundType _Type, float _fVolume)
{
	for (auto iter : m_mapSound)
	{
		if (_Type == iter.second->m_Type)
		{
			iter.second->SetVolume(_fVolume);
		}
	}
}

void CSoundManager::Update()
{
	m_pSystem->update();
}
