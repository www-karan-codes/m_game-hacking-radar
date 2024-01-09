#include "radar.hpp"

#include "../BaseStructures/base_structures.hpp"

namespace gamehacking::radar
{
	std::list<RadarInformation> radar_information_data;
	void Tick(void)
	{
		radar_information_data.clear();
		for (const auto& player : gamehacking::base_structures::players)
		{
			RadarInformation radar_information;
			radar_information.right = gamehacking::base_structures::my_player.forward_.Orientation(player.location_ - gamehacking::base_structures::my_player.location_) == gamehacking::math::Vector3D::Side::kRight ? true : false;
			radar_information.r = (player.location_ - gamehacking::base_structures::my_player.location_).Magnitude();
			radar_information.theta = gamehacking::base_structures::my_player.forward_.AngleBetweenXY(player.location_ - gamehacking::base_structures::my_player.location_);
			radar_information_data.push_back(radar_information);
		}
	}
}