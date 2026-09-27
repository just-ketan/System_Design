#ifndef ENTRY_GATE_HPP
#define ENTRY_GATE_HPP

#include "ParkingLot.hpp"

class EntryGate {
    private:
        int gateId;
        ParkingLot* parkingLot;

    public:
        EntryGate(int gateId, ParkingLot* parkingLot);
        Ticket* enter(Vehicle* vehicle);
        int getGateId() const;
};

#endif