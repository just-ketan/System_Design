#include "ParkingRate.hpp"

ParkingRate::ParkingRate(double hourlyRate)
    : hourlyRate(hourlyRate) {}

double ParkingRate::calculateFee(std::chrono::system_clock::time_point entryTime, std::chrono::system_clock::time_point exitTime ) const {
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(exitTime - entryTime);
    double hours = static_cast<double>(duration.count()) / 60.0;
    if (hours < 1.0) {  hours = 1.0;    }

    return hours * hourlyRate;
}