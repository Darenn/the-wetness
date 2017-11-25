/// \file       Vector3.inl
/// \date       07/10/2017
/// \package    Maths
/// \author     Vincent STEHLY--CALISTO

/// \brief	Default constructor
template <typename T>
Vector3<T>::Vector3()
: x(0)
, y(0)
, z(0)
{
	// None
}

/// \brief	Constructs the vector from three parameters
/// \param  X The x coordinate
/// \param  Y The y coordinate
/// \param  Z The z coordinate
template <typename T>
Vector3<T>::Vector3(T X, T Y, T Z)
: x(X)
, y(Y)
, z(Z)
{
	// None
}

/// \brief	Copy constructor
/// \param  other The vector to copy
template <typename T>
Vector3<T>::Vector3(const Vector3<T>& other)
: x(other.x)
, y(other.y)
, z(other.z)
{
	// None
}

/// \brief	Constructs the vector from a different one
/// \param  other The other vector
template <typename T>
template <typename U>
Vector3<T>::Vector3(const Vector3<U>& other)
: x(static_cast<T>(other.x))
, y(static_cast<T>(other.y))
, z(static_cast<T>(other.z))
{
	// None
}

/// \brief	Unary - operator
template <typename T>
inline Vector3<T> operator -(const Vector3<T>& right)
{
	return Vector3<T>(-right.x, -right.y, -right.z);
}

/// \brief Binary operator +=
template <typename T>
inline Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;

	return left;
}

/// \brief	Binary operator -=
template <typename T>
inline Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;

	return left;
}

/// \brief	Binary operator +
template <typename T>
inline Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right)
{
	return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

/// \brief	Binary operator -
template <typename T>
inline Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right)
{
	return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

/// \brief	Binary operator *
template <typename T>
inline Vector3<T> operator *(const Vector3<T>& left, T right)
{
	return Vector3<T>(left.x * right, left.y * right, left.z * right.z);
}

/// \brief	Binary operator *
template <typename T>
inline Vector3<T> operator *(T left, const Vector3<T>& right)
{
	return Vector3<T>(right.x * left, right.y * left, right.z * left.z);
}

/// \brief	Binary operator *=
template <typename T>
inline Vector3<T>& operator *=(Vector3<T>& left, T right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;

	return left;
}

/// \brief	Binary operator /
template <typename T>
inline Vector3<T> operator /(const Vector3<T>& left, T right)
{
	return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

/// \brief	Binary operator /=
template <typename T>
inline Vector3<T>& operator /=(Vector3<T>& left, T right)
{
	left.x /= right;
	left.y /= right;
	left.z /= right;

	return left;
}

/// \brief	Binary operator ==
template <typename T>
inline bool operator ==(const Vector3<T>& left, const Vector3<T>& right)
{
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

/// \brief	Binary operator !=
template <typename T>
inline bool operator !=(const Vector3<T>& left, const Vector3<T>& right)
{
	return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}