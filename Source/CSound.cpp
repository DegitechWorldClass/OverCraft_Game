#include "DXUT.h"
#include "CSound.h"



CSound::CSound(Sound * _pSound, Channel * _pChannel, SoundType _sndType)
	: m_pSound(_pSound), m_pChannel(_pChannel), m_Type(_sndType)
{
}

CSound::~CSound()
{
	m_pSound->release();
}

bool CSound::IsPlaying()
{
	bool rtn;
	m_pChannel->isPlaying(&rtn);
	return rtn;;
}

void CSound::Pause()
{
	m_pChannel->setPaused(TRUE);
}

void CSound::Resume()
{
	m_pChannel->setPaused(FALSE);
}

void CSound::SetVolume(float Volume)
{
	m_pChannel->setVolume(Volume);
}

void CSound::Stop()
{
	m_pChannel->stop();
}

void CSound::Play(bool _bRepeat)
{
	SOUND.Play(this,_bRepeat);
}
