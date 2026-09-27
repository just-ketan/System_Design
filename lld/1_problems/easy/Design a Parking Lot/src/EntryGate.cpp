#include "EntryGate.hpp"
#include <iostream>

EntryGate::EntryGate(int gateId,ParkingLot* parkingLot) : gateId(gateId),parkingLot(parkingLot) {}

Ticket* EntryGate::enter(Vehicle* vehicle) {
    if (!parkingLot || !vehicle) {  return nullptr;    }
    std::cout << "\nEntry Gate "<< gateId<< ": ";
    vehicle->displayInfo();
    std::cout << '\n';
    
    Ticket* ticket = parkingLot->parkVehicle(vehicle);
    if (ticket)   std::cout << "Vehicle parked. Ticket: "<< ticket->getTicketId()<< '\n';
    else    std::cout << "No suitable parking spot available.\n";

    return ticket;
}

int EntryGate::getGateId() const {  return gateId;  }