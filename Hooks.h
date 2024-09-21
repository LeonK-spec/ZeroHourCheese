#pragma once
#include "il2cpp.h"
#include "sdk.h"
#include "Lists.hpp"
namespace hooks
{
	void(__fastcall* userinputupdate_og) (UserInput_o* __this);
	void __stdcall userinputupdate(UserInput_o* __this) {
		float num = vars::crouchspeedfloat;
		__this->fields.CrouchWalkSpeed = num;

		
		//if (vars::infstamina) {
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.ex_Weight = 0.0f;
		//}
		//if (vars::nospread) {
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.MaxSpray = 1.f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.DoFireShake = false;
		//}
		//if (vars::norecoil) {
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.recoilAmount = 0.1f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.recoilRecoverTime = 0.1f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.upwardKick = 0.01f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.upwardKickSpeed = 0.0f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.HorizontalKick = 0.0f;

		//}
		//if (vars::moredmg) {
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.ex_Dmg = 70.f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.BulletsPerShot = 4;
		//	
		//}
		//else {
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.ex_Dmg = 30.f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.BulletsPerShot = 1;
		//}
		//if (vars::firerate) {

		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.fireRate = 0.01f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.Automatic = true;
		//}
		//else {
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.fireRate = 0.1f;
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.Automatic = true;
		//}
		//if (vars::infiniteammo) {
		//	__this->fields.myWeaponManager->fields.CurrentWeapon->fields.Properties->fields.Totalammo = 40;
		//}

		return userinputupdate_og(__this);
	}


	float(__fastcall* set_fov_o)(DWORD*, UnityEngine_UI_Slider_o*, DWORD*);
	float __stdcall set_fov_Hook(DWORD* __this, UnityEngine_UI_Slider_o* options, DWORD* methodinfo) {
		int num = vars::CameraFOV;

		options->fields.m_Value = num;
		options->fields.m_WholeNumbers = true;
		options->fields.m_MinValue = static_cast<float>(0);;
		options->fields.m_MaxValue = static_cast<float>(130);

		return set_fov_o(__this, options, methodinfo);

	}


	void(__fastcall* gamenetworksupdate_og) (GameNetworks_o* __this);
	void __stdcall gamenetworksupdate(GameNetworks_o* __this) {
		if (vars::addbdtbooltoggle) {
			__this->fields.BDTStat->fields.value += vars::bdtint;
		}
		if (vars::usernamespoofer) {
			/*auto gnu = (Unity::CComponent*)__this;
				gnu->SetObscuredValue<const char[15]>("s_UserName", vars::username);*/
		}
		return gamenetworksupdate_og(__this);
	}


}