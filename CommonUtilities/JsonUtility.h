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
		
		template <typename T> 
		T ParseValue(const char* aMemberName) const;
	private:
		rapidjson::Document myJsonDocument;
	};
	
	template<typename T>
	inline T JsonUtility::ParseValue(const char* aMemberName) const
	{
		rapidjson::Value::ConstMemberIterator member = myJsonDocument.FindMember(aMemberName);
		assert((member != myJsonDocument.MemberEnd()) && (aMemberName) && (" not found."));
		assert((member->value.Is<T>()) && aMemberName);
		return member->value.Get<T>();
	}
}

