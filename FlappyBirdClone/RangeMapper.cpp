#include "RangeMapper.hpp"

namespace FlappyBirdClone
{
	float RangeMapper::operator()(float value) const
	{
		for (auto i = mapping.cbegin(); i != mapping.cend(); ++i) {
			if (i->first > value) {
				return i->second;
			}
		}

		return 0;
	}

	float& RangeMapper::operator[](float value)
	{
		return mapping[value];
	}
}
