/// \file       Vector3.hpp
/// \date       07/10/2017
/// \package    Maths
/// \author     Vincent STEHLY--CALISTO

#ifndef _VECTOR_3_HPP
#define _VECTOR_3_HPP

/// \class  Vector3
/// \brief  Stores 3 value of type T
template <typename T>
class Vector3
{
public:

	T x; ///< The x coordinate
	T y; ///< The y coordinate
	T z; ///< The z coordinate

		 /// \see	Vector.inl for implementation
	inline Vector3(void);
	inline Vector3(T X, T Y, T Z);
	inline Vector3(const Vector3<T> & other);

	template <typename U> explicit inline Vector3(const Vector3<U> & other);
};

/// \see	Vector.inl for implementation
template <typename T> Vector3<T>  operator -  (const Vector3<T>& right);
template <typename T> Vector3<T>& operator += (Vector3<T>& left, const Vector3<T>& right);
template <typename T> Vector3<T>& operator -= (Vector3<T>& left, const Vector3<T>& right);
template <typename T> Vector3<T>  operator +  (const Vector3<T>& left, const Vector3<T>& right);
template <typename T> Vector3<T>  operator -  (const Vector3<T>& left, const Vector3<T>& right);
template <typename T> Vector3<T>  operator *  (const Vector3<T>& left, T right);
template <typename T> Vector3<T>  operator *  (T left, const Vector3<T>& right);
template <typename T> Vector3<T>& operator *= (Vector3<T>& left, T right);
template <typename T> Vector3<T>  operator /  (const Vector3<T>& left, T right);
template <typename T> Vector3<T>& operator /= (Vector3<T>& left, T right);
template <typename T> bool        operator == (const Vector3<T>& left, const Vector3<T>& right);
template <typename T> bool        operator != (const Vector3<T>& left, const Vector3<T>& right);

#include "Impl/Vector3.inl"

typedef Vector3<int>          Vector3i; ///< Handy typedef for int   vector
typedef Vector3<float>		  Vector3f; ///< Handy typedef for float vector
typedef Vector3<unsigned int> Vector3u; ///< Handy typedef for uint  vector

#endif // _VECTOR_3_HPP
