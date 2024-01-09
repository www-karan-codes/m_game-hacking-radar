#pragma once

#include <list>

namespace gamehacking::radar
{
	struct RadarInformation
	{
		double r = 0;
		double theta = 0;
		bool right = 0;
	};

	extern std::list<RadarInformation> radar_information_data;

	void Tick(void);
}