#include <string>
namespace CommonUtilities
{
	// Replaces all occurances of [aReplace] in [aSource] with [aReplaceWith].
	void ReplacePartsInString(std::string& aSource, const std::string& aReplace, const std::string& aReplaceWith);

	std::wstring StringToWide(std::string str);
	std::string GetDirectoryFromPath(const std::string& filepath);
	std::string GetFileExtension(const std::string& filename);
}
