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
	std::string resourceFolder { "Resource" };

	std::string projectRootUper  { "The-Wetness" };
	std::string projectRootLower { "the-wetness" };

	std::string projectRoot = (env.find(projectRootUper) != std::string::npos) ? projectRootUper : projectRootLower;
	
	// Searches the first occurrence of the project name in env path
	size_t projectIndex = env.find(projectRoot);

	// Constructs a string containing the project path
	std::string resourceFolderPath { env.begin(), env.begin() + projectIndex };

	// Concatenates with the resource folder
	resourceFolderPath += projectRoot     + separator +
						  projectRootUper + separator +
		                  resourceFolder  + separator;

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