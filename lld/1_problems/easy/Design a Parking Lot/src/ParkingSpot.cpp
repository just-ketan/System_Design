#include "ParkingSpot.hpp"
#include <iostream>

ParkingSpot::ParkingSpot(int spotId, SpotType type){
    this->spotId = spotId;
    this->type = type;
    this->vehicle = nullptr;
    this->available = true;
}

int ParkingSpot::getSpotId() const {    return spotId;  }
SpotType ParkingSpot::getSpotType() const { return type;    }
Vehicle* ParkingSpot::getVehicle() const {  return vehicle; }
bool ParkingSpot::isAvailable() const { return available;   }

//entry sequence
bool ParkingSpot::canFitVehicle(const Vehicle* vehicle) const {
    if(!vehicle)    return false;

    switch(vehicle->getVehicleType()){
        case VehicleType::BIKE:    return true;    // can fit anywhere
        case VehicleType::CAR:  return type != SpotType::COMPACT;   //anywhere but compact space
        case VehicleType::BUS:
        case VehicleType::TRUCK:    return type == SpotType::LARGE; //only supported is space is large enough
    }

    return false;   //otw
}

bool ParkingSpot::parkVehicle(Vehicle* vehicle) {
    // check if we can fit the incoming vehicle in available spot
    if(!canFitVehicle(vehicle) || !available)   return false;

    // dedicate this spot to vehicle
    this->vehicle = vehicle;

    // mark the place and not available
    available = false;
    return true;
}


Vehicle* ParkingSpot::removeVehicle(){
    // deallocate the vehicle and mark status as available
    if(!vehicle)    return nullptr;
    Vehicle* removing = vehicle;    // store return value
    vehicle = nullptr;
    available = true;

    return removing;
}

void ParkingSpot::displayInfo() const {
    std::cout<<"Spot "<<spotId<<" (";
    switch(type){
        case SpotType::COMPACT: std::cout<<"COMPACT";   break;
        case SpotType::REGULAR: std::cout<<"REGULAR";   break;
        case SpotType::LARGE:   std::cout<<"LARGE";     break;
    }
    std::cout<<" ):"<<(available ? "Available":"Occupied");
    if(vehicle){
        std::cout<<" by ";
        vehicle->displayInfo();
    }else{
        std::cout<<std::endl;
    }
}