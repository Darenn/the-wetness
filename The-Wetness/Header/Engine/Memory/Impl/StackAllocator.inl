/// \file       StackAllocator.hpp
/// \date       29/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

/// \brief	Constructor
/// \parma  size The size of the store space
inline StackAllocator::StackAllocator(size_t const size)
: m_size(size)
, m_index(0)
, m_aData(new unsigned char[m_size])
{
	// None
}

/// \brief	Copy constructor
inline StackAllocator::StackAllocator(StackAllocator const & allocator)
{
	// None
}

/// \brief	Destructor
inline StackAllocator::~StackAllocator()
{
	delete[] m_aData;
}

/// \brief	Resets the allocator
inline void StackAllocator::Clear()
{
	m_index = 0;
}

/// \brief	
template <typename T> 
inline void * StackAllocator::Allocate(size_t n)
{
	if (m_index + n * sizeof(T) < m_size)
	{
		void * pData = static_cast<void *>(&m_aData[m_index]);
		m_index += n * sizeof(T);
		return pData;
	}

	return nullptr;
}
