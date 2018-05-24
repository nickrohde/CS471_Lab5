#pragma once

#ifndef _UTILITY_H
#define _UTILITY_H

#pragma region Includes:
	#include "MasterInclude.hpp"

#pragma endregion


#pragma region Defines:
	/// <summary>Assert that always fails to mark unfinished code.</summary>
	#ifndef TODO
	#define TODO assert(false)
	#endif

	/// <summary>Success return values.</summary>
	#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
	#endif // !EXIT_SUCCESS

	/// <summary>Failure return values.</summary>
	#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
	#endif // !EXIT_FAILURE

	/// <summary>Null</summary>
	#ifndef NULL
	#define NULL 0x0
	#endif

#pragma endregion


#pragma region Typedefs:
	/// <summary>Typedefs for convenience.</summary>
	typedef unsigned char uchar;
	typedef unsigned int uint;
	typedef unsigned long long ulong;

	typedef std::chrono::high_resolution_clock::time_point	timePoint;
	typedef std::chrono::duration<double>					duration;
	typedef std::chrono::high_resolution_clock				highRes_Clock;

#pragma endregion


#pragma region Templates:
template <std::size_t> inline ulong __getDoubleMax(void) noexcept;
template <> inline ulong __getDoubleMax<2>(void) noexcept { return 0x7BFF; }             // 16 bit just for completeness
template <> inline ulong __getDoubleMax<4>(void) noexcept { return 0x7F7FFFFF; }		 // 32 bit
template <> inline ulong __getDoubleMax<8>(void) noexcept { return 0x7FEFFFFFFFFFFFFF; } // 64 bit


///<summary>Sets the double to the maximum value for the system.</summary>
///<remarks>Numeric limits wasn't coorporating so I wrote my own double max function.</remarks>
inline double getDoubleMax(void) noexcept
{
	static double a;
	static ulong* b = reinterpret_cast<ulong*>(&a);
	*b = (*b & 0x0) | __getDoubleMax<sizeof(double)>();
	return a;
} // end method getDoubleMax


/// <summary>Finds the maximum of two values.</summary>
/// <typeparam name="T">Some <see cref="std::NumericType"/> or a class with comparison operators overloaded.</typeparam>
/// <param name="a">First value.</param>
/// <param name="b">Second value.</param>
/// <returns>The maximum of a and b.</returns>
template <typename T>
inline T* Max(T* a, T* b) noexcept
{
	return (*a > *b) ? (a) : (b);
} // end template Max

#pragma endregion

#endif

