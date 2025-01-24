#pragma once

#include <string>
#include <iostream>

#include <cstdarg>

using namespace std;



namespace Utils {
	template <typename Type>
	class Flexible {
	public:
		Flexible();
		~Flexible();
		Type& operator[](int indexOf) {
			if (indexOf > this->m_currentSize) {
				std::cerr << "Index is out of range";
			}
			return *(m_memory + indexOf);
		}
		const Type operator[](int indexOf) const {
			if (indexOf > this->m_currentSize) {
				std::cerr << "Index is out of range";
			}
			return *(m_memory + indexOf);
		}
		void push_back(Type element);
		//#-- Definition of accessors
		inline size_t getExpansion() { return this->m_currentSize; }
	private:
		size_t m_currentCapacity{};
		size_t m_currentSize{};
		Type* m_memory;
	};
	template <typename Type>
	Utils::Flexible<Type>::Flexible() {
		this->m_currentCapacity = 4;
		this->m_currentSize = 0;
		this->m_memory = new Type[this->m_currentCapacity]; // no use of std::malloc, because of the requirement to call the constructor in case of default types like std::string
	}

	template <typename Type>
	Utils::Flexible<Type>::~Flexible() {
		delete[] this->m_memory;
	}

	template <typename Type>
	void Utils::Flexible<Type>::push_back(Type element) {
		if (!((this->m_currentSize + 1) > this->m_currentCapacity)) {
			*(this->m_memory + this->m_currentSize) = element;
			this->m_currentSize += 1;
		}
		else {
			Type* tmp_memory = new Type[this->m_currentCapacity];
			for (size_t index = 0; index < this->m_currentSize; index++) {
				*(tmp_memory + index) = *(this->m_memory + index);
			} //std::memcpy() not usabale, because of abstract datatypes
			this->m_currentCapacity *= 2;
			delete[] this->m_memory;
			this->m_memory = new Type[this->m_currentCapacity];
			for (size_t index = 0; index < this->m_currentSize; index++) {
				*(m_memory + index) = *(tmp_memory + index);
			}
			push_back(element);
		}
	}
	class CustomString {
		public:
			CustomString() : m_data("") {};
			CustomString(string data) : m_data(data) {};
			string operator=(string newData) {
				this->m_data = newData;
				return newData;
			}
			char operator[](int idx) {
				return this->m_data[idx];
			}


			inline string data() { return this->m_data; };
			Utils::Flexible<string> splitString(string delimiter);

			static string compose(int count, string delimiter = " ", ...);
			static string uuidGEN(int length);
			static bool startsWith(string, string);

		private:
			string m_data = "";
	};
}