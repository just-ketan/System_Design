#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include<string>

enum class VehicleType{
    CAR,
    BIKE,
    TRUCK,
    BUS
};

class Vehicle{
// what should this class define ? , it should define basica charachteristics of a vehicle
// we will extend this later in main.cpp to have specific entities
    private:
        std::string licensePlate;
        std::string color;
        VehicleType type;

    public:
        Vehicle(std::string licensePlate, VehicleType type, std::string color);

        std::string getLicensePlate() const;   // returns number plate
        std::string getColor() const;   // returns color
        VehicleType getVehicleType() const; // returns the vehicle type
        void displayInfo() const;   // displays the info of current vehicle object
};

#endif