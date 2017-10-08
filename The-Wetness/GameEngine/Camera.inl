/// \file       Camera.inl
/// \date       07/10/2017
/// \package    Raycaster
/// \author     Vincent STEHLY--CALISTO

/// \brief	Sets the far of the camera
/// \param  far The new far to set
inline void Camera::SetFar(unsigned short far)
{
	m_far = far;
}

/// \brief	Sets the Near of the camera
/// \param  near The new near to set
inline void Camera::SetNear(unsigned short near)
{
	m_near = near;
}

/// \brief	Sets the resolution of the camera
/// \param  resolution The new resolution to set
inline void Camera::SetResolution(unsigned short resolution)
{
	m_resolution = resolution;
}

/// \brief	Sets the focal length of the camera
/// \param  focal The new focal length
inline void Camera::SetFocalLength(float focal)
{
	m_focalLength = focal;
}

/// \brief	Returns the far of the camera
/// \return The far of the camera
inline unsigned short Camera::GetFar() const
{
	return m_far;
}

/// \brief	Returns the near of the camera
/// \return The near of the camera
inline unsigned short Camera::GetNear() const
{
	return m_near;
}

/// \brief	Returns the resolution of the camera
/// \return The resolution of the camera
inline unsigned short Camera::GetResolution() const
{
	return m_resolution;
}

/// \brief	Returns the focal length of the camera
/// \return The focal length of the camera
inline float Camera::GetFocalLength() const
{
	return m_focalLength;
}

/// \brief	Returns the current camera position
/// \return The camera position
inline const Vector3f & Camera::GetPosition(void) const
{
	return m_position;
}