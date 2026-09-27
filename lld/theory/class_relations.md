# Class Relations :  describes how the objects are connected and interact with one another.

## Association: one class is connected to another, i.e, one object knows about another object
```cpp
// an order can be associated with a customer
class Customer{
    private:
        std::string uname;
        std::string email;
    
    public: 
        Customer(std::string uname, std::string email){
            this->uname = uname;
            this->email = email;
        }
};

class Order{
    private:
        std::string orderId;
        Customer* customer; // coupled object of Customer into Order

    public:
        Order(std::string orderId, Customer* customer){
            this->orderId = orderId;
            this->customer = customer;
        }
};
```
here `order` is storing reference to `customer`. this allows every generated order to be connected to a customer.

## Aggregation: sometimes, one object does more than knowing others, it groups them. this is called "has-a" representation with weak ownership. one object contains groups of other objects, but those objects can still exist independently.

```cpp
class EngineeringTeam{
    private:
        std::string teamName;
        std::vector<Developer*> devs;

    public:
        EngineeringTeam(std::string teamName, std::vector<Developers*> devs){
            this->teamName = teamName;
            this->devs = devs;
        }
};

Developer* dev1 = new Developer("Alice");
Developer* dev2 = new Developer("Bob");
EngineeringTeam("payments", {dev1, dev2});
```
if in case the scope of EngineeringTeam ends, the individual Developer objects can still exist, or can be moved to other instances of EngineeringTeam.

## Composition: is a stricter "has-a" association fostering strong ownership. the child is important part of parent and cannot exist independently from it
```cpp
class OrderItem{
    private:
        std::string product;
        int qtty;

    public:
        OrderItem(std::string product, int qtty){
            this->product = product;
            this->qtty = qtty;
        }
};

class Order{
    private:
        std::string orderId;
        std::vector<OrderItem> items;

    public:
        Order(std::string orderid){
            this->orderId = orderid;
        }

        void addItem(std::string prod, int qtty){
            items.push_back(OrderItem(prod, qtty));
        }
};
```
the `order` creates and manages `orderitem` objects and each order item belongs to a specific order (note there is no reference, its direct object) and does not have meaning outside of it

## Dependency: instead of storing objects or references, sometimes we need class to simply perform an additional/important task for an existing class

```cpp
class InvoiceService{
    private:
        TaxCalculator* taxer;
    
    public:
        InvoiceService(TaxCalculator* taxer){
            this->taxer = taxer;
        }

        void createInvoice(int amount){
            int tax = taxxer->calculate(amount);
            int tot = amount  +tax;
            std::cout<<"Invoice total: "<<total<<std::endl;
        }
};
// or it could be something inlined as parameter as well
class InvoiceService{
    public:
        void InvoiceService(int amont, TaxCalculator& taxxer){
            int tax = tazzer->calculate(amount);
            int tot = amount + tax;
            std::cout<<"invoice total "<<tot<<std::endl;
        }
};