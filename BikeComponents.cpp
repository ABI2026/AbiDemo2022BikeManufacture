#include "BikeComponents.h"

BikeComponents::Component::Component(Utils::CustomString parts0) {
	Utils::Flexible<string> args = parts0.splitString(",");
	if (args.getExpansion() < 5) {
		std::cerr << "Could not construct Component. Too few arguments!";
	}
	this->m_id = args[0];
	this->m_identifier = args[1];
	this->m_weight = stoi(args[2]);
	this->m_price = stof(args[3]);
	this->m_manufacture = args[4];
}

BikeComponents::GearShiftElement::GearShiftElement(Utils::CustomString parts0, Utils::CustomString parts1) : Component::Component(parts0) {
	Utils::Flexible<string> args = parts1.splitString(",");
	if (args.getExpansion() < 2) {
		std::cerr << "Could not construct FramePart object. Too few arguments!";
	}
	this->m_group = args[0];
	this->m_detail = args[1];
}

string BikeComponents::GearShiftElement::repr() {
	return Utils::CustomString::compose(7, "\n",
		("ID=" + this->getComponentID()),
		("Identifier: " + this->m_identifier),
		(this->m_identifier + " weight: " + to_string(this->m_weight) + "g"),
		("Price: " + to_string(this->m_price)),
		("Manufacture: " + this->m_manufacture),
		("Group: " + this->m_group),
		("Detail: " + this->m_detail)
	);
}

BikeComponents::FramePart::FramePart(Utils::CustomString parts0, Utils::CustomString parts1) : Component::Component(parts0) {
	Utils::Flexible<string> args = parts1.splitString(",");
	if (args.getExpansion() < 2) {
		std::cerr << "Could not construct FramePart object. Too few arguments!";
	}
	this->m_group = args[0];
	this->m_dimensions = args[1];
}

string BikeComponents::FramePart::repr() {
	return Utils::CustomString::compose(7, "\n",
		("ID=" + this->getComponentID()),
		("Identifier: " + this->m_identifier),
		(this->m_identifier + " weight: " + to_string(this->m_weight) + "g"),
		("Price: " + to_string(this->m_price)),
		("Manufacture: " + this->m_manufacture),
		("Group: " + this->m_group),
		("Dimensions: " + this->m_dimensions)
	);
}

BikeComponents::SingleItem::SingleItem(Utils::CustomString parts0, Utils::CustomString parts1) : Component::Component(parts0) {
	Utils::Flexible<string> args = parts1.splitString(",");
	if (args.getExpansion() < 2) {
		std::_Xlength_error("Could not construct SingleItem objekt. Too few arguments!");
	}
	this->m_name = args[0];
	this->m_dimensions = args[1];
}

string BikeComponents::SingleItem::repr() {
	return Utils::CustomString::compose(7, "\n",
		("ID=" + this->getComponentID()),
		("Identifier: " + this->m_identifier),
		(this->m_identifier + " weight: " + to_string(this->m_weight) + "g"),
		("Price: " + to_string(this->m_price)),
		("Manufacture: " + this->m_manufacture),
		("Name: " + this->m_name),
		("Dimensions: " + this->m_dimensions)
	);
}