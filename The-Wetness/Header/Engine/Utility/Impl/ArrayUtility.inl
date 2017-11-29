/// \file       ArrayUtility.hpp
/// \date       28/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include <intrin.h>

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

template <typename T>
 void util::ArrayMul(
	T const * const __restrict rhs,
	T const * const __restrict lhs,
	T       * const __restrict out, size_t len)
{
	for (size_t n = 0; n < len; ++n) 
	{
		out[n] = rhs[n] * lhs[n];
	}
}
 
template <> 
inline void util::ArrayMul(
	double const * const __restrict rhs,
	double const * const __restrict lhs,
	double       * const __restrict out, size_t const len)
{
	size_t const index = len - len % 2;

	for (size_t n = 0; n < index; n += 2)
	{
		_mm_store_pd(&out[n],
			_mm_mul_pd(
				_mm_load_pd(&rhs[n]), 
				_mm_load_pd(&lhs[n])));
	}

	for (size_t n = index; n < len; ++n)
	{
		out[n] = rhs[n] + lhs[n];
	}
}

template <typename T>
inline void util::ArrayDiff(
	T const * const __restrict rhs,
	T const * const __restrict lhs,
	T       * const __restrict out, size_t const len)
{
	for (size_t n = 0; n < len; ++n)
	{
		out[n] = rhs[n] - lhs[n];
	}
}

template <>
inline void util::ArrayDiff(
	double const * const __restrict rhs,
	double const * const __restrict lhs,
	double       * const __restrict out, size_t const len)
{
	size_t const index = len - len % 2;

	for (size_t n = 0; n < index; n += 2)
	{
		_mm_store_pd(&out[n],
			_mm_sub_pd(
				_mm_load_pd(&rhs[n]),
				_mm_load_pd(&lhs[n])));
	}

	for (size_t n = index; n < len; ++n)
	{
		out[n] = rhs[n] - lhs[n];
	}
}