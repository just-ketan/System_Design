// our main driver class

#ifndef PARKING_LOT_HPP
#define PARKING_LOT_HPP

#include "ParkingFloor.hpp"
#include "Ticket.hpp"

#include <memory>
#include <mutex>
#include <string>
#include <vector>

class ParkingLot{
    private:
        std::vector<std::unique_ptr<ParkingFloor>> floors;
        mutable std::mutex parkingMutex;
        int nextTicketId;

    public:
        ParkingLot(int floors, int compactPerFloor, int regularPerFloor, int largePerFloor);
        Ticket* parkVehicle(Vehicle* vehicle);
        Vehicle* removeVehicle(Ticket* ticket);
        ParkingSpot* findAvailableSpot(const Vehicle* vehicle) const;

        void displayInfo() const;
        void displayOccupancy() const;
};

#endif