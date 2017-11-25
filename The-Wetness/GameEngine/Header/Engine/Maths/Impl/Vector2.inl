/// \file       Vector2.inl
/// \date       07/10/2017
/// \package    Maths
/// \author     Vincent STEHLY--CALISTO

/// \brief	Default constructor
template <typename T> 
Vector2<T>::Vector2() 
: x(0)
, y(0)
{
	// None
}

/// \brief	Constructs the vector from two parameters
/// \param  X The x coordinate
/// \param  Y The y coordinate
template <typename T>
Vector2<T>::Vector2(T X, T Y) 
: x(X)
, y(Y)
{
	// None
}

/// \brief	Copy constructor
/// \param  other The vector to copy
template <typename T>
Vector2<T>::Vector2(const Vector2<T>& other) 
: x(other.x)
, y(other.y)
{
	// None
}

/// \brief	Constructs the vector from a different one
/// \param  other The other vector
template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U>& other)
: x(static_cast<T>(other.x))
, y(static_cast<T>(other.y))
{
	// None
}

/// \brief	Unary - operator
template <typename T>
inline Vector2<T> operator -(const Vector2<T>& right)
{
	return Vector2<T>(-right.x, -right.y);
}

/// \brief Binary operator +=
template <typename T>
inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
{
	left.x += right.x;
	left.y += right.y;

	return left;
}

/// \brief	Binary operator -=
template <typename T>
inline Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;

	return left;
}

/// \brief	Binary operator +
template <typename T>
inline Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

/// \brief	Binary operator -
template <typename T>
inline Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x - right.x, left.y - right.y);
}

/// \brief	Binary operator *
template <typename T>
inline Vector2<T> operator *(const Vector2<T>& left, T right)
{
	return Vector2<T>(left.x * right, left.y * right);
}

/// \brief	Binary operator *
template <typename T>
inline Vector2<T> operator *(T left, const Vector2<T>& right)
{
	return Vector2<T>(right.x * left, right.y * left);
}

/// \brief	Binary operator *=
template <typename T>
inline Vector2<T>& operator *=(Vector2<T>& left, T right)
{
	left.x *= right;
	left.y *= right;

	return left;
}

/// \brief	Binary operator /
template <typename T>
inline Vector2<T> operator /(const Vector2<T>& left, T right)
{
	return Vector2<T>(left.x / right, left.y / right);
}

/// \brief	Binary operator /=
template <typename T>
inline Vector2<T>& operator /=(Vector2<T>& left, T right)
{
	left.x /= right;
	left.y /= right;

	return left;
}

/// \brief	Binary operator ==
template <typename T>
inline bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
{
	return (left.x == right.x) && (left.y == right.y);
}

/// \brief	Binary operator !=
template <typename T>
inline bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
{
	return (left.x != right.x) || (left.y != right.y);
}