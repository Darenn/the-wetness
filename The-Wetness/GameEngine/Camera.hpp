/// \file       Camera.hpp
/// \date       07/10/2017
/// \package    Raycaster
/// \author     Vincent STEHLY--CALISTO

#ifndef _RAYCASTER_HPP
#define _RAYCASTER_HPP

#include "Vector3.hpp"

/// \class  Camera
/// \brief  This is the object through what
///         the player is seeing the game
class Camera
{
public:

	/// \see Camera.inl for implementation
	inline void SetFar			(unsigned short far);
	inline void SetNear			(unsigned short near);
	inline void SetResolution	(unsigned short resolution);
	inline void SetFocalLength	(float focal);

	inline unsigned short GetFar			(void) const;
	inline unsigned short GetNear			(void) const;
	inline unsigned short GetResolution		(void) const;
	inline float		  GetFocalLength	(void) const;

	inline const Vector3f & GetPosition(void) const;

private:

	unsigned short	m_far;			///< How far  can we see ?
	unsigned short	m_near;			///< How near can we see ?
	unsigned short	m_resolution;	///< How many rays are cast ?
	float			m_focalLength;	///< What is the angle between rays ?

	Vector3f		m_position;		///< The camera position in 3D 
};

#include "Camera.inl"

#endif // _RAYCASTER_HPP
