#pragma once
#include "RapidJSON/document.h"
#include "RapidJSON/istreamwrapper.h"
#include <functional>

namespace CommonUtilities
{
	class JsonUtility
	{
	public:
		JsonUtility() = default;
		JsonUtility(const char* aFilePath, bool aCreateDocIfNotFound = false);

		JsonUtility(const JsonUtility& aCopy) = delete;
		JsonUtility(JsonUtility&& aCopy) = delete;
		JsonUtility& operator=(const JsonUtility& aCopy) = delete;
		JsonUtility& operator=(JsonUtility&& aCopy) = delete;

		bool Open(const char* aFilePath, bool aCreateDocIfNotFound = false);
		
		/// Does not deallocate memory. The capacity stays the same.
		void Clear();
		
		/// Finds an array member and calls the callback each iteration and passes the current element.
		/// Use the getter methods on the rapidjson::Value.
		void IterateOverArray(const char* aMemberName, std::function<void(const rapidjson::Value& anElement)> aCallback);

		/// Finds an array member and calls the callback each iteration and passes the current element. 
		/// All elements must be of same type e.g. integers or strings.
		/// Use IterateOverArray() for multiple types.
		template <class ValueType>
		void IterateOverArraySingleType(const char* aMemberName, std::function<void(const ValueType& anElement)> aCallback);

		template <typename ValueType>
		ValueType ParseValue(const char* aMemberName) const;
		
		/// Returns true if a ParseError has occurred. Call GetParseErrorMessage() to get a string with potential info.
		bool HasError() const;
		/// Returns a string with the current ParseErrorMessage. Call HasError() to check if an error exists before calling GetParseErrorMessage.
		std::string GetParseErrorMessage() const;

	private:
		/// Returns a string with the mapped error message.
		const char* ParseErrorCode(rapidjson::ParseErrorCode aCode) const;

		rapidjson::Document myJsonDocument;
	};

	template<class ValueType>
	inline void JsonUtility::IterateOverArraySingleType(const char* aMemberName, std::function<void(const ValueType& anElement)> aCallback)
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
			if (el.Is<ValueType>())
			{
				assert(false && "An element in the array is the wrong type.");
				return;
			}
			aCallback(el.Get<ValueType>());
		}
	}

	template<typename ValueType>
	inline ValueType JsonUtility::ParseValue(const char* aMemberName) const
	{
		rapidjson::Value::ConstMemberIterator member = myJsonDocument.FindMember(aMemberName);
		assert((member != myJsonDocument.MemberEnd()) && (aMemberName) && (" not found."));
		assert((member->value.Is<ValueType>()) && aMemberName);
		return member->value.Get<ValueType>();
	}
}

