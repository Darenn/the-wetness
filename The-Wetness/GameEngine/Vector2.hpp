/// \file       Vector2.hpp
/// \date       07/10/2017
/// \package    Maths
/// \author     Vincent STEHLY--CALISTO

#ifndef _VECTOR_2_HPP
#define _VECTOR_2_HPP

/// \class  Vector2
/// \brief  Stores 2 value of type T
template <typename T>
class Vector2
{
public:
	
	T x; ///< The x coordinate
	T y; ///< The y coordinate

	/// \see	Vector.inl for implementation
	inline Vector2 (void);
	inline Vector2 (T X, T Y);
	inline Vector2 (const Vector2<T> & other);

	template <typename U> explicit inline Vector2 (const Vector2<U> & other);
};

/// \see	Vector.inl for implementation
template <typename T> Vector2<T>  operator -  (const Vector2<T>& right);
template <typename T> Vector2<T>& operator += (Vector2<T>& left, const Vector2<T>& right);
template <typename T> Vector2<T>& operator -= (Vector2<T>& left, const Vector2<T>& right);
template <typename T> Vector2<T>  operator +  (const Vector2<T>& left, const Vector2<T>& right);
template <typename T> Vector2<T>  operator -  (const Vector2<T>& left, const Vector2<T>& right);
template <typename T> Vector2<T>  operator *  (const Vector2<T>& left, T right);
template <typename T> Vector2<T>  operator *  (T left, const Vector2<T>& right);
template <typename T> Vector2<T>& operator *= (Vector2<T>& left, T right);
template <typename T> Vector2<T>  operator /  (const Vector2<T>& left, T right);
template <typename T> Vector2<T>& operator /= (Vector2<T>& left, T right);
template <typename T> bool        operator == (const Vector2<T>& left, const Vector2<T>& right);
template <typename T> bool        operator != (const Vector2<T>& left, const Vector2<T>& right);

#include "Vector2.inl"

typedef Vector2<int>          Vector2i; ///< Handy typedef for int   vector
typedef Vector2<float>		  Vector2f; ///< Handy typedef for float vector
typedef Vector2<unsigned int> Vector2u; ///< Handy typedef for uint  vector

#endif // _VECTOR_2_HPP
