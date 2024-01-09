#include "radar_visuals.hpp"
#include "radar.hpp"
#include "../ImGui/imgui.h"

#include "../Visuals/visuals.hpp"

namespace gamehacking::radar::visuals
{
	double zoom = 4;
	double zoom_ = 0.004;


	void Draw(void)
	{

		static ImVec2 window_size = { 300,300 };
		static float window_size_ = window_size.x;
		static ImVec2 window_location = { 100,100 };

		ImGui::SetNextWindowPos(window_location, ImGuiCond_FirstUseEver);
		//ImGui::SetNextWindowPos({ 0, 0 });
		ImGui::SetNextWindowSize(window_size);
		if (gamehacking::visuals::show_imgui_menu)
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImColor(0.0f, 0.0f, 0.0f, 0.0f).Value);
			ImGui::Begin("radar", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse /*| ImGuiWindowFlags_NoBringToFrontOnFocus*/);
			ImGui::PopStyleColor();
		}
		else
		{
			ImGui::Begin("radar", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse /*| ImGuiWindowFlags_NoBringToFrontOnFocus */);
		}

		window_size_ = std::max(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
		window_size = { window_size_, window_size_ };

		window_location = ImGui::GetWindowPos();

		ImVec2 center(window_location.x + window_size.x / 2, window_location.y + window_size.y / 2);

		auto imgui_draw_list = ImGui::GetWindowDrawList();

		float border = 4;
		float axes_thickness = 2;

		imgui_draw_list->AddCircleFilled(center, window_size.x / 2 - border, ImColor(25, 25, 25, 200), 0);
		imgui_draw_list->AddCircle(center, window_size.x / 2 - border, ImColor(25, 25, 25, 200), 0, axes_thickness);

		imgui_draw_list->AddLine({ window_location.x + border, window_location.y + window_size.y / 2 }, { window_location.x + window_size.x - border, window_location.y + window_size.y / 2 }, ImColor(65, 65, 65, 255), axes_thickness);
		imgui_draw_list->AddLine({ window_location.x + window_size.x / 2, window_location.y + border }, { window_location.x + window_size.x / 2, window_location.y + window_size.y - border }, ImColor(65, 65, 65, 255), axes_thickness);
		imgui_draw_list->AddCircleFilled(center, axes_thickness + 1, ImColor(65, 65, 65, 125));

		const auto& radar_information_data = gamehacking::radar::radar_information_data;

		for (const auto& radar_information : radar_information_data)
		{
			if (radar_information.r * zoom_ * zoom > window_size_ / 2 - border)
			{
				continue;
			}

			auto theta = radar_information.theta;
			auto y = radar_information.r * cos(theta) * zoom_ * zoom;
			auto x = radar_information.r * sin(theta) * zoom_ * zoom;

			if (!radar_information.right)
				x = -abs(x);

			imgui_draw_list->AddCircleFilled({ static_cast<float>(center.x + x), static_cast<float>(center.y - y) }, 2, ImColor(0, 255, 255));
		}

		ImGui::End();
	}
}