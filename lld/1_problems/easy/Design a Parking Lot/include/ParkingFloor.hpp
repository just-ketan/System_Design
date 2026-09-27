#ifndef PARKING_FLOOR_HPP
#define PARKING_FLOOR_HPP

#include "parkingSpot.hpp"
#include <memory>
#include <vector>

class ParkingFloor{
    private:
        int floorId;
        std::vector<std::unique_ptr<ParkingSpot>> spots;

    public:
        ParkingFloor(int floorId, int compactSpots, int regularSpots, int largeSpots);
        int getFloorId() const;
        ParkingSpot* findAvailableSpot(const Vehicle* vehicle) const;
        ParkingSpot* findSpot(int spotId) const;

        void displayInfo() const;
        void displayOccupancy() const;
};
#endif