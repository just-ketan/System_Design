#ifndef PAYMENT_HPP
#define PAYMENT_HPP

enum class PaymentMethod{
    CASH,
    CARD
};

class Payment{
    private:
        double amount;
        PaymentMethod method;

    public:
        Payment(double amount, PaymentMethod method);
        double getAmount() const;
        PaymentMethod getPaymentMethod() const;
        bool processPayment() const;
};

#endif