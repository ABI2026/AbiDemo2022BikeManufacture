#include "Bike.h"

Bike::Bike::Bike() {
	this->m_bikeUUID = Utils::CustomString::uuidGEN(10);
	this->m_componentCount = 0;
	this->m_model = "";
	this->m_fileName = "";
}

Bike::Bike::Bike(string fileName) {
	this->m_fileName = fileName;
	bool configLoaded = this->readConfigFromFile();
	configLoaded ? void() : std::_Xinvalid_argument("Could not load config. Invalid File Name");
	bool correctConfigFormat = this->checkConfigFormat();
	if (!correctConfigFormat) {
		std::cerr << "[Error]: Configurationfile does not have to correct format. Please reformat and try again";
	} else {
		this->autoAssamble();
	}
}

Bike::Bike::~Bike() = default;

bool Bike::Bike::readConfigFromFile() {
	const char* basePath = "./config/";
	fstream configFile(basePath + this->m_fileName, ios::in);
	if (!fs::exists(basePath + this->m_fileName)) {
		return false;
	}
	string line{};
	while (configFile) {
		getline(configFile, line);
		this->m_configLines.push_back(Utils::CustomString(line));
	}
	return true;
}

bool Bike::Bike::checkConfigFormat() {
	bool valid = true;
	for (int configLineIdx = 0; configLineIdx < this->m_configLines.getExpansion(); configLineIdx++) {
		Utils::Flexible<string> splittedConfigLine = this->m_configLines[configLineIdx].splitString(";");
		splittedConfigLine.getExpansion() == 2 ? bool() : valid = false;
	}
	return valid;
}

void Bike::Bike::autoAssamble() { // Alias: "hinzufuegenKomp()"
	BikeComponents::Component* framePart = nullptr;
	Utils::Flexible<BikeComponents::Component*> gearShiftParts;
	Utils::Flexible<BikeComponents::Component*> singleItems;

	for (size_t configLineIdx = 0; configLineIdx < this->m_configLines.getExpansion(); configLineIdx++) {
		Utils::CustomString configLine = this->m_configLines[configLineIdx];
		string id = configLine.splitString(",")[0];
		Utils::Flexible<string> componentArgs = configLine.splitString(";");

		//#-- Sorting parts by ID
		if (Utils::CustomString::startsWith(id, "f")) {
			BikeComponents::FramePart* framePart_ = new BikeComponents::FramePart(componentArgs[0], componentArgs[1]);
			framePart = framePart_;
		}
		else if (Utils::CustomString::startsWith(id, "s")) {
			BikeComponents::GearShiftElement* gearShiftElement = new BikeComponents::GearShiftElement(componentArgs[0], componentArgs[1]);
			gearShiftParts.push_back(gearShiftElement);
		}
		else if (Utils::CustomString::startsWith(id, "i")) {
			BikeComponents::SingleItem* singleItem = new BikeComponents::SingleItem(componentArgs[0], componentArgs[1]);
			singleItems.push_back(singleItem);
		}
	}
	/*
		@brief
		No sorting algorithm for id index (example: f0)
												 ^
		It has to be specified correctly in the bike
		config file (.txt)
	*/

	this->addComponent(framePart);

	for (int compIdx = 0; compIdx < gearShiftParts.getExpansion(); compIdx++) {
		this->addComponent(gearShiftParts[compIdx]);
	}
	for (int compIdx = 0; compIdx < singleItems.getExpansion(); compIdx++) {
		this->addComponent(singleItems[compIdx]);
	}
}

void Bike::Bike::addComponent(BikeComponents::Component* component) {
	if (this->m_componentCount == 0) {
		this->m_head.next = component;
	}
	else {
		BikeComponents::Component* tmp = this->m_head.next;
		while (tmp->getNextComponent() != nullptr) {
			tmp = tmp->getNextComponent();
		}
		tmp->setNext(component);
		component->setPrevious(tmp);
	}
	this->m_componentCount++;
}

void Bike::Bike::displayComponents() const {
	BikeComponents::Component* tmp = this->m_head.next;
	while (tmp->getNextComponent() != nullptr) {
		std::cout << tmp->repr() << "\n";
		tmp = tmp->getNextComponent();
	}
}

float Bike::Bike::determineFullWeightKG() const {
	float* fullWeight = new float(0);
	auto callback = [&](BikeComponents::Component* component, float* fullWeight) {
		*fullWeight += component->getComponentWeight();
		return 0.f;
	};
	this->iterateAction(&callback, fullWeight);
	return (*fullWeight / 1000); // Return value in kg -> g / 1000
}

float Bike::Bike::determinePrice() const {
	float* fullPrice = new float(0);
	auto callback = [&](BikeComponents::Component* component, float* fullPrice) {
		*fullPrice += component->getComponentPrice();
	};
	this->iterateAction(&callback, fullPrice);
	return *fullPrice;
}

bool Bike::Bike::complete() {
	return (this->m_configLines.getExpansion() >= 16) ? true : false;
}


// @info !experimental!
bool Bike::Bike::replaceComponent(BikeComponents::Component* newComponent) {
	return false;
	//not implemeted yet
}

