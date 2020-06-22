#pragma once
#include <cassert>
namespace CommonUtilities
{
	template <class T>
	T Lerp(const T& a, const T& b, float t)
	{
		return (a * (1.0f - t)) + (b * t);
	}

	// Calculates the linear parameter t that produces the interpolant [aValue] within the range[aFrom, aTo].
	float InverseLerp(const float aFrom, const float aTo, const float aValue)
	{
		return (aValue - aFrom) / (aTo - aFrom);
	}

	template <class T>
	T Min(const T& aValue0, const T& aValue1)
	{
		return aValue0 < aValue1 ? aValue0 : aValue1;
	}
	template <class T>
	T Max(const T& aValue0, const T& aValue1)
	{
		return aValue0 < aValue1 ? aValue1 : aValue0;
	}
	template <class T>
	T Clamp(const T& aValue, const T& aMin, const T& aMax)
	{
#ifdef _DEBUG
		assert(aMin <= aMax && "Min value must be equal or less than Max value.");
#endif
		return
			aValue < aMin ? aMin :
			aValue > aMax ? aMax : aValue;
	}

	// Combines two values into one unique. Warning: for optimization reasons this returns a integer and will overflow if pairing too high numbers.
	// If the function should not make a distinction between (a, b) and (b, a) then sort a and b first.
	int SzudzikPairingFunction(int aValue0, int aValue1)
	{
		// http://szudzik.com/ElegantPairing.pdf
		// This is a more space efficent version of Cantors pairing function and also accounts for negative numbers
		int a = aValue0 >= 0 ? 2 * aValue0 : -2 * aValue0 - 1;
		int b = aValue1 >= 0 ? 2 * aValue1 : -2 * aValue1 - 1;
		int value = a >= b ? a * a + a + b : a + b * b;
		assert(value >= 0 && "Pairing value was negative. Most likely due to overflow from big numbers. Consider using long instead of int.");
		return value;
	}

	// Converts a value from a range to another. E.g Value 5 in range 0-10 converted to range 100-200 will become 150.
	template <class T>
	T Remap(T aValue, T aOldMin, T aOldMax, T aNewMin, T aNewMax)
	{
		return (((aValue - aOldMin) * (aNewMax - aNewMin)) / (aOldMax - aOldMin)) + aNewMin;
	}
}
