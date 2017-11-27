/// \file       StringUtility.hpp
/// \date       27/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _STRING_UTILITY_HPP
#define _STRING_UTILITY_HPP

#include <string>
#include <locale>
#include <codecvt>

/// \brief	Returns the path to the resource folder
/// \param  env The executable path
/// \return A string containing the path to the resource folder
std::string GetResourcePath(std::string const& env);

/// \param  Convert a string into a wstring
/// \param  env The string to convert
/// \return The converted string
std::wstring StringToWString(std::string const& env);

#endif // _STRING_UTILITY_HPP
