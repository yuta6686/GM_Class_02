#pragma once

#include <vector>
#include <xaudio2.h>
#include "gameObject.h"

//#define STREAMING_BUFFER_SIZE 65536
//#define MAX_BUFFER_COUNT 3
//BYTE buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];

#define SOUND_SOURCE_MAX 10

class Audio : public GameObject
{
private:
	static IXAudio2* m_Xaudio;
	static IXAudio2MasteringVoice* m_MasteringVoice;
	static std::vector<IXAudio2MasteringVoice*> m_MasteringVoices;

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
	
	void Strmng() {

		//// OVERLAPPED 構造体を初期化します。
		//OVERLAPPED Overlapped = { 0 };
		//Overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		////ストリーミング オーディオを再生するソース音声で Start 関数を呼び出します。
		//HRESULT hr = m_SourceVoice->Start(0, 0);

		/*CurrentDiskReadBuffer = 0;
		CurrentPosition = 0;
		while (CurrentPosition < cbWaveSize)
		{
		
		}*/

		//	https://docs.microsoft.com/ja-jp/windows/win32/xaudio2/how-to--stream-a-sound-from-disk
	}
};

