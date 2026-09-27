#include "ParkingLot.hpp"

#include <iostream>

ParkingLot::ParkingLot(int numberOfFloors,int compactSpotsPerFloor,int regularSpotsPerFloor,int largeSpotsPerFloor)
    : nextTicketId(1) {
    for (int i = 1; i <= numberOfFloors; ++i) {
        floors.push_back(
            std::make_unique<ParkingFloor>(
                i,
                compactSpotsPerFloor,
                regularSpotsPerFloor,
                largeSpotsPerFloor
            )
        );
    }
}

ParkingSpot* ParkingLot::findAvailableSpot(const Vehicle* vehicle) const {
    for (const auto& floor : floors) {
        ParkingSpot* spot = floor->findAvailableSpot(vehicle);
        if (spot) { return spot;    }
    }
    return nullptr;
}

Ticket* ParkingLot::parkVehicle(Vehicle* vehicle) {
    if (!vehicle) { return nullptr; }

    /*
     * Critical section:
     *
     * Find an available spot
     * +
     * Occupy it
     *
     * must happen atomically.
     */
    std::lock_guard<std::mutex> lock(parkingMutex);

    ParkingSpot* spot = findAvailableSpot(vehicle);
    if (!spot) {    return nullptr; }
    if (!spot->parkVehicle(vehicle)) {  return nullptr; }

    std::string ticketId =  "T" + std::to_string(nextTicketId++);
    return new Ticket(ticketId,vehicle,spot);
}

Vehicle* ParkingLot::removeVehicle(Ticket* ticket) {
    if (!ticket) {  return nullptr;    }
    std::lock_guard<std::mutex> lock(parkingMutex);
    ParkingSpot* spot = ticket->getParkingSpot();
    if (!spot) {    return nullptr;    }
    return spot->removeVehicle();
}

void ParkingLot::displayInfo() const {
    std::lock_guard<std::mutex> lock(parkingMutex);
    std::cout << "\n========== PARKING LOT ==========\n";
    for (const auto& floor : floors) {  floor->displayInfo();   }
    std::cout << "=================================\n";
}

void ParkingLot::displayOccupancy() const {
    std::lock_guard<std::mutex> lock(parkingMutex);
    std::cout << "\n========== OCCUPANCY ==========\n";
    for (const auto& floor : floors) {  floor->displayOccupancy();     }
    std::cout << "===============================\n";
}