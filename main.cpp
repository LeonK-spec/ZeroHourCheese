#include "includes.h"
#include "Rendering.hpp"
#include "Font.h"
#include "sdk.h"
#include "Menu.h"
#include "Hooks.h"
#include "Functions.h"
#include "kiero/minhook/include/MinHook.h"
#include "il2cpp_resolver.hpp"
#include "Lists.hpp"
#include "Callback.hpp"
#include <Utils/VFunc.hpp>
#include <iostream>
#include <PaternScan.hpp>
#include <intrin.h>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void CreateConsole() {
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	SetConsoleTitle("IL2CPP");
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
}

void initvars() {
	if (IL2CPP::Initialize(true)) {
		printf("[ DEBUG ] Il2Cpp initialized\n");
	}
	else {
		printf("[ DEBUG ] Il2Cpp initialize failed, quitting...");
		Sleep(300);
		exit(0);
	}
	sdk::Base = (uintptr_t)GetModuleHandleA(NULL);
	printf("[ DEBUG ] Base Address: 0x%llX\n", sdk::Base);
	sdk::GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
	printf("[ DEBUG ] GameAssembly Base Address: 0x%llX\n", sdk::GameAssembly);
	sdk::UnityPlayer = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");
	printf("[ DEBUG ] UnityPlayer Base Address: 0x%llX\n", sdk::UnityPlayer);
	printf("----------------------------------------------------------\n");
	printf("\n");
}

void Log(uintptr_t address, const char* name) {
	printf("[ LOG ] %s: 0x%llX\n", name, address);
}
#define DEBUG // undefine in release

bool find_sigs() {
	return true;
}

