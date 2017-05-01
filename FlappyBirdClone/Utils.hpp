#pragma once

#include <cstdlib>

namespace FlappyBirdClone
{
	namespace Utils
	{
		template <typename Type>
		Type GetRandom(Type max)
		{
			return static_cast<Type>(max * rand() / (float)RAND_MAX);
		}

		template <typename Type>
		Type GetRandom(Type min, Type max)
		{
			return static_cast<Type>(GetRandom(max - min) + min);
		}

		template <typename Type>
		Type Clamp(Type val, Type min, Type max)
		{
			return std::min(max, std::max(val, min));
		}
	}
}
