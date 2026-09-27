# OCP : OPEN CLOSED PRINCIPLE

adding a new feature causes editing numerous existing classes, introduceing bugs at places we didnt even touch? well we are probably violating OCP.

## Problem : A growing payment system
initially we had one payment method for a checkout feature in e-comerce platform: `credit card`

```cpp
class PaymentProcessor{
    public:
        void processCreditCardPayment(double amount){
            cout<<"processing credit card payment";
            // some complex logic for processing credit card
        }
};
```
and then we use this in checkout service
```cpp
class CheckoutSerice{
    public:
        void processPayment(const string& paymentType){
            PaymentProcessor processor;
            processor.processCreditCardPayment(100.00);
        }
};
```
Now, if client says `add paypal`. then
```cpp
class PaymentProcessor{
    public:
        void processCreditCardPayment(double amount){
            // CC implementation
        }

        void processPayPalPaymeny(double amount){
            // PayPal implementation
        }
};

// now checkout service becomes
class CheckoutService{
    public:
        void processPayment(const string& paymenttype){
            PaymentProcessor processor;
            if(paymenttpye == "CreditCard") processor.processCreditCardPayment(100.00);
            else if(paymenttype=="PayPal")  processor.processPayPalPayment(100.00);
        }
};
```
Now, each time a new payment method is getting introduced, say, `UPI`, `Bitcoin`, `applepay`, we are doing surgery on `CheckoutService` and `PaymentProcessor`, to incorporate the changes. everytime we do this, we risk changing some existing codes, that we did not intend. if-else if or switch logics are harder to interpret

## OCP : Open for Extension, Closed for Modification
every class, module, function, etc, should be open for extension and closed for modification. so in this scenario, `PaymentProcessor` evolves as

```cpp
class PaymentMethod{
    public:
        virtual void processPayment(double amount) = 0;
        virtual ~PaymentMethod() = default;
};
```
the concrete classes extend this `Interface/template`
```cpp
class CreditCardPayment : public PaymentMethod {
    public:
        void processPayment(double amount) override {
            // credit card logic
        }
};

class PayPalPayment : public PaymentMethod {
    public:
        void processPayment(double amount) override {
            // paypal logic
        }
};

class UPIPayment : public PaymentMethod {
    public:
        void processPayment(double amount) override {
            // UPI logic
        }
};
```
and now we update the payment processor to utilize this abstraction

```cpp
class PaymentProcessor{
    public:
        void process(PaymentMethod* paymentmethod, double amount){
            paymentmethod->processPayment(amount);  // directly process the amount from given handler
        }
};
```

and finally the checkout service translates to
```cpp
class CheckoutService {
    public:
        void processPayment(PaymentMethod* method, double amount){
            PaymentProcessor processor;
            processor.process(method, amount);
        }
};

// usage
CheckoutService checkout_srvc;
CreditCardPayment cc_payment;
PayPalPayment pp_payment;
UPIPayemnt upi_payment;

checkout.processPayment(&cc_payment, 100,00);
checkout.processPayment(&pp_payment, 100,00);
checkout.processPayment(&upi_payment, 100,00);
```