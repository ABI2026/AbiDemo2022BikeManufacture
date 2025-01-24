#pragma once

#include <string>
#include <cstdarg>

#include "Utils.h"

using namespace std;

typedef unsigned int u_int;

namespace BikeComponents {
	class Component abstract {
		public:
			Component() = default;
			Component(Utils::CustomString parts0);
			~Component() = default;

			// Definition of accessors
			inline string getComponentID() const { return this->m_id; }
			inline void setComponentID(string ID) { this->m_id = ID; }
			inline string getComponentIdentifier() const { return this->m_identifier; }
			inline u_int getComponentWeight() const { return this->m_weight; }
			inline float getComponentPrice() const { return this->m_price; }
			inline string getComponentManufacture() const { return this->m_manufacture; }

			inline Component* getNextComponent() const { return this->m_next; }
			inline Component* getPreviousComponent() const { return this->m_previous; }
			inline void setNext(Component* next) { this->m_next = next; }
			inline void setPrevious(Component* previous) { this->m_previous = previous; }

			virtual string repr() = 0;

		private:
			string m_id;
			Component* m_next = nullptr;
			Component* m_previous = nullptr;
		protected:
			string m_identifier;
			u_int m_weight;
			float m_price;
			string m_manufacture;
	};
	class GearShiftElement : public Component {
		public:	
			GearShiftElement() = default;
			GearShiftElement(Utils::CustomString parts0, Utils::CustomString parts1);
			~GearShiftElement() = default;
			string repr();

			//Definition of accessors
			inline string getComponentGroup() const { return this->m_group; }
			inline string getComponentDetail() const { return this->m_detail; }

		private:
			string m_group;
			string m_detail;
	};
	class FramePart : public Component {
		public:
			FramePart() = default;
			FramePart(Utils::CustomString parts0, Utils::CustomString parts1);
			~FramePart() = default;
			string repr();

			//Definition of accessors
			inline string getComponentGroup() const { return this->m_group; }
			inline string getComponentDimensions() const { return this->m_dimensions; }

		private:
			string m_group;
			string m_dimensions;
	};
	class SingleItem : public Component {
		public:
			SingleItem() = default;
			SingleItem(Utils::CustomString parts0, Utils::CustomString parts1);
			~SingleItem() = default;
			string repr();

			//Definition of accessors
			inline string getComponentIndividualName() const { return this->m_name; }
			inline string getComponentDimensions() const { return this->m_dimensions; }

		private:
			string m_name;
			string m_dimensions;
	};
}
