#include "Utils.h"

#include <random>

using namespace Utils;

Utils::Flexible<string> CustomString::splitString(string delimiter) {
	Utils::Flexible<string> stringSplits;
	if (this->m_data.size() == 0) return stringSplits;
	int lastIndexOf = 0;
	while (lastIndexOf != this->m_data.size()) {
		if (this->m_data.substr(lastIndexOf).find(delimiter) == -1) { stringSplits.push_back(this->m_data.substr(lastIndexOf)); break; }
 		int indexOf = lastIndexOf + this->m_data.substr(lastIndexOf).find(delimiter);
		size_t length = indexOf - lastIndexOf;
		string part = this->m_data.substr(lastIndexOf, length);
		stringSplits.push_back(part);
		lastIndexOf = indexOf + 1;
	}
	return stringSplits;
}

string Utils::CustomString::compose(int count, string delimiter, ...) {
	string composedString{};
	va_list argList;
	va_start(argList, (count+1));
	for (int argIdx = 0; argIdx < count; argIdx++) {
		string part = va_arg(argList, string);
		composedString += delimiter + part;
	}
	return composedString;
}

string Utils::CustomString::uuidGEN(int length) {
	const int codeCharsCount = 61;
	const char* chars = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890!";
	string uuid{};
	srand(time(0)); // Seed rand by current time for more unpredictable indices
	for (int uuidIdx = 0; uuidIdx < length; uuidIdx++) {
		int randomIdx = rand() % (codeCharsCount + 1);
		uuid += *(chars + randomIdx);
	}
	return uuid;
}

bool Utils::CustomString::startsWith(string str, string part) {
	return (str.find(part, 0) == 0) ? true : false;
}