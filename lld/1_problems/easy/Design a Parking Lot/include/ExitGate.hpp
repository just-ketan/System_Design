#ifndef EXIT_GATE_HPP
#define EXIT_GATE_HPP

#include "ParkingLot.hpp"
#include "ParkingRate.hpp"
#include "Payment.hpp"

class ExitGate {
    private:
        int gateId;
        ParkingLot* parkingLot;
        ParkingRate* parkingRate;

    public:
        ExitGate(int gateId,ParkingLot* parkingLot,ParkingRate* parkingRate);
        bool exit(Ticket* ticket,PaymentMethod paymentMethod);
        int getGateId() const;
};

#endif