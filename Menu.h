#pragma once
#include "imgui/imgui.h"
#include "sdk.h"
#include "functions.h"
#include "Dumper.hpp"
#include "imgui/imgui.h"
#include "Lists.hpp"
#include <fstream>
using namespace ImGui;

void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("[?]");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ImGuiTheme1()
{
	IMGUI_CHECKVERSION();
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(10.0f, 10.0f);
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(50.0f, 50.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 1.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(5.0f, 3.0f);
	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(6.0f, 6.0f);
	style.ItemInnerSpacing = ImVec2(3.0f, 2.0f);
	style.IndentSpacing = 6.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 13.0f;
	style.ScrollbarRounding = 16.0f;
	style.GrabMinSize = 20.0f;
	style.GrabRounding = 4.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.8588235378265381f, 0.929411768913269f, 0.886274516582489f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5215686559677124f, 0.5490196347236633f, 0.5333333611488342f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1294117718935013f, 0.1372549086809158f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1490196138620377f, 0.1568627506494522f, 0.1882352977991104f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1372549086809158f, 0.1137254908680916f, 0.1333333402872086f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.168627455830574f, 0.1843137294054031f, 0.2313725501298904f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.2313725501298904f, 0.2000000029802322f, 0.2705882489681244f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.501960813999176f, 0.07450980693101883f, 0.2549019753932953f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.239215686917305f, 0.239215686917305f, 0.2196078449487686f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3882353007793427f, 0.3882353007793427f, 0.3725490272045135f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.6941176652908325f, 0.6941176652908325f, 0.686274528503418f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.6941176652908325f, 0.6941176652908325f, 0.686274528503418f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.658823549747467f, 0.1372549086809158f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.6509804129600525f, 0.1490196138620377f, 0.3450980484485626f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.7098039388656616f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.6509804129600525f, 0.1490196138620377f, 0.3450980484485626f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.6509804129600525f, 0.1490196138620377f, 0.3450980484485626f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.501960813999176f, 0.07450980693101883f, 0.2549019753932953f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.6509804129600525f, 0.1490196138620377f, 0.3450980484485626f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f, 0.5764706134796143f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.196078434586525f, 0.407843142747879f, 0.6784313917160034f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.8588235378265381f, 0.929411768913269f, 0.886274516582489f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.3098039329051971f, 0.7764706015586853f, 0.196078434586525f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.3843137323856354f, 0.6274510025978088f, 0.9176470637321472f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 1.0f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.300000011920929f);
}
void ImGuiTheme2()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	ImGuiStyle& style = ImGui::GetStyle();
	//style.WindowPadding = ImVec2(8.00f, 8.00f);
	//style.FramePadding = ImVec2(5.00f, 2.00f);
	//style.CellPadding = ImVec2(6.00f, 6.00f);
	//style.ItemSpacing = ImVec2(6.00f, 6.00f);
	//style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	//style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	//style.FrameBorderSize = 1;
	style.WindowRounding = 4;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
}

