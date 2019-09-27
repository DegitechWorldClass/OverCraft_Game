#pragma once

class CSound
{
public:
	CSound(Sound * _pSound, Channel * _pChannel,SoundType _sndType);
	~CSound();
	friend class CSoundManager;
public:
	bool IsPlaying();
	void Pause();
	void Resume();
	void SetVolume(float Volume);
	void Stop();
	void Play(bool _bRepeat);
private:
	SoundType m_Type;
	Channel * m_pChannel;
	Sound * m_pSound;
};

