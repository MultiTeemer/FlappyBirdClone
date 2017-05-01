#pragma once

#include <map>

namespace FlappyBirdClone
{
	class RangeMapper
	{
	public:
		float operator()(float value) const;
		float& operator[](float value);

	private:
		std::map<float, float> mapping;
	};
}
