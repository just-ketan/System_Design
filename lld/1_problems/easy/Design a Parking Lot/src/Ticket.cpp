#include "Ticket.hpp"

Ticket::Ticket(const std::string& ticketId,
               Vehicle* vehicle,
               ParkingSpot* parkingSpot)
    : ticketId(ticketId),
      vehicle(vehicle),
      parkingSpot(parkingSpot),
      entryTime(std::chrono::system_clock::now()) {}

const std::string& Ticket::getTicketId() const {    return ticketId; }
Vehicle* Ticket::getVehicle() const {   return vehicle; }
ParkingSpot* Ticket::getParkingSpot() const {   return parkingSpot; }

std::chrono::system_clock::time_point
Ticket::getEntryTime() const {
    return entryTime;
}