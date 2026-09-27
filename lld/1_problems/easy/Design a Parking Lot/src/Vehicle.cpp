#include "Vehicle.hpp"
#include <iostream>

Vehicle::Vehicle(std::string plate, VehicleType type, std::string color){
    this->licensePlate = plate;
    this->type = type;
    this->color = color;
}

std::string Vehicle::getLicensePlate() const {  return licensePlate;    }
std::string Vehicle::getColor() const { return color;   }
VehicleType Vehicle::getVehicleType() const {   return type; }
void Vehicle::displayInfo() const {
    std::cout<<"Vehicle Info: "<<color<< " ";
    switch(type){
        case VehicleType::CAR:  std::cout<<"Car"; break;
        case VehicleType::BIKE: std::cout<<"Bike"; break;
        case VehicleType::TRUCK:    std::cout<<"Truck"; break;
        case VehicleType::BUS:  std::cout<<"Bus";   break;
    }
    std::cout<<" (License "<<licensePlate<<")"<<std::endl;
}