void EnableHooks() {
	MH_CreateHook(reinterpret_cast<void*>((uintptr_t)(GetModuleHandle("GameAssembly.dll")) + 0x6E3E40), &hooks::userinputupdate, (void**)&hooks::userinputupdate_og);//UserInput$$Update
	MH_CreateHook(reinterpret_cast<void*>((uintptr_t)(GetModuleHandle("GameAssembly.dll")) + 0x4A5930), &hooks::gamenetworksupdate, (void**)&hooks::gamenetworksupdate_og);//GameNetworks$$Update
	MH_CreateHook(reinterpret_cast<LPVOID*>((uintptr_t)(GetModuleHandle("GameAssembly.dll")) + 0x526B30), &hooks::set_fov_Hook, (void**)&hooks::set_fov_o); //GameSettings$$UpdateGameFOV
	MH_EnableHook(MH_ALL_HOOKS);
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProcA(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;




static DWORD lastShotTime = 0;
static DWORD lasttick = 0;


void renderloop()
{
	DWORD currentTime = GetTickCount64(); // Get current time in milliseconds

	if (!vars::initil2cpp)
		return;

	if (LocalPlayer != NULL)
	{
		auto wm_script = LocalPlayer->GetComponent("WeaponManag");
		if (!wm_script)
			return;
		auto curweapon = wm_script->GetMemberValue<Unity::CComponent*>("CurrentWeapon");
		if (!curweapon)
			return;
		auto properties = curweapon->GetMemberValue<Unity::CComponent*>("Properties");
		if (!properties)
			return;

		if (vars::gunmod) {
			properties->SetMemberValue<float>("recoilAmount",0.f);
			properties->SetMemberValue<float>("MaxSpray", 0.1f);
			properties->SetMemberValue<float>("MinSpray", 0.0f);
			properties->SetMemberValue<float>("upwardKick", 0.f);
			properties->SetMemberValue<float>("upwardKickSpeed", 0.f);
			properties->SetMemberValue<float>("Speed", 1000.f);

			curweapon->SetMemberValue<float>("ex_Spread", 0.0f);
			curweapon->SetMemberValue<float>("ex_Recoil", 0.0f);
			curweapon->SetMemberValue<float>("currentRecoilZPos", 0.0f);
			curweapon->SetMemberValue<float>("currentRecoilZPosV", 0.0f);

		}
		if (vars::instakill) {
			curweapon->SetMemberValue<float>("ex_Dmg", 700.f);

			properties->SetMemberValue<int>("BulletsPerShot", 4);
		}
	}




	if (vars::crosshair)
	{
		ImColor coltouse = vars::CrossColor;
		if (vars::crosshairRainbow)
		{
			coltouse = ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z);
		}
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(vars::screen_center.x - vars::crosshairsize, vars::screen_center.y), ImVec2((vars::screen_center.x - vars::crosshairsize) + (vars::crosshairsize * 2), vars::screen_center.y), coltouse, 1.2f);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(vars::screen_center.x, vars::screen_center.y - vars::crosshairsize), ImVec2(vars::screen_center.x, (vars::screen_center.y - vars::crosshairsize) + (vars::crosshairsize * 2)), coltouse, 1.2f);
	}

	if (vars::fov_check)
	{
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(vars::screen_center.x, vars::screen_center.y), vars::aim_fov, ImColor(255, 255, 255), 360);
	}
	



	if (AIList.size() > 0)
	{

		for (int i = 0; i < AIList.size(); i++)
		{
			if (!AIList[i]) // Verify that the player is valid
				continue;
			vars::currentAIidx = i;



			auto playerPosition = AIList[vars::currentAIidx]->GetTransform()->GetPosition();
			
			auto curAI = AIList[vars::currentAIidx]->GetComponent("ZH_AINav");

			if (!curAI)
				continue;

			auto manualreference = curAI->GetMemberValue<Unity::CComponent*>("ManualReference");

			if (!manualreference)
				continue;

			auto curAIAnim = manualreference->GetMemberValue<Unity::CComponent*>("anim");

			auto healthScript = manualreference->GetMemberValue<Unity::CComponent*>("healthScript");

			

		


			bool* isalive = healthScript->GetMemberValue<bool*>("alive");
			bool* isarrested = curAI->GetMemberValue<bool*>("GotArrested");
			bool* isaggresive = curAI->GetMemberValue<bool*>("hostile");
			bool* isobjective = curAI->GetMemberValue<bool*>("isObjective");


			if (!isalive) {
				continue;
			}

			
			if (vars::aiesp)
			{
				Unity::Vector3 root_pos = playerPosition;
				root_pos.y -= 0.2f;
				Vector2 pos;
				if (Functions::worldtoscreen(root_pos, pos)) {
					ImColor Colortouse = vars::PlayerSnaplineColor;
					if (vars::SnaplineRainbow)
						Colortouse = ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z);
					switch (vars::linetype)
					{
					case 1:
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(vars::screen_center.x, vars::screen_size.y), ImVec2(pos.x, pos.y), Colortouse, 1.5f);
						break;
					case 2:
						ImGui::GetBackgroundDrawList()->AddRect(ImVec2(pos.x,pos.y), ImVec2(pos.x + 20.f, pos.y - 100.f), Colortouse, 0.0f, ImDrawCornerFlags_All, 1.5f);
						break;
					}
				}
			}


			if (vars::aibones) {
				for (std::pair<int, int> bone_pair : sdk::bone_pairs) {
					auto bone1 = curAIAnim->CallMethodSafe<Unity::CTransform*>("GetBoneTransformInternal", bone_pair.first);
					auto bone2 = curAIAnim->CallMethodSafe<Unity::CTransform*>("GetBoneTransformInternal", bone_pair.second);

					if (!bone1 || !bone2)
						continue;

					auto bone1pos = bone1->GetPosition();
					auto bone2pos = bone2->GetPosition();

					Vector2 pos1;
					Vector2 pos2;

					if (Functions::worldtoscreen(bone1pos, pos1) && Functions::worldtoscreen(bone2pos, pos2)) {
						if (isarrested) {
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(255, 255, 0), 2.0);
						}
						else if (isaggresive) {
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(178, 34, 34), 2.0);
						}
						else if (isobjective) {
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(255, 0, 255), 2.0);
						}
						else 
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(255, 255, 255), 2.0);
					}
				}
			}


			if (vars::aimbot) {
				Unity::Vector3 bonepos;
				auto bonetransform = curAIAnim->CallMethodSafe<Unity::CTransform*>("GetBoneTransformInternal", 9);
				if (!bonetransform)
					continue;
				bonepos = bonetransform->GetPosition();


				Vector2 AimScreenPos;
				if (Functions::worldtoscreen(bonepos, AimScreenPos))
				{
					if (vars::fov_check)
					{
						if (AimScreenPos.x > (vars::screen_center.x + vars::aim_fov))
							continue;
						if (AimScreenPos.x < (vars::screen_center.x - vars::aim_fov))
							continue;
						if (AimScreenPos.y > (vars::screen_center.y + vars::aim_fov))
							continue;
						if (AimScreenPos.y < (vars::screen_center.y - vars::aim_fov))
							continue;
					}
					if (GetAsyncKeyState(VK_RBUTTON)) {
							sdk::mousemove(AimScreenPos.x, AimScreenPos.y, vars::screen_size.x, vars::screen_size.y, vars::smooth);
						
					}
				}
			}



		}
	}
	if (PlayerList.size() > 0)
	{

		for (int i = 0; i < PlayerList.size(); i++)
		{
			if (!PlayerList[i]) // Verify that the player is valid
				continue;
			vars::currentplayeridx = i;

			
			

			auto playerPosition = PlayerList[vars::currentplayeridx]->GetTransform()->GetPosition();
			auto curPlayer = PlayerList[vars::currentplayeridx]->GetComponent("UserInput");
			if (!curPlayer)
				continue;


			auto curLogger = curPlayer->GetMemberValue<Unity::CComponent*>("myLogger");

			if (!curLogger)
				continue;
			auto health = curPlayer->GetMemberValue<Unity::CComponent*>("myHealth");
			
			if (!health)
				continue;

			auto curPlayerGameObject = curPlayer->GetGameObject();

			if (!curPlayerGameObject)
				continue;

			auto curPlayerWeaponManag = curPlayerGameObject->GetComponent("WeaponManag");

			if (!curPlayerWeaponManag)
				continue;

			auto curPlayeranim = curPlayerWeaponManag->GetMemberValue<Unity::CComponent*>("anim");

			if (!curPlayeranim)
				continue;

			auto gamenetworks = GameManager->GetComponent("GameNetworks");
			
			if (!gamenetworks)
				continue;


			int* myTeamID = gamenetworks->GetMemberValue<int*>("MyTeamID");
			int* TeamID = curPlayer->GetMemberValue<Unity::CComponent*>("myLogger")->GetMemberValue<int*>("TeamID");
			bool* isalive = health->GetObscuredValue<bool*>("alive");


			if (TeamID == myTeamID)
				continue;

			if (!isalive)
				continue;
			




			if (vars::playeresp)
			{
				Unity::Vector3 root_pos = playerPosition;
				root_pos.y -= 0.2f;
				Vector2 pos;
				if (Functions::worldtoscreen(root_pos, pos)) {
					ImColor Colortouse = vars::PlayerSnaplineColor;
					if (vars::SnaplineRainbow)
						Colortouse = ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z);
					switch (vars::linetype)
					{
					case 1:
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(vars::screen_center.x, vars::screen_size.y), ImVec2(pos.x, pos.y), Colortouse, 1.5f);
						break;
					case 2:
						ImGui::GetBackgroundDrawList()->AddRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + 20.f, pos.y + 100.f), Colortouse, 0.0f, ImDrawCornerFlags_All, 1.5f);
						break;
					}
				}
			}

			if (vars::playerbones) {
				for (std::pair<int, int> bone_pair : sdk::bone_pairs) {
					auto bone1 = curPlayeranim->CallMethodSafe<Unity::CTransform*>("GetBoneTransformInternal", bone_pair.first);
					auto bone2 = curPlayeranim->CallMethodSafe<Unity::CTransform*>("GetBoneTransformInternal", bone_pair.second);

					if (!bone1 || !bone2)
						continue;

					auto bone1pos = bone1->GetPosition();
					auto bone2pos = bone2->GetPosition();


					Vector2 pos1;
					Vector2 pos2;

					if (Functions::worldtoscreen(bone1pos, pos1) && Functions::worldtoscreen(bone2pos, pos2)) {

							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(178, 34, 34), 2.0);
						
					}
				}
			}
			if (vars::aimbot) {
				Unity::Vector3 bonepos;
				auto bonetransform = curPlayeranim->CallMethodSafe<Unity::CTransform*>("GetBoneTransformInternal", 9);
				if (!bonetransform)
					continue;
				bonepos = bonetransform->GetPosition();

				Vector2 AimScreenPos;
				if (Functions::worldtoscreen(bonepos, AimScreenPos))
				{
					if (vars::fov_check)
					{
						if (AimScreenPos.x > (vars::screen_center.x + vars::aim_fov))
							continue;
						if (AimScreenPos.x < (vars::screen_center.x - vars::aim_fov))
							continue;
						if (AimScreenPos.y > (vars::screen_center.y + vars::aim_fov))
							continue;
						if (AimScreenPos.y < (vars::screen_center.y - vars::aim_fov))
							continue;
					}
					if (GetAsyncKeyState(VK_RBUTTON)) {

							sdk::mousemove(AimScreenPos.x, AimScreenPos.y, vars::screen_size.x, vars::screen_size.y, vars::smooth);


					}
				}
			}
			

		}
	}
	

	if (currentTime - lasttick > 5) //  5 ms Timer For Whatever you want to do
	{	
		
		lasttick = currentTime;
	}
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			ImGui::GetIO().Fonts->AddFontDefault();
			ImFontConfig font_cfg;
			font_cfg.GlyphExtraSpacing.x = 1.2;
			gameFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(TTSquaresCondensedBold, 14, 14, &font_cfg);
			ImGui::GetIO().Fonts->AddFontDefault();
			// Grab A shader Here If You want
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	pContext->RSGetViewports(&vars::vps, &vars::viewport);
	vars::screen_size = { vars::viewport.Width, vars::viewport.Height };
	vars::screen_center = { vars::viewport.Width / 2.0f, vars::viewport.Height / 2.0f };

	auto begin_scene = [&]() {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	};

	auto end_scene = [&]() {
		ImGui::Render();
	};

	begin_scene();

	auto isFrames = ImGui::GetFrameCount();
	static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;
	if (isFrames % 1 == 0)
	{
		if (isGreen == 0.01f && isBlue == 0.0f)
		{
			isRed += 0.01f;

		}
		if (isRed > 0.99f && isBlue == 0.0f)
		{
			isRed = 1.0f;

			isGreen += 0.01f;

		}
		if (isGreen > 0.99f && isBlue == 0.0f)
		{
			isGreen = 1.0f;

			isRed -= 0.01f;

		}
		if (isRed < 0.01f && isGreen == 1.0f)
		{
			isRed = 0.0f;

			isBlue += 0.01f;

		}
		if (isBlue > 0.99f && isRed == 0.0f)
		{
			isBlue = 1.0f;

			isGreen -= 0.01f;

		}
		if (isGreen < 0.01f && isBlue == 1.0f)
		{
			isGreen = 0.0f;

			isRed += 0.01f;

		}
		if (isRed > 0.99f && isGreen == 0.0f)
		{
			isRed = 1.0f;

			isBlue -= 0.01f;

		}
		if (isBlue < 0.01f && isGreen == 0.0f)
		{
			isBlue = 0.0f;

			isRed -= 0.01f;

			if (isRed < 0.01f)
				isGreen = 0.01f;

		}
	}
	vars::Rainbow = ImVec4(isRed, isGreen, isBlue, 1.0f);

	if (vars::watermark)
	{
		render::DrawOutlinedText(gameFont, ImVec2(vars::screen_center.x, vars::screen_size.y - 20), 13.0f, ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z), true, "[ TRYCLIENT ]");
		render::DrawOutlinedText(gameFont, ImVec2(vars::screen_center.x, 5), 13.0f, ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z), true, "[ %.1f FPS ]", ImGui::GetIO().Framerate);
	}

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(window, &mousePos);

	if (show_menu)
	{
		// X Mouse Cursor
		//render::DrawOutlinedTextForeground(gameFont, ImVec2(mousePos.x, mousePos.y), 13.0f, ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z), false, "X");
		DrawMenu();
	}
	// Render
	try
	{
		renderloop();
	}
	catch (...) {}

	end_scene();

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show_menu = !show_menu;
		ImGui::GetIO().MouseDrawCursor = show_menu;
	}

	if (GetKeyState(VK_END) & 1)
	{
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
		show_menu = false;
	}

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	IL2CPP::Thread::Detach(m_pThisThread);

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void initchair()
{
#ifdef DEBUG
	CreateConsole(); // if using melonloader console is already created
	system("cls");
#endif // DEBUG
	initvars();
	//find_sigs();
	IL2CPP::Callback::Initialize();
	EnableHooks();



	kiero::bind(8, (void**)&oPresent, hkPresent);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Functions::AI_Cache, NULL, NULL, NULL); 
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Functions::Player_Cache, NULL, NULL, NULL); 
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Functions::cleanshit, NULL, NULL, NULL); 
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			initchair();
			init_hook = true;
			vars::initil2cpp = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, LPVOID lpReserved)
{
	if (reason == 1)
	{
		DisableThreadLibraryCalls(mod);
		CreateThread(nullptr, 0, MainThread, mod, 0, nullptr);
	}
	return TRUE;
}