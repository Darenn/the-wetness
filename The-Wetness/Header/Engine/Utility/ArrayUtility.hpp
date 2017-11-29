/// \file       ArrayUtility.hpp
/// \date       28/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _ARRAY_UTILITY_HPP
#define _ARRAY_UTILITY_HPP

/// \namespace util
namespace util
{
	/* inline */
	template <typename T>
	T ArraySum(T const * const __restrict array, size_t const len);

	/* inline */
	template <typename T>
	void ArrayPow(T const * const __restrict array, 
			      T       * const __restrict out, size_t const len, int power);

	/* inline */
	template <typename T>
	void ArrayMul(T const * const __restrict rhs, 
				  T const * const __restrict lhs,
				  T       * const __restrict out, size_t len);

	/* inline */
	template <typename T>
	T * ArrayDiff(T const * const __restrict rhs,
				  T const * const __restrict lhs, size_t len);
				
}

#include "Impl/ArrayUtility.inl"

#endif // _ARRAY_UTILITY_HPP
