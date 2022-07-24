#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include "input.h"

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"



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


//シェーダーのコンパイラ
#include <d3dcompiler.h>
//ベクトルやFLOAT3など便利な算術ライブラリ
#include <DirectXMath.h>
//デバイスの管理をしやすくするためのDirectX版のスマートポインタのようなもの
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;
using namespace DirectX;

#include <memory>
#include <vector>
#include <list>
#include <string>
#include <map>

#define SCREEN_WIDTH	(960*2)
#define SCREEN_HEIGHT	(540*2)


HWND GetWindow();
char* GetDebugStr(void);

struct Point {
	int x, y;
};

Point GetMousePosition();