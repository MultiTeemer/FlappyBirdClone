#pragma once

namespace FlappyBirdClone
{
	namespace Converter
	{
		constexpr double PIXELS_PER_METERS = 32.0;
		constexpr double PI = 3.14159265358979323846;
		
		template<typename T>
		constexpr T PixelsToMeters(const T& x) {
			return x / PIXELS_PER_METERS;
		};
		
		template<typename T>
		constexpr T MetersToPixels(const T& x) {
			return x * PIXELS_PER_METERS;
		};
		
		template<typename T>
		constexpr T DegToRad(const T& x) { return PI * x / 180.0; };
		
		template<typename T>
		constexpr T RadToDeg(const T& x) { return 180.0 * x / PI; }
	}
}
