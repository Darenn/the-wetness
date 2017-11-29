/// \file       ArrayUtility.hpp
/// \date       28/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include <intrin.h>

/// \brief	Makes the sum of an array of type T
/// \param  array The array as a pointer
/// \param  len The lenght of the array
template <typename T>
inline T util::ArraySum(T const * const __restrict array, size_t const len)
{
	T sum = 0;
	for(size_t n = 0; n < len; ++n)
	{
		sum += array[n];
	}

	return sum;
}

/// \brief	Makes the power of each item by the given number
///			and stores them into the out array
/// \param  array The array as a pointer
/// \param  out The result array
/// \param  len The lenght of the array
/// \param  power The power to apply on each item
template <typename T>
inline void util::ArrayPow(
	T const * const __restrict array,
	T       * const __restrict out, size_t const len, int power)
{
	for (int n = 0; n < len; ++n) 
	{
		out[n] = pow(array[n], power);
	}
}

/// \brief	Mutliplies two arrays item by item
///			and stores the result in the result array
/// \param  rhs The right array
/// \param  lhs The left  array
/// \param  out The result array
/// \param  len The lenght of the arrays
template <typename T>
inline void util::ArrayMul(
	T const * const __restrict rhs,
	T const * const __restrict lhs,
	T       * const __restrict out, size_t len)
{
	for (size_t n = 0; n < len; ++n) 
	{
		out[n] = rhs[n] * lhs[n];
	}
}

/// \brief	TODO
template <>
inline void util::ArrayMul(
	double const * const __restrict rhs,
	double const * const __restrict lhs,
	double       * const __restrict out, size_t len)
{
	for (size_t n = 0; n < len; n += 4)
	{
		__m128d vectorRHSA = _mm_load_pd(&rhs[n + 0]);
		__m128d vectorLHSA = _mm_load_pd(&lhs[n + 0]);
		__m128d vectorRHSB = _mm_load_pd(&rhs[n + 2]);
		__m128d vectorLHSB = _mm_load_pd(&lhs[n + 2]);

		_mm_store_pd(&out[n + 0], _mm_mul_pd(vectorRHSA, vectorLHSA));
		_mm_store_pd(&out[n + 2], _mm_mul_pd(vectorRHSB, vectorLHSB));
	}

	__asm
	{
		mov		rax, rhs	; Buffers the rhs pointer
		mov		rcx, lhs	; Buffers the lhs pointer
	}

	for (size_t n = 0; n < len; n += 4)
	{
		__asm
		{
			movapd 
		}
	}

	
}