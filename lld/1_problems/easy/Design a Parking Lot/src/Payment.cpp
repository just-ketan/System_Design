#include "Payment.hpp"
#include <iostream>

Payment::Payment(double amount, PaymentMethod method) : amount(amount), method(method) {}

double Payment::getAmount() const { return amount;  }
PaymentMethod Payment::getPaymentMethod() const { return method;  }

bool Payment::processPayment() const {
    std::cout << "Processing payment of ₹"<< amount << "... ";
    std::cout << "SUCCESS\n";
    return true;
}