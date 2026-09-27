#include "ParkingLot.hpp"
#include "EntryGate.hpp"
#include "ExitGate.hpp"
#include "ParkingRate.hpp"
#include "Vehicle.hpp"

#include <iostream>
#include <thread>
#include <vector>

int main() {

    /*
     * 2 floors
     *
     * Each floor:
     * 2 compact
     * 2 regular
     * 1 large
     */
    ParkingLot parkingLot(2,2,2,1);
    ParkingRate parkingRate(50.0);

    EntryGate entryGate1(1,&parkingLot);
    EntryGate entryGate2(2,&parkingLot);

    ExitGate exitGate(1,&parkingLot,&parkingRate);

    parkingLot.displayInfo();

    // Vehicles are owned by main.
    Vehicle bike1("KA01BIKE",VehicleType::BIKE,"Red");
    Vehicle car1("KA01CAR1",VehicleType::CAR,"Blue");
    Vehicle car2("KA01CAR2",VehicleType::CAR,"Black");
    Vehicle truck1("KA01TRUCK",VehicleType::TRUCK,"White");

    /*
     * Normal entry flow.
     */
    Ticket* ticket1 = entryGate1.enter(&bike1);
    Ticket* ticket2 = entryGate2.enter(&car1);
    Ticket* ticket3 = entryGate1.enter(&truck1);

    parkingLot.displayOccupancy();

    /*
     * Concurrency demonstration.
     *
     * Multiple entry gates trying to park
     * vehicles at approximately the same time.
     */
    std::cout<< "\n========== CONCURRENCY TEST ==========\n";

    Vehicle concurrentCar1("CONCURRENT1",VehicleType::CAR,"Silver");
    Vehicle concurrentCar2("CONCURRENT2",VehicleType::CAR,"Grey");

    Ticket* concurrentTicket1 = nullptr;
    Ticket* concurrentTicket2 = nullptr;

    std::thread t1([&]() {
        concurrentTicket1 = entryGate1.enter(&concurrentCar1);
    });

    std::thread t2([&]() {
        concurrentTicket2 = entryGate2.enter(&concurrentCar2);
    });

    t1.join();
    t2.join();

    parkingLot.displayOccupancy();

    /*
     * Exit one vehicle.
     */
    if (ticket2) {
        exitGate.exit(ticket2,PaymentMethod::CARD);
    }

    parkingLot.displayOccupancy();

    /*
     * Cleanup tickets.
     *
     * Important:
     * Ticket does NOT own Vehicle.
     */
    delete ticket1;
    delete ticket2;
    delete ticket3;
    delete concurrentTicket1;
    delete concurrentTicket2;

    return 0;
}