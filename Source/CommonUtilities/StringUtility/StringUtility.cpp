#include "StringUtility.h"
#include <algorithm>

namespace CommonUtilities
{
	void ReplacePartsInString(std::string& aSource, const std::string& aReplace, const std::string& aReplaceWith)
	{
		size_t index = 0;
		while ((index = aSource.find(aReplace, index)) != std::string::npos)
		{
			aSource.replace(index, aReplace.length(), aReplaceWith);
			index += aReplaceWith.length();
		}
	}

	std::wstring StringToWide(std::string str)
	{
		std::wstring wide_string(str.begin(), str.end());
		return wide_string;
	}

	std::string GetDirectoryFromPath(const std::string& filepath)
	{
		size_t off1 = filepath.find_last_of('\\');
		size_t off2 = filepath.find_last_of('/');
		if (off1 == std::string::npos && off2 == std::string::npos) //If no slash or backslash in path?
		{
			return "";
		}
		if (off1 == std::string::npos)
		{
			return filepath.substr(0, off2);
		}
		if (off2 == std::string::npos)
		{
			return filepath.substr(0, off1);
		}
		//If both exists, need to use the greater offset
		return filepath.substr(0, std::max(off1, off2));
	}

	std::string GetFileExtension(const std::string& filename)
	{
		size_t off = filename.find_last_of('.');
		if (off == std::string::npos)
		{
			return {};
		}
		return std::string(filename.substr(off + 1));
	}
}

