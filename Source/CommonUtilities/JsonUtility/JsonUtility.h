#pragma once
#include "RapidJSON/document.h"
#include "RapidJSON/istreamwrapper.h"

namespace CommonUtilities
{
	class JsonUtility
	{
	public:
		JsonUtility() = default;
		JsonUtility(const char* aFilePath);

		JsonUtility(const JsonUtility& aCopy) = delete;
		JsonUtility(JsonUtility&& aCopy) = delete;
		JsonUtility& operator=(const JsonUtility& aCopy) = delete;
		JsonUtility& operator=(JsonUtility&& aCopy) = delete;

		bool Open(const char* aFilePath);
		void Clear();
		
		rapidjson::GenericArray<true, rapidjson::Value::ValueType> ParseArray(const char* aMemberName) const;	
		template <typename ValueType> ValueType ParseValue(const char* aMemberName) const;

	private:
		rapidjson::Document myJsonDocument;
	};

	template<typename ValueType>
	inline ValueType JsonUtility::ParseValue(const char* aMemberName) const
	{
		rapidjson::Value::ConstMemberIterator member = myJsonDocument.FindMember(aMemberName);
		assert((member != myJsonDocument.MemberEnd()) && (aMemberName) && (" not found."));
		assert((member->value.Is<ValueType>()) && aMemberName);
		return member->value.Get<ValueType>();
	}

	inline rapidjson::GenericArray<true, rapidjson::Value::ValueType> JsonUtility::ParseArray(const char* aArrayName) const
	{
		return ParseValue<rapidjson::GenericArray<true, rapidjson::Value::ValueType>>(aArrayName);
	}
}

