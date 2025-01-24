# AbiDemo2022BikeManufacture
Functional Version of Abitur Exam "Bike Manufacture"
## Class Documentation

```
  File Utils.h:
```
```
  class Utils::Flexible: Allocator class, providing the function of flexible arrays (similar to std::vector)
  class Utils::CustomString: String helper class, provided in exam for splitting strings by delimiter, storing string data and some static functions
```
---
```
  File Bike.h
```
```
  struct Bike::Category: Datastructure storing the two variables of "IDENTIFIER: string" and "ENSURANCE: bool"
  class Bike::Bike: Class template for Bike-Objects storing the components and additional data
```
---
```
  File BikeComponents.h:
```
```
  namespace BikeComponents: Section for all "Bike" component definitions
  class BikeComponents::Component: Abstract base class template for components of type -> "GearShiftElement", "FramePart" and "SingleItem"
  class BikeComponents::GearShiftElement, BikeComponents::FramePart, BikeComponents::SingleItem: Derivative classes of base class Bike::Components::Component <<abstract>>
```
## Info
``` Bike::replaceComponent(BikeComponents::Component* newComponent) ``` not implemented yet!
