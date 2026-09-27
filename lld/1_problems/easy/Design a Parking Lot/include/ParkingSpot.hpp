// now a parking spot should hold vehicles
// so the dependency graph is ParkingSpot -> Vehicle
// this is dependency, cause vehicle objects may exist outside the scope of parkingspot class instance

#ifndef PARKING_SPOT_HPP
#define PARKING_SPOT_HPP

#include "Vehicle.hpp"

// what are the spots in this ParkingSpot class instances
enum class SpotType{
    COMPACT,    // for motorbikes
    REGULAR,    // for cars
    LARGE       // for trucks and bus
};

class ParkingSpot{
    private:
        int spotId; // the spot identifier
        SpotType type;  // which type of spot is it ?
        Vehicle* vehicle;   // ParkingSpot knows/refers to Vehicle class object
        bool available;     // is this instance of spot available

    public:
        ParkingSpot(int spotId, SpotType type);

        int getSpotId() const;
        SpotType getSpotType() const;
        Vehicle* getVehicle() const;
        bool isAvailable() const;

        // define behaviors associated with parking spot
        // on entry we log it and at exit we process exit activities
        bool canFitVehicle(const Vehicle* vehicle) const;
        bool parkVehicle(Vehicle* vehicle);
        // exit activites
        Vehicle* removeVehicle();
        void displayInfo() const;
};

#endif