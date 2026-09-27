#include "ParkingFloor.hpp"
#include <iostream>

ParkingFloor::ParkingFloor(int floorId, int compactSpots, int regularSpots, int largeSpots)
    : floorId(floorId) {
    int spotId = 1;

    for (int i = 0; i < compactSpots; ++i) {
        spots.push_back(
            std::make_unique<ParkingSpot>(
                spotId++, SpotType::COMPACT
            )
        );
    }

    for (int i = 0; i < regularSpots; ++i) {
        spots.push_back(
            std::make_unique<ParkingSpot>(
                spotId++, SpotType::REGULAR
            )
        );
    }

    for (int i = 0; i < largeSpots; ++i) {
        spots.push_back(
            std::make_unique<ParkingSpot>(
                spotId++, SpotType::LARGE
            )
        );
    }
}

int ParkingFloor::getFloorId() const {
    return floorId;
}

ParkingSpot* ParkingFloor::findAvailableSpot(
    const Vehicle* vehicle
) const {

    for (const auto& spot : spots) {
        if (spot->isAvailable() &&
            spot->canFitVehicle(vehicle)) {
            return spot.get();
        }
    }

    return nullptr;
}

ParkingSpot* ParkingFloor::findSpot(int spotId) const {
    for (const auto& spot : spots) {
        if (spot->getSpotId() == spotId) {
            return spot.get();
        }
    }

    return nullptr;
}

void ParkingFloor::displayInfo() const {
    std::cout << "\nFloor " << floorId << '\n';

    for (const auto& spot : spots) {
        spot->displayInfo();
    }
}

void ParkingFloor::displayOccupancy() const {
    int available = 0;
    int occupied = 0;

    for (const auto& spot : spots) {
        if (spot->isAvailable()) {
            ++available;
        } else {
            ++occupied;
        }
    }

    std::cout << "Floor " << floorId<< " | Available: " << available<< " | Occupied: " << occupied<< '\n';
}