# LOD : LAW OF DEMETER

## PROBLEM : A Simple E Commerce system

imagine we are bulding a simple e-commerce system
we have-
    - A `customer` who owns a `shopping_cart`
    - A `cart` contains list of `items`
    - each `item` is a `product`
    - every `product` has a `price`
this creates a chain as
```yaml
[OrderSrvc] -> [Customer] -> [Cart] -> [list of Items] -> [items] -> [products] -> [price]
```
A falwed approach would be to write something like
```cpp
Money price = customer.getcart().getitems()[0].getproduct().getprice();
```
this chain is coupling several classes and this can go very deep as well. Now any point of modification, say `customer->cart` changes, then the whole chain is flawed and incorrect.

## LOD :  Principle Of Least Knowledge
A method `M` on an object `O` should only call emthods on
```yaml
    - itself : Object `O`
    - its won fields : objects that `O` holds as instance variables
    - its method parameters : objects passed into `M`
    - objects it creates : objects instantiated within `M`
```

## Another Problem : A `NotificationSrvc` needs three pieces of information to send a ride udpate to a passenger
`Driver's name`, `car's license plate` and `passenger's phone numer`. in a hurry, the poor design looks like
```cpp
class NotificationService{
    public:
        void sendRideUpdate(const Ride& ride){
            // getting the name of driver
            std::string drivername = ride.getDriver().getProfile().getName();
            // getting plate number
            std::string plate = ride.getDriver().getVehicle().getRegistration().getLicense();
            // finding passenger phone
            std::string phone = ride.getPassenger().getContact().getPhone();

            // cout everything or return on this information
        }
};
```

now the `NotificationService` is coupled to a `driver`,`profile`,`vehicle`,`registration`,`passenger`,`contact info` and their internal structures
```yaml
                [NotificationSrvc]
                        |
                 _____[ Ride ]_______
                |                    |
            [Driver]               [Passenger]
        [profile]   [vehicle]           [Contactinfo]
                        |
                    [registration]
```
if any connected entity changes or updates or evolves it's definition, the code breaks. 
---

### The fix ? Delefation Methods

instead od letting `NotificationService` navigate the entire object graph, we add delagation methods to `Ride`. as it already has info of `Driver` and `passenger` so its right to delegate this here.

```cpp
class Ride{
    private:
        Driver driver;
        Passenger passenger;
    
    public:
        // .... constructors and other methods
        std::string getDriverName() const {
            return driver.getProfile().getFullName();
        }

        std::string getVehiclePlate() const {
            return driver.getVehicle().getRegistration().getLicensePlate();
        }

        std::string getPassengerPhone() const {
            return passenger.getContactDtls().getPhoneNumber();
        }
};

// now Notification class becomes simple and clean
class NotificationService{
    public:
        void sendRideUpdate(const Ride& ride){
            std::string drivername = ride.getDriverName();
            std::string plate = ride.getVehiclePlate();
            std::string phone = ride.getPassengerPhone();

            // now do something with the info you have on hand
        }
};
```
Now the dependency is straightforward
```yaml
[NotificationService] -> [Ride]
```