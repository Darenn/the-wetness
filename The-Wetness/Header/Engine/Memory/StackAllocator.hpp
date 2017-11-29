/// \file       StackAllocator.hpp
/// \date       29/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _STACK_ALLOCATOR_HPP
#define _STACK_ALLOCATOR_HPP

/// \class	StackAllocator
class StackAllocator
{
public:

	inline void Clear();
	template <typename T> void * Allocate  (size_t n);

private:

	friend class Engine;
	friend class RenderingEngine;

	inline StackAllocator(size_t const size);
	inline StackAllocator(StackAllocator const& allocator);
	inline ~StackAllocator();

private:

	size_t			m_size;
	size_t			m_index;
	unsigned char * m_aData;
};

#include "Impl/StackAllocator.inl"

/// \brief	A stack allocator can also be a FrameAllocator
typedef StackAllocator FrameAllocator;

#endif // _STACK_ALLOCATOR_HPP
