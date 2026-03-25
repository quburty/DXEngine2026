#pragma once

//Windows
#include <Windows.h>
#include <cassert>
#include <wincodec.h>

//DX Header
#include <d3d11.h>
//#include <D3DX11.h>
//#include <D3DX10.h>
//#include <D3DX10math.h>
#include <d3dcompiler.h>

//DX Library
#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "d3dx11.lib")
//#pragma comment(lib, "d3dx10.lib")
//#pragma comment(lib, "dxguid.lib")

//STL
#include <valarray>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include <utility>
#include <map>
#include <set>

//Macro
#define SAFE_FREE(p) {if(p!=nullptr){ free(p); p=nullptr;}}
#define SAFE_DELETE(p) {if(p!=nullptr){delete p; p=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p!=nullptr){delete[] p; p=nullptr;}}
#define SAFE_RELEASE(p) {if(p!=nullptr){p->Release(); p=nullptr;}}

#define Check(p) {assert(SUCCEEDED(p));}
#define CheckNull(p) {if(p==NULL) return;}
#define CheckNullResult(p, result) {if(p==NULL) return result;}
#define CheckTrue(p) {if(p==true) return;}
#define CheckTrueResult(p, result) {if(p==true) return result;}
#define CheckFalse(p) {if(p==false) return;}
#define CheckFalseResult(p, result) {if(p==false) return result;}

#define Super __super

typedef unsigned int uint;

//System
#include "System/Window.h"