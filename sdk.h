#pragma once
#include "il2cpp.h"
#include "vec.h"
#include "vec2.h"
#include <vector>
#include <utility> // for std::pair
bool show_menu = true;

namespace mem
{
	template<typename T> T read(uintptr_t address) {
		try { return *(T*)address; }
		catch (...) { return T(); }
	}

	template<typename T> void write(uintptr_t address, T value) {
		try { *(T*)address = value; }
		catch (...) { return; }
	}
}

namespace sdk
{
	uintptr_t Base;
	uintptr_t GameAssembly;
	uintptr_t UnityPlayer;

	void mousemove(float tarx, float tary, float X, float Y, int smooth)
	{
		float ScreenCenterX = (X / 2);
		float ScreenCenterY = (Y / 2);
		float TargetX = 0;
		float TargetY = 0;

		smooth = smooth + 3;

		if (tarx != 0)
		{
			if (tarx > ScreenCenterX)
			{
				TargetX = -(ScreenCenterX - tarx);
				TargetX /= smooth;
				if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
			}

			if (tarx < ScreenCenterX)
			{
				TargetX = tarx - ScreenCenterX;
				TargetX /= smooth;
				if (TargetX + ScreenCenterX < 0) TargetX = 0;
			}
		}

		if (tary != 0)
		{
			if (tary > ScreenCenterY)
			{
				TargetY = -(ScreenCenterY - tary);
				TargetY /= smooth;
				if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
			}

			if (tary < ScreenCenterY)
			{
				TargetY = tary - ScreenCenterY;
				TargetY /= smooth;
				if (TargetY + ScreenCenterY < 0) TargetY = 0;
			}
		}
		mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	}



	std::vector<std::pair<int, int>> bone_pairs = {
		// left leg
		{21, 6},
		{6, 4},
		{4, 2},
		{2, 7},

		// right leg
		{20, 5},
		{5, 3},
		{3, 1},
		{1, 7},

		//torso
		{10, 9},
		{9, 8},
		{8, 7},

		//left arm
		{19, 17},
		{17, 15},
		{15, 13},
		{13, 9},

		//right arm
		{18, 16},
		{16, 14},
		{14, 12},
		{12, 9},

		//Neck and head
		{24, 10} //24 is head ig
	};
}

namespace Offsets
{
	uintptr_t SetTargetRecoil = 0x0; // Use This to Hold Offsets for Functions


}

namespace vars
{
	inline static UINT vps = 1;
	Vector2 screen_size = { 0, 0 };
	Vector2 screen_center = { 0, 0 };
	D3D11_VIEWPORT viewport;
	bool initil2cpp = false;
	
	bool playerbones = false;
	bool aibones = false;
	bool aiesp = false;
	bool playeresp = false;
	bool SnaplineRainbow = false;
	bool aimbot = false;

	bool crosshair = false;
	bool crosshairRainbow = false;
	bool watermark = true;
	
	bool fov_check = true;
	bool fov_changer = false;

	bool infstamina = false;


	bool gunmod = false;
	bool instakill = false;

	bool crouchspeed = false;
	float crouchspeedfloat =  3.f;

	bool addbdtbooltoggle = false;
	bool usernamespoofer = false;
	int bdtint = 1;


	bool infinitestamina = false;
	bool infiniteammo = false;

	// todo
	bool recoileditor = true;
	float recoiledited = 0.0f;

	float Xrot = 0.0f;
	float Yrot = 0.0f;
	float ViewmodelFOV = 85.0f;

	// Floats
	float CameraFOV = 120.0f;
	float crosshairsize = 8.0f;
	float smooth = 1;
	float aim_fov = 60.0f;

	// Ints
	int linetype = 1;
	int currentplayeridx = 0;
	int currentAIidx = 0;

	static char username[14];

	// Colors
	ImColor CrossColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor PlayerNameColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor skeletonESPCol = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor PlayerSnaplineColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor PlayerHealthbarColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor SelfChamsColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor ChamsColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor ItemNameColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor ItemSnaplineColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor boxESPCol = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImColor hitdebugcol = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	ImVec4 Rainbow = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	Vector3 PlayerPos = { 0, 0, 0 };

	const char* bones[]{ "Head", "Chest" };
	int boneselected = 0;

}
