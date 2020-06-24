#include "JsonUtility.h"
#include <fstream>
#include <assert.h>
#include <iostream>
namespace CommonUtilities
{
	JsonUtility::JsonUtility(const char* aFilePath, bool aCreateIfNotFound)
	{
		Open(aFilePath, aCreateIfNotFound);
	}

	bool JsonUtility::Open(const char* aFilePath, bool aCreateIfNotFound)
	{
		std::ios::openmode openMode = std::ios::in;
		if (aCreateIfNotFound)
		{
			openMode |= std::ios::out | std::ios::app;
		}
		std::fstream inputFile;
		inputFile.open(aFilePath, openMode);

		if (!inputFile.is_open())
		{
			std::cout << "Error: Couldn't find the document " << aFilePath << std::endl;
			return false; 
		}

		rapidjson::IStreamWrapper streamWrapper(inputFile);
		myJsonDocument.ParseStream(streamWrapper);
		if (myJsonDocument.HasParseError())
		{
			rapidjson::ParseErrorCode error = myJsonDocument.GetParseError();
			std::cout << "Error: "<< ParseErrorCode(error) << aFilePath << std::endl;
			return false;
		}
		return true;
	}

	// Does not deallocate memory. The capacity stays the same.
	void JsonUtility::Clear()
	{
		myJsonDocument.RemoveAllMembers();
	}

	void JsonUtility::IterateOverArray(const char* aMemberName, std::function<void(const rapidjson::Value& anElement)> aCallback)
	{
		rapidjson::Value::ConstMemberIterator member = myJsonDocument.FindMember(aMemberName);
		if ((member == myJsonDocument.MemberEnd()))
		{
			return;
		}
		if (!member->value.IsArray())
		{
			assert(false && "Member is not an array.");
			return;
		}
		for (auto& el : member->value.GetArray())
		{
			aCallback(el);
		}
	}

	bool JsonUtility::HasError() const
	{
		return myJsonDocument.HasParseError();
	}

	std::string JsonUtility::GetParseErrorMessage() const
	{
		return ParseErrorCode(myJsonDocument.GetParseError());
	}

	const char* JsonUtility::ParseErrorCode(rapidjson::ParseErrorCode aCode) const
	{
		switch (aCode)
		{
		case rapidjson::kParseErrorNone:
			return "No error.";
		case rapidjson::kParseErrorDocumentEmpty:
			return "The document is empty.";
		case rapidjson::kParseErrorDocumentRootNotSingular:
			return "The document root must not follow by other values.";
		case rapidjson::kParseErrorValueInvalid:
			return "Invalid value.";
		case rapidjson::kParseErrorObjectMissName:
			return "Missing a name for object member.";
		case rapidjson::kParseErrorObjectMissColon:
			return "Missing a colon after a name of object member.";
		case rapidjson::kParseErrorObjectMissCommaOrCurlyBracket:
			return "Missing a comma or '}' after an object member.";
		case rapidjson::kParseErrorArrayMissCommaOrSquareBracket:
			return "Missing a comma or ']' after an array element.";
		case rapidjson::kParseErrorStringUnicodeEscapeInvalidHex:
			return "Incorrect hex digit after \\u escape in string.";
		case rapidjson::kParseErrorStringUnicodeSurrogateInvalid:
			return "The surrogate pair in string is invalid.";
		case rapidjson::kParseErrorStringEscapeInvalid:
			return "Invalid escape character in string.";
		case rapidjson::kParseErrorStringMissQuotationMark:
			return "Missing a closing quotation mark in string.";
		case rapidjson::kParseErrorStringInvalidEncoding:
			return "Invalid encoding in string.";
		case rapidjson::kParseErrorNumberTooBig:
			return "Number too big to be stored in double.";
		case rapidjson::kParseErrorNumberMissFraction:
			return "Miss fraction part in number.";
		case rapidjson::kParseErrorNumberMissExponent:
			return "Miss exponent in number.";
		case rapidjson::kParseErrorTermination:
			return "Parsing was terminated.";
		case rapidjson::kParseErrorUnspecificSyntaxError:
			return "Unspecific syntax error.";
		default:
			return "Error code not defined.";
		}
	}
}