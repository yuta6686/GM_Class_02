#pragma once

#include <xaudio2.h>
#include "gameObject.h"


class Audio : public GameObject
{
private:
	static IXAudio2* m_Xaudio;
	static IXAudio2MasteringVoice* m_MasteringVoice;

	IXAudio2SourceVoice* m_SourceVoice;
	BYTE* m_SoundData;

	int						m_Length;
	int						m_PlayLength;

	float m_Volume;//	(0.0f ～ 1.0f)
	float m_Pitch;
	float m_sourceRate = 1024.0f;
	float m_targetRate = 1024.0f;

public:
	static void InitMaster();
	static void UninitMaster();

	void Init() {};
	void Uninit();
	void Update() {};
	void Draw() {};

	void Load(const char* FileName);
	void Play(bool Loop = false);

//	ボリューム
	void SetAudioVolume(const float& vol) {
		if (m_SourceVoice == nullptr)return;
		m_SourceVoice->SetVolume(vol);
	}

	void VolumeUp(const float& vol) {
		if (m_SourceVoice == nullptr)return;
		if (m_Volume + vol > 1.0f) {
			m_Volume = 1.0f;
		}
		m_Volume += vol;
		SetAudioVolume(m_Volume);
	}
	
	void VolumeDown(const float& vol) {
		if (m_SourceVoice == nullptr)return;
		if (m_Volume - vol < 0.0f) {
			m_Volume = 0.0f;
		}
		m_Volume -= vol;
		SetAudioVolume(m_Volume);
	}
//	ピッチ
	void SetAudioPitch(const float& pit) {
		if (m_SourceVoice == nullptr)return;
		if (pit < 0.0f || pit > 1.0f)return;
		m_SourceVoice->SetFrequencyRatio(pit);
	}

	void PitchUp(const float& pit) {
		if (m_SourceVoice == nullptr)return;
		if (m_sourceRate + pit > 1024.0f) {
			m_sourceRate = 1024.0f;
		}
		m_sourceRate += pit;
		m_Pitch = m_sourceRate / m_targetRate;
		SetAudioPitch(m_Pitch);
	}
	void PitchDown(const float& pit) {
		if (m_SourceVoice == nullptr)return;
		if (m_sourceRate - pit < 1.0f / 1024.0f) {
			m_sourceRate = 1.0f / 1024.0f;
		}
		m_sourceRate -= pit;
		m_Pitch = m_sourceRate / m_targetRate;
		SetAudioPitch(m_Pitch);
	}

};

