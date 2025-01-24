#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "BikeComponents.h"
#include "Utils.h"

using namespace std;
namespace fs = std::filesystem;

namespace Bike {
	 struct Category {
		private:
			string m_identity{};
			bool m_ensurance;
		public:
			Category() = default;
			Category(string identity) : m_identity(identity), m_ensurance(false) {};

			//Defining accessors
			inline string getIdentity() const { return this->m_identity; }
			inline void setEnsurance(bool b) { this->m_ensurance = b; }
			inline bool getEnsuranceState() const { return this->m_ensurance; }
	};
	struct DoubleLinkedListHead {
		BikeComponents::Component* next = nullptr;
		BikeComponents::Component* previous = nullptr;
	};
	class Bike {
		public:
			Bike();
			Bike(string fileName);
			~Bike();

			void autoAssamble();
			bool replaceComponent(BikeComponents::Component* newComponent);
			float determineFullWeightKG() const;
			float determinePrice() const;

			void displayComponents() const;
			[[nodiscard]] bool complete();

		private:
			const u_int minimumCompCount = 16;
			string m_bikeUUID{};
			u_int m_componentCount = 0;
			string m_model{};
			Utils::Flexible<Utils::CustomString> m_configLines{}; // Alias: KonfigZeilen
			string m_fileName{};
			Category m_category{};

			DoubleLinkedListHead m_head;

			[[nodiscard]] bool readConfigFromFile();
			[[nodiscard]] bool checkConfigFormat();
			
			void addComponent(BikeComponents::Component*);

			template <typename CallbackT, typename ValueT>
			void iterateAction(CallbackT*, ValueT*) const;
	};

	template <typename CallbackT, typename ValueT>
	void Bike::iterateAction(CallbackT* callback, ValueT* value) const {
		BikeComponents::Component* tmp = this->m_head.next;
		while (tmp->getNextComponent()) {
			(*callback)(tmp, value);
			tmp = tmp->getNextComponent();
		}
	}

}
