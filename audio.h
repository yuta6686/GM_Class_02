#pragma once

#include <vector>
#include <xaudio2.h>
#include "gameObject.h"

//#define STREAMING_BUFFER_SIZE 65536
//#define MAX_BUFFER_COUNT 3
//BYTE buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];

#define SOUND_SOURCE_MAX 50

class Audio : public GameObject
{
private:
	const float MAX_VOLUME = 1.0f;

	static IXAudio2* m_Xaudio;
	static IXAudio2MasteringVoice* m_MasteringVoice;	
	
	std::vector<IXAudio2SourceVoice*> m_SourceVoices;
	BYTE* m_SoundData;

	int						m_Length;
	int						m_PlayLength;
	int						m_Index;

	float m_Volume;//	(0.0f ～ 1.0f)
	float m_Pitch;
	float m_sourceRate = 1024.0f;
	float m_targetRate = 1024.0f;
	float m_curVolume;
	float m_curSourceRate;
	
public:
	static void InitMaster();
	static void UninitMaster();

	void Init() {
		m_SourceVoices.resize(SOUND_SOURCE_MAX);
		m_Volume = 1.0f;
		m_curVolume = 1.0f;
		m_curSourceRate = 1024.0f;
	};
	void Uninit();
	void Update() {
		if (m_curSourceRate != m_sourceRate) {
			PitchUp(0.0f);
		}
		if (m_curVolume != m_Volume) {
			VolumeUp(0.0f);
		}

		m_curSourceRate = m_sourceRate;
		m_curVolume = m_Volume;
	};
	void Draw() {};

	void DrawImgui() override {		

		if (ImGui::TreeNode("Volume")) {			
			ImGui::ProgressBar(m_Volume);
			ImGui::SliderFloat("Volume", &m_Volume, 0.0f, 1.0f, "%.1f");
			ImGui::TreePop();
		}
		
		

		if (ImGui::TreeNode("SourceRate")) {
			ImGui::ProgressBar(m_sourceRate / m_targetRate);
			ImGui::SliderFloat("sourceRate", &m_sourceRate, 0.0f, 1024.0f, "%.1f");
			ImGui::TreePop();
		}
		

	}

	void Load(const char* FileName);
	void Play(bool Loop = false);

//	ボリューム
	//	0.0f～1.0f
	void SetAudioVolume(const float& vol) {
		for (int j = 0; j < SOUND_SOURCE_MAX; j++) {
			if (IsNowPlay(j) == false)continue;			
			m_SourceVoices[j]->SetVolume(vol);
		}
	}

	void VolumeUp(const float& vol) {		
		if (m_Volume + vol > MAX_VOLUME) {
			m_Volume = MAX_VOLUME;
		}
		m_Volume += vol;
		SetAudioVolume(m_Volume);
	}
	
	void VolumeDown(const float& vol) {		
		if (m_Volume - vol < 0.0f) {
			m_Volume = 0.0f;
		}
		m_Volume -= vol;
		SetAudioVolume(m_Volume);
	}
//	ピッチ
	void SetAudioPitch(const float& pit) {		
		if (pit < 0.0f || pit > 1.0f)return;
		for (int j = 0; j < SOUND_SOURCE_MAX; j++) {
			if (IsNowPlay(j) == false)continue;
			m_SourceVoices[j]->SetFrequencyRatio(pit);
		}		
	}

	void PitchUp(const float& pit) {		
		if (m_sourceRate + pit > 1024.0f) {
			m_sourceRate = 1024.0f;
		}
		m_sourceRate += pit;
		m_Pitch = m_sourceRate / m_targetRate;
		SetAudioPitch(m_Pitch);
	}
	void PitchDown(const float& pit) {		
		if (m_sourceRate - pit < 1.0f / 1024.0f) {
			m_sourceRate = 1.0f / 1024.0f;
		}
		m_sourceRate -= pit;
		m_Pitch = m_sourceRate / m_targetRate;
		SetAudioPitch(m_Pitch);
	}

	bool IsNowPlay(const int& index) {
		XAUDIO2_VOICE_STATE xa2state;
		m_SourceVoices[index]->GetState(&xa2state);

		//	0じゃなかったら再生中
		if (xa2state.BuffersQueued != 0)return true;
		return false;
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

	void SetSourceRate(float source) {
		m_sourceRate = source;
	}
};