void DrawInspector() {
	ImGui::SetNextWindowSize(ImVec2(600.000f, 1000.000f), ImGuiCond_Once);
	if (!ImGui::Begin("Inspector", nullptr, 2)) {
		ImGui::End();
		return;
	}

	static std::vector<std::string> components;
	static std::vector<std::string> classes;
	static std::vector<std::string> methods;
	static std::vector<std::string> fields;
	static std::string current_comp = "";

	ImGui::Text("Components");
	if (ImGui::Button("Update##comp")) {
		components = Dumper::DumpComponentsString();
	}
	ImGui::SetNextItemWidth(150.000f);
	static int component_current_idx = 0; // Here we store our selection data as an index.
	static ImGuiTextFilter c_filter;
	c_filter.Draw("Search##compfilter");
	if (ImGui::BeginListBox("##Components", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < components.size(); n++)
		{
			if (!c_filter.PassFilter(components[n].c_str())) {
				continue;
			}
			const bool comp_is_selected = (component_current_idx == (int)n);
			if (ImGui::Selectable(components[n].c_str(), comp_is_selected))
				component_current_idx = (int)n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (comp_is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}
	ImGui::Spacing();
	ImGui::Text("Classes");
	if (ImGui::Button("Update##class")) {
		classes = Dumper::DumpClassesString(components[component_current_idx]);
		current_comp = components[component_current_idx];
	}

	ImGui::SetNextItemWidth(150.000f);
	static int class_current_idx = 0; // Here we store our selection data as an index.
	static ImGuiTextFilter cl_filter;
	cl_filter.Draw("Search##classfilter");
	if (ImGui::BeginListBox("##Class", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < classes.size(); n++)
		{
			if (!cl_filter.PassFilter(classes[n].c_str())) {
				continue;
			}
			const bool class_is_selected = (class_current_idx == (int)n);
			if (ImGui::Selectable(classes[n].c_str(), class_is_selected)) {
				class_current_idx = (int)n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (class_is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	ImGui::Spacing();
	ImGui::Text("Methods");
	if (ImGui::Button("Update##Methods")) {
		methods = Dumper::DumpMethodsString(current_comp, classes[class_current_idx]);
	}

	ImGui::SetNextItemWidth(150.000f);
	static int method_current_idx = 0; // Here we store our selection data as an index.
	static ImGuiTextFilter me_filter;
	me_filter.Draw("Search##methodfilter");
	if (ImGui::BeginListBox("##Methods", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < methods.size(); n++)
		{
			if (!me_filter.PassFilter(methods[n].c_str())) {
				continue;
			}
			const bool meth_is_selected = (method_current_idx == (int)n);
			if (ImGui::Selectable(methods[n].c_str(), meth_is_selected))
				method_current_idx = (int)n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (meth_is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	ImGui::Spacing();
	ImGui::Text("Fields");
	if (ImGui::Button("Update##Fields")) {
		fields = Dumper::DumpFieldsString(current_comp, classes[class_current_idx]);
	}

	ImGui::SetNextItemWidth(150.000f);
	static int field_current_idx = 0; // Here we store our selection data as an index.
	static ImGuiTextFilter fe_filter;
	fe_filter.Draw("Search##fieldsfilter");
	if (ImGui::BeginListBox("##Fields", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < fields.size(); n++)
		{
			if (!fe_filter.PassFilter(fields[n].c_str())) {
				continue;
			}
			const bool field_is_selected = (field_current_idx == (int)n);
			if (ImGui::Selectable(fields[n].c_str(), field_is_selected))
				field_current_idx = (int)n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (field_is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	ImGui::End();
}

void DrawMenu()
{
	
	ImGuiTheme1();
	DrawInspector();
	static int page = 0;
	if (ImGui::Begin("[ TRYS ZH HACKS ]", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::SetWindowPos(ImVec2(500, 500), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(375, 400), ImGuiCond_Once);
		static int tabb = 0;
		ImGui::SameLine();
		if (ImGui::Button("Visual"))
		{
			tabb = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Weapon"))
		{
			tabb = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("Exploits"))
		{
			tabb = 2;
		}
		ImGui::Separator();
		switch (tabb) {
		case 0:
			ImGui::Checkbox("AI ESP", &vars::aiesp);
			ImGui::SameLine();
			ImGui::ColorEdit3("##PlayerSnaplineColor", (float*)&vars::PlayerSnaplineColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Checkbox("##RGB3", &vars::SnaplineRainbow);
			ImGui::Checkbox("AIBones", &vars::aibones);
			ImGui::Checkbox("PlayerBones", &vars::playerbones);
			ImGui::Checkbox("Player ESP", &vars::playeresp); 
			ImGui::Checkbox("Inf Stamina", &vars::infstamina);


			ImGui::Checkbox("Crosshair", &vars::crosshair);
			ImGui::SameLine();
			ImGui::ColorEdit3("##CrosshairColor", (float*)&vars::CrossColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Checkbox("##RGB6", &vars::crosshairRainbow);
			

			ImGui::Checkbox("Crouch Speed", &vars::crouchspeed);
			if (vars::crouchspeed) {
				ImGui::SliderFloat("##CrouchSpeed", &vars::crouchspeedfloat, 0, 7, "Speed: %.0f");

			}


			ImGui::Checkbox("Fov Changer", &vars::fov_changer);
			if (vars::fov_changer)
			{
				ImGui::SliderFloat("##CamFOV", &vars::CameraFOV, 20, 180, "Camera FOV: %.0f");
				// ImGui::SliderFloat("##ViewFOV", &vars::ViewmodelFOV, 20, 180, "Viewmodel FOV: %.0f");
			}
			//ImGui::Checkbox("Watermark", &vars::watermark);
			ImGui::SliderInt("Line Style", &vars::linetype, 1, 2);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("1 = Bottom Screen Line\n2 = BOX");
			break;
		case 1:

			ImGui::Checkbox("GunMod", &vars::gunmod);// notworking
			ImGui::Checkbox("More DMG", &vars::instakill);


			ImGui::Checkbox("Aim", &vars::aimbot);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Aimbot lol");

			/*
			ImGui::Checkbox("Silent Aim", &vars::silent_aim);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Aimbot without moving camera");
				*/

			ImGui::Checkbox("Aim FOV", &vars::fov_check);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Aim FOV Check");
			if (vars::fov_check)
			{
				ImGui::SliderFloat("Aimbot FOV", &vars::aim_fov, 0, 1000.0f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Circle FOV");
			}
			ImGui::SliderFloat("Aimbot Smoothing", &vars::smooth, 0.2f, 10.0f);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Humanized Aim");

			
			ImGui::Combo("Aim Bone", &vars::boneselected, vars::bones, IM_ARRAYSIZE(vars::bones));
			break;
		case 2:
			ImGui::Checkbox("ADD BDT", &vars::addbdtbooltoggle);
			if (vars::addbdtbooltoggle) {
				ImGui::SliderInt("##BDT", &vars::bdtint, 0, 10, "Speed: %.0f");

			}
			if (ImGui::Button("Kill Lights")) {
				auto GameNetworks = GameManager->GetComponent("GameSettings");

				if (!GameNetworks)
					return;

				auto breakerboxlogger = GameNetworks->GetMemberValue<Unity::CComponent*>("BreakerBoxLogger");

				auto photon = breakerboxlogger->GetMemberValue<Unity::CComponent*>("myPhoton");

				photon->CallMethodSafe<void*>("RPC", "DisableConnectedLights", 0, new Unity::CGameObject);
			}
			break;
		}
		ImGui::End();
	}
}

