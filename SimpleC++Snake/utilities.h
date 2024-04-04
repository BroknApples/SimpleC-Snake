#ifndef UTILITIES_H
#define UTILITIES_H

#include <Windows.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <thread>
#include <utility>
#include <array>
#include <random>

//******************Typedefs, Constexprs, & Defines******************
#define IS_DOWN(b) inputs.buttons[b].is_down
#define PRESSED(b) inputs.buttons[b].is_down && inputs.buttons[b].changed

typedef unsigned int uint32;

// VK codes
constexpr uint32 VK_A = 0x41;
constexpr uint32 VK_B = 0x42;
constexpr uint32 VK_C = 0x43;
constexpr uint32 VK_D = 0x44;
constexpr uint32 VK_E = 0x45;
constexpr uint32 VK_F = 0x46;
constexpr uint32 VK_G = 0x47;
constexpr uint32 VK_H = 0x48;
constexpr uint32 VK_I = 0x49;
constexpr uint32 VK_J = 0x4A;
constexpr uint32 VK_K = 0x4B;
constexpr uint32 VK_L = 0x4C;
constexpr uint32 VK_M = 0x4D;
constexpr uint32 VK_N = 0x4E;
constexpr uint32 VK_O = 0x4F;
constexpr uint32 VK_P = 0x50;
constexpr uint32 VK_Q = 0x51;
constexpr uint32 VK_R = 0x52;
constexpr uint32 VK_S = 0x53;
constexpr uint32 VK_T = 0x54;
constexpr uint32 VK_U = 0x55;
constexpr uint32 VK_V = 0x56;
constexpr uint32 VK_W = 0x57;
constexpr uint32 VK_X = 0x58;
constexpr uint32 VK_Y = 0x59;
constexpr uint32 VK_Z = 0x5A;

// tilemap
constexpr int tilemapSizeX = 15;
constexpr int tilemapSizeY = 15;

// colors
constexpr uint32 LIGHTGREEN = 0x007a21;
constexpr uint32 SLIGHTLYDARKGREEN = 0x00b515;
constexpr uint32 DARKGREEN = 0x0f3814;
constexpr uint32 DARKERGREEN = 0x003900;
constexpr uint32 DARKESTGREEN = 0x002000;
constexpr uint32 BEAUTIFULBLUE = 0x262afd;


//******************Typedefs, Constexprs, & Defines******************

//******************Structs/Classes******************
struct RenderState {
	int width, height;
	void* memory;
	BITMAPINFO bitmap_info;
};
//******************Structs/Classes******************

//******************Functions*****************
uint32 calculateTileColor(const int xPos, const int yPos);
int getFPS();

template <typename T1, typename T2, typename T3> inline T2 clamp(T1 rendererMin, T2 val, T3 rendererMax) {
	if		(val < rendererMin) return static_cast<T2>(rendererMin);
	else if (val > rendererMax) return static_cast<T2>(rendererMax);
	else				return val;
}
//******************Functions******************

//******************Global Variables******************
extern RenderState renderer;
extern bool running;
extern float scale;
extern float velocityScaleX;
extern float velocityScaleY;
extern std::array<std::array<uint32, tilemapSizeY>, tilemapSizeX> tilemap;
extern uint32 runNumber;
//******************Global Variables******************

#endif