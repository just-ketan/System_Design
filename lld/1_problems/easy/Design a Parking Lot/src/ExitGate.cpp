#include "ExitGate.hpp"

#include <chrono>
#include <iostream>

ExitGate::ExitGate(int gateId,ParkingLot* parkingLot,ParkingRate* parkingRate): gateId(gateId),parkingLot(parkingLot),parkingRate(parkingRate) {}

bool ExitGate::exit(Ticket* ticket,PaymentMethod paymentMethod) {
    if (!parkingLot ||!parkingRate ||!ticket) { return false;   }

    auto exitTime = std::chrono::system_clock::now();
    double fee = parkingRate->calculateFee(ticket->getEntryTime(),exitTime);

    std::cout << "\nExit Gate "<< gateId<< '\n';
    std::cout << "Ticket: "<< ticket->getTicketId()<< '\n';
    std::cout << "Amount due: ₹"<< fee<< '\n';

    Payment payment(fee,paymentMethod);
    if (!payment.processPayment()) {    return false;    }

    Vehicle* vehicle =  parkingLot->removeVehicle(ticket);
    if (!vehicle) { return false;    }

    std::cout << "Vehicle exited successfully: ";
    vehicle->displayInfo();
    std::cout << '\n';
    return true;
}

int ExitGate::getGateId() const {   return gateId;  }