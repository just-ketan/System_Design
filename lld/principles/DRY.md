# DRY : DONT REPEAT YOURSELF
the core idea is that "every piece of knowledge must have a `single`, `unambiguous`, `authoritative` representation within a system.
---
DRY tells that piece of knowledge in the system should live in exactly one place, when we need it, we reference that single source, instead of creating several copies.
```yaml
1. Business Logic: rules should be defines once and then modified wrt reference wherever needed

2. Configurations: databse connections, API keys, etc config values should be in one config files rather than inplace definitions thorughout code base

3. Data Models : if user has name and email, that structure should be defines once and not redefined every other modeule that touces User.
```

wherever the same concept appears in more than one place, we might eventually introduce `redundancy`, follow rule of three, and if you see a lgoci getting duplicate definitions more than 2 times, then extracting from a single location is the right call.

```cpp
// In AuthService.cpp
bool isValidEmail(const std::string& email) {
    return !email.empty() && email.find('@') != std::string::npos
        && email.find('.') != std::string::npos;
}

// In PaymentService.cpp
bool isValidEmail(const std::string& email) {
    return !email.empty() && email.find('@') != std::string::npos
        && email.find('.') != std::string::npos;
}

// In MessagingService.cpp
bool isValidEmail(const std::string& email) {
    return !email.empty() && email.find('@') != std::string::npos
        && email.find('.') != std::string::npos;
}
```
The above is poor design, cause we are validating the similar business logic across multiple code sections, applying DRY would make it-
```cpp
class EmailValidator{
    public:
        static bool isValid(const string& email){
            if(email.empty())   return false;
            bool hasdot = email.find(".") != string::npos;
            bool hasat = email.find("@") != string::npos;
            bool validending = email.size() >= 4 && (email.substr(email.size()-4) == ".com" || email.substr(email.size()-4) == ".org");
            return hasat & hasdot & validending;
        }
};

// then use it across translation units

// In AuthService.cpp
if (EmailValidator::isValid(user.getEmail())) {
    // Proceed with authentication
}

// In PaymentService.cpp
if (EmailValidator::isValid(customer.getEmail())) {
    // Proceed with payment processing
}

// In MessagingService.cpp
if (EmailValidator::isValid(recipient.getEmail())) {
    // Proceed with sending message
}
```

### Notification system : we have `order service`, `shipping service` and `support service`, all need to send notificaiton to users.

using DRY would look like-
```cpp
// this class defines how to format a message
class MessageFormatter{
    public:
        static string format(const string& category, const string& userid, const string& detail){
            string msg = "["+category+"] Hi "+userid+" , "+detail;
            msg[0] = roupper(msg[0]);
            return msg;
};

class NotificationSender{
    public:
        static void send(const sttring& userid, const string& msg){
            cout<<"Connecting to notification API..."<<endl;
            cout<<"sending to "<<userid<<":"<<msg<<endl;
            cout<<"Notification sent successfully"<<endl;
        }
};

class OrderService{
    public:
        void notifyOrderConfirmation(const string& userid, const string& orderid){
            string msg = MessageFormatter::format("ORDER", userid, "your order "+orderid+" has been confirmed.");
            NotificationSender::send(userid, msg);
        }
};

class ShippingService{
    public:
        void notifyShipmentUpdate(const string& userid, const string& trackingid){
            string msg = MessageFormatter::format("SHIPPING", userid, "your shipment "+trackingid+" is on its way.");
            NotificationSender::send(userid, msg);
        }
};

class SupportService{
    public:
        void notifySupportService(const string& userid, const string& ticketid){
            string msg = MessageFormatter::format("SUPPORT",userid,"your ticker "+ticketid+" has been resolved.");
            NotificationSender::send(userid, msg);
        }
};
```

This creates a clean single source of invocation, where we parametrise the message based on our business requirements.