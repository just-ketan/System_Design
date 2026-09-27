// simple pricing

#ifndef PARKING_RATE_HPP
#define PARKING_RATE_HPP

#include<chrono>

class ParkingRate{
    private:
        double hourlyRate;
    
    public:
        explicit ParkingRate(double hourlyRate);
        double calculateFee(std::chrono::system_clock::time_point entry_time, std::chrono::system_clock::time_point exit_time) const;
};
#endif