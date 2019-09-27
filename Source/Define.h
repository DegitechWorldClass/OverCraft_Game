#pragma once
#include "DXUT.h"

class CRect;
class CSphere;
class CBox;

using Vector2	= D3DXVECTOR2;
using Vector3	= D3DXVECTOR3;
using Vector4	= D3DXVECTOR4;
using Matrix	= D3DXMATRIX;
using Color		= D3DCOLOR;
using Rect		= CRect;
using String	= string;
using WString	= wstring;
using Sphere	= CSphere;
using Box		= CBox;
using Quaternion = D3DXQUATERNION;
using Shader = ID3DXEffect;
using LPShader = LPD3DXEFFECT;

using CRWString = const WString&;
using CRString	= const string&;
using CRVector2 = const Vector2&;
using CRVector3 = const Vector3&;
using CRVector4 = const Vector4&;
using CRMatrix	= const Matrix&;
using CRRect	= const Rect&;
using CRSphere	= const CSphere&;
using CRBox		= const CBox&;

using Second = chrono::duration<double>;
using namespace chrono;

const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR        RED(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

const D3DXCOLOR DESERT_SAND(D3DCOLOR_XRGB(250, 205, 135));
const D3DXCOLOR BEACH_SAND(D3DCOLOR_XRGB(255, 249, 157));

const D3DXCOLOR LIGHTGREEN(D3DCOLOR_XRGB(60, 184, 120));
const D3DXCOLOR  PUREGREEN(D3DCOLOR_XRGB(0, 166, 81));
const D3DXCOLOR  DARKGREEN(D3DCOLOR_XRGB(0, 114, 54));

const D3DXCOLOR LIGHT_YELLOW_GREEN(D3DCOLOR_XRGB(124, 197, 118));
const D3DXCOLOR  PURE_YELLOW_GREEN(D3DCOLOR_XRGB(57, 181, 74));
const D3DXCOLOR  DARK_YELLOW_GREEN(D3DCOLOR_XRGB(25, 123, 48));

const D3DXCOLOR LIGHTBROWN(D3DCOLOR_XRGB(198, 156, 109));
const D3DXCOLOR DARKBROWN(D3DCOLOR_XRGB(115, 100, 87));

using TimePoint = system_clock::time_point;
#define SCREEN_CENTER Vector2(WINSIZEX/2.f,WINSIZEY/2.f)

#define g_Device DXUTGetD3D9Device()
#define DeltaTime DXUTGetElapsedTime()
#define FixedDeltaTime 0.02

#if _DEBUG || DEBUG
#else 
#endif
#pragma comment (linker , "/entry:wWinMainCRTStartup /subsystem:console")
#define VERTEXFVF D3DFVF_XYZ | D3DFVF_NORMAL| D3DFVF_TEX1

#define DEBUG_LOG cout << endl; cout << "DEBUG_LOG :: "; printf        
