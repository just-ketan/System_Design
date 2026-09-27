
# building blocks of OOPS

## Class: a blueprint for creating objects. it defines the data that an object stores and the behaviors/actions it performs
```cpp
class User{
    std::string name;
    std::string email;

    void login(){
        std::cout<<name<<" logged in"<< std::endl;
    }
};
```
---

## Object: instace of a class, the actual thing created from the class blueprint

```cpp
User u1;
u1.name = "user 1";
u1.email = "u1@email.com"

User u2;
u2.name = "user 2";
u2.email = "u2.email.com"

u1.login();
u2.login();
```
both `user 1` and `user 2` are objects of same definition/blueprint `User` class. they have same structure and behavior but store different data.
---

## Constructor: sets the fields defined in the structure class, and/or initiallises and brings system to a known default state.
```cpp
class User{
    public:
    std::string name;
    std::string email;
    // constructor
    User(std::string name, std::string email){
        this->name = name;
        this->email = email;
    }
    bool login(){
        // some login behavior
        return true;
    }
};

User u1("Alice", "a.b@com");
User u2("Bob", "b.c@com");
```
constructors helps to ensure that object starts from `valid and known state`, we can further add validations to constructor to ensure we are not creating objects that invaldiate the contract.
```cpp
User(std::string name, std::string email){
    if(email.find("@") == std::string::npos)    return throw std::invalid_argument("invalid email");
    // normal processing
}
```
---

## Enum: attainable value by an object's structural element is limited or fixed to a set of options. usually used to track the state transitions
```cpp
enum class OrderStatus{
    PENDING,
    SHIPPED,
    CANCELLED,
    FULFILLED
};
OrderStatus status = OrderStatus::PENDING;
// lets say the order gets shipped at later point of time
status = OrderStatus::SHIPPED;
```

## Access Modifiers: controls when a class, field, constructor or method can be accessed
```cpp
class UserAccount{
    private:
        std::string password;
        std::string username;

        // private constructor controls object creation -> Singleton class feature
        UserAccount(std::string uname, std::string pass){
            this->username = uname;
            this->password = pass;
        }
    
    public:
        // user can login via public implementation
        bool login(std::string uname, std::string pass){
            return this->password == pass;
        }
    
    protected:
        // child class could reuse or customize it
        void log(){
            std::cout<<"Account updated"<<std::endl;
        }
};
```
---

