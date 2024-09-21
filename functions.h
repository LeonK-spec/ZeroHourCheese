#pragma once
#include "vec.h"
#include "vec2.h"
#include <string>
#include "il2cpp_resolver.hpp"
#include "Lists.hpp"
#include <intrin.h>
#include <cmath>
#include <limits>
namespace Functions
{
#pragma region Hooks
	//void(UNITY_CALLING_CONVENTION SetTargetRecoil)(CombatMaster_Battle_Gameplay_Player_PlayerMovement_o*, float);
	//void SetTargetRecoil_hk(CombatMaster_Battle_Gameplay_Player_PlayerMovement_o* movement, float recoil)
	//{
	//	if (vars::recoileditor)
	//	{
	//		recoil = vars::recoiledited; // 0.0f
	//	}

	//	return SetTargetRecoil(movement, recoil);
	//}
#pragma endregion

#pragma region Game Functions
	// UnityEngine_Camera$$Get_Main
	Unity::CCamera* GetMainCamera()
	{
		Unity::CCamera* (UNITY_CALLING_CONVENTION get_main)();
		return reinterpret_cast<decltype(get_main)>(sdk::GameAssembly + 0x0)();
	}
#pragma endregion

#pragma region Custom Functions
	bool worldtoscreen(Unity::Vector3 world, Vector2& screen)
	{
		Unity::CCamera* CameraMain = Unity::Camera::GetMain(); // Get The Main Camera
		if (!CameraMain) {
			return false;
		}

		//Unity::Vector3 buffer = WorldToScreenPoint(CameraMain, world, 2);

		Unity::Vector3 buffer = CameraMain->CallMethodSafe<Unity::Vector3>("WorldToScreenPoint", world, Unity::eye::mono); // Call the worldtoscren function using monoeye (2)

		if (buffer.x > vars::screen_size.x || buffer.y > vars::screen_size.y || buffer.x < 0 || buffer.y < 0 || buffer.z < 0) // check if point is on screen
		{
			return false;
		}

		if (buffer.z > 0.0f) // Check if point is in view
		{
			screen = Vector2(buffer.x, vars::screen_size.y - buffer.y);
		}

		if (screen.x > 0 || screen.y > 0) // Check if point is in view
		{
			return true;
		}
	}





	void cleanshit() {
		while (true) {
			Unity::CGameObject* anti = Unity::GameObject::Find("Anti-Cheat Toolkit");
			if (anti) {
				printf("[ZH]-> Found...\n");
				anti->Destroy();
				printf("[ZH]-> Destroyed that shii\n");

			}
			Unity::CGameObject* error = Unity::GameObject::Find("ErrorPrompt");
			if (error) {
				printf("[ZH]-> Found Error Prompt\nDestroying...\n");
				error->Destroy();
				printf("[ZH]-> Destroyedd\n");
			}
			Unity::CGameObject* GameManagerObj = Unity::GameObject::Find("GameManager");
			if (GameManagerObj) {

				GameManager = GameManagerObj;
			}
			Sleep(1000);
		}
	}

	


	void AI_Cache()
	{
		while (true)
		{
			if (!vars::initil2cpp)
				continue;
			void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());
			AIList.clear();
			try {
				auto list = Unity::Object::FindObjectsOfType<Unity::CComponent>("ZH_AINav");

				for (int i = 0; i < list->m_uMaxLength; i++)
				{
					if (!list->operator[](i)) {
						continue;
					}

					AIList.push_back(list->operator[](i)->GetGameObject());
				}

				IL2CPP::Thread::Detach(m_pThisThread);
			}
			catch (...) {}

			Sleep(1000);
		}
	}



	void Player_Cache()
	{
		while (true)
		{
			if (!vars::initil2cpp)
				continue;

			void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());
			PlayerList.clear();

			try {
				

				auto list = Unity::Object::FindObjectsOfType<Unity::CComponent>("UserInput");

				if (list) {
					for (int i = 0; i < list->m_uMaxLength; i++)
					{
						if (list->operator[](i)) {
							PlayerList.push_back(list->operator[](i)->GetGameObject());
							auto ppp = list->operator[](i)->GetGameObject()->GetComponent("Photon.Pun.PhotonView");
							if (ppp) {
								auto contoller = ppp->CallMethodSafe<Unity::CComponent*>("get_Controller");
								if (contoller) {
									bool* isLocal = contoller->GetMemberValue<bool*>("IsLocal");
									if (isLocal) {
										LocalPlayer = list->operator[](i)->GetGameObject();
									}
										
								}
							}
							
							
							
						}
					}
				}

				IL2CPP::Thread::Detach(m_pThisThread);
			}
			catch (...) {
				
			}

			Sleep(7000);
		}
	}

	

	auto RectFilled(float x0, float y0, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags) -> VOID
	{
		auto vList = ImGui::GetBackgroundDrawList();
		vList->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
	}
	auto HealthBar(float x, float y, float w, float h, int phealth, ImColor col) -> VOID
	{
		auto vList = ImGui::GetBackgroundDrawList();

		int healthValue = max(0, min(phealth, 100));

		int barColor = ImColor
		(min(510 * (100 - healthValue) / 100, 255), min(510 * healthValue / 100, 255), 25, 255);
		vList->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), col);
		RectFilled(x, y, x + w, y + (((float)h / 100.0f) * (float)phealth), barColor, 0.0f, 0);
	}


#pragma endregion
}