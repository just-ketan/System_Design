# 4 Pillars of OOPS

## Encapsulation :  keeping data and methods that operate on that data together inside a class, while controlling how the data can be accessed or modified from outside.
```cpp
class BankAccount{
    private:
        double balance = 0;
    
    public:
        void deposit(double balance){
            if(amount<=0){
                throw std::invalid_argument("deposit cant be negative");
            }
            balance += amount;
        }
        void withdraw(double amount){
            if(amount>balance){
                throw std::invalid_argument("overdrafting not allowed");
            }
            deposit -= amount;
        }
        bool isOverdrawn(){
            return balance < 0;
        }
};
```
now balance cannot be changed directly, it can only be modified through `deposit` and `withdrawn` behaviors. this protects objects from onvalid states and keeps the logic for managing class resources in one place.
---

## Abstraction: hides the internal complexity of operations and exposes simplified API's that end user can consume.
```cpp
class VideoPlayer{
    public:
        void play(std::string fname){
            connect(fname);
            buffer();
            decodeFrames();
            render();
        }
    private:
        // these defines the internal behavior of method "play"
        void connect(std::string fname);
        void vuffer();
        void decodeFrames();
        void render();
};
VideoPlayer player;
player.play("movie.mp4");
```
caller only knows what `play` is used for, it consumes it for playing movies/mp4 files, without knowing exactly how the internal working fo that API is designed.

## Inheritance: allows one class to inherit data and behavior of another class. represents "is-a" relationship, commonly coined as "tight-coupling".
```cpp
class Notification{
    protected:
        std::string recipients;
    
    public:
        Notification(std::string recipient){
            this->recipient = recipient;
        }
        virtual void send(std::string msg){
            std::cout<<"sending notifs to "<<recipient<<std::endl;
        }
        void log(std::string msg){
            std::cout<<"Sent: "<<msg<<std::endl;
        }

        virtual ~Notification() = default;
};
```
now we have a Notification class that sends a message and logs it. we can extend this class and add additional behaviors on top of it
```cpp
class EmailNotification : Notification{
    public: 
        EmailNotification(std::string recipient) : Notification(recipient) {}
        void send(std::string msg) override {
            std::cout<<"Sending email to "<<recipient<<":"<<message<<std::endl;
        }
};

class SMSNotification : Notification {
    public:
        SMSNotification(std::string recipient) : Notification(recipient) {}
        void send(std::string msg) override {
            std::cout<<"Sending SMS to "<<recipient<<":"<<msg<<std::endl;
        }
};
```
now `SMS` and `Email` both define additional behaviors on top of base class behavior of `Notification`. this is done by `Method Overloading` this causes runtime polymorphism. this allows new behavior to be defined for exsiting methods.
---

## Polymorphism : allows different types to be used through the same interface. the call behvaes differently depending on the actual object being used.

```cpp
// lets extend the above Notification class
Notification* email = new EmailNotification("a@b.com");
Notification* sms = new SMSNotification("123456789");

email->send("email aaya hai");
sms->send("sms aaya hai");
```
now both are of type `Notification` but calling the same method from their own `constructors` causes the `send()` methods to work differently when called from respective variables.
```cpp
//we can also process in bulks
std::vector<Notification*> notifs = {
    new EmailNotification("email@a.com"),
    new SMSNotification("9861235876")
};
for(Notification* notif : notifs){
    notif->send("a common message across all platforms");
}
```
The language runtime chooses the correct method based on the actual object, this enables `runtime polymorphism`. allows high level code to work with a common abstraction w/o knowing implementation specific details.