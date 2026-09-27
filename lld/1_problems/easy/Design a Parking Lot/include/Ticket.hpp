#ifndef TICKET_HPP
#define TICKET_HPP

#include "ParkingSpot.hpp"
#include "Vehicle.hpp"

#include <chrono>
#include <string>

class Ticket{
    private:
        std::string ticketId;
        Vehicle* vehicle;
        ParkingSpot* parkingSpot;
        std::chrono::system_clock::time_point entryTime;

    public:
        Ticket(const std::string& ticketId, Vehicle* vehicle, ParkingSpot* parkingSpot);
        const std::string& getTicketId() const;
        Vehicle* getVehicle() const;
        ParkingSpot* getParkingSpot() const;

        std::chrono::system_clock::time_point getEntryTime() const;
};  

#endif

