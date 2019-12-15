#include "../CommonUtilities/JsonUtility.h"
#include <string>
#include <iostream>
int main()
{
	CommonUtilities::JsonUtility json("test.json");
	auto names = json.ParseArray("testArray");
	std::cout << names.begin()->GetString() << std::endl;
	std::cout << (names.begin() + 1)->GetInt() << std::endl;
	
}
