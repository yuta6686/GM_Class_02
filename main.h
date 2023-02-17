#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include "input.h"

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#ifdef _DEBUG
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
#else
    #define DBG_NEW new
#endif

#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

#pragma warning(pop)



#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//�V�F�[�_�[�̃R���p�C��
#include <d3dcompiler.h>
//�x�N�g����FLOAT3�ȂǕ֗��ȎZ�p���C�u����
#include <DirectXMath.h>
//�f�o�C�X�̊Ǘ������₷�����邽�߂�DirectX�ł̃X�}�[�g�|�C���^�̂悤�Ȃ���
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;
using namespace DirectX;


#define SCREEN_WIDTH	(960*2)
#define SCREEN_HEIGHT	(540*2)


HWND GetWindow();
char* GetDebugStr(void);
