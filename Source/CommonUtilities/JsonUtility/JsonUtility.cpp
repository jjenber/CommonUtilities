#include "JsonUtility.h"
#include <fstream>
#include <assert.h>
namespace CommonUtilities
{
	JsonUtility::JsonUtility(const char* aFilePath)
	{
		Open(aFilePath);
	}

	bool JsonUtility::Open(const char* aFilePath)
	{
		std::ifstream inputFile(aFilePath);

		if (!inputFile.is_open()) { return false; }

		rapidjson::IStreamWrapper streamWrapper(inputFile);
		myJsonDocument.ParseStream(streamWrapper);

		return !myJsonDocument.HasParseError();
	}

	// Does not deallocate memory.
	void JsonUtility::Clear()
	{
		myJsonDocument.RemoveAllMembers();
	}
}