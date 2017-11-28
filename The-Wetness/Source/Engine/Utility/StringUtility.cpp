/// \file       StringUtility.cpp
/// \date       27/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Utility/StringUtility.hpp"

/// \brief	Returns the path to the resource folder
/// \param  env The executable path
/// \return A string containing the path to the resource folder
std::string GetResourcePath(std::string const& env)
{
	std::string separator      { "\\" };
	std::string projectName    { "The-Wetness" };
	std::string resourceFolder { "Resource" };

	std::string x;

	// Searches the first occurrence of the project name in env path
	size_t projectIndex = env.find(projectName);

	// Constructs a string containing the project path
	std::string resourceFolderPath { env.begin(), env.begin() + projectIndex };

	// Concatenates with the resource folder
	resourceFolderPath += projectName + separator + 
						  projectName + separator + 
		                  resourceFolder + separator;

	return resourceFolderPath;
}

/// \param  Converts a string into a wstring
/// \param  env The string to convert
/// \return The converted string
std::wstring StringToWString(std::string const& env)
{
	std::wstring_convert <std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(env);
}