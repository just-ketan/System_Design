# DIP : Dependency Inversion Principle

sometimes the system are soo coupled with modules that changing a business requirement alters a huge chunk of the class. consider `EmailService` , we have simple request to send `GmailClien` an email

```cpp
class GmailClient{
    public:
        void sendGmail(const string& toAddr, const string& subject, const string& body){
            // gmail sending logic
        }
};

// now EmailSrvc can use this instance to send Gmail maiks
class EmailSrvc{
    private:
        GmailClient gc;
    
    public:
        void sendWelcomeMail(const string& to, const string& sub, const string& body) {
            gc.sendGmail(to, sub, "Thanks for signing up");
        }
        void sendPasswdResetEmail(const string& to, const string& sub, const string& body){
            gc.sendGmail(to, "reset passwd", "please click link to reset");
        }
};
```
now, the EmailSrvc is tightly coupled with `GmailClient` and its methods, if we introduce `OutlookClient` later, we need to restructure both `EmailSrvc` as well as methods.

## DIP : high level modules should not depend on low level modules, both should depend on abstractions. AND, abstraction should not depend on details, details should depend on abstractions.

a good structure would be to have 
```
[EmailSrvc] -> [EmailClientInterface]   -> [GmailClientImplementation]
                        |________________> [OutlookClientImplementation]
```

```cpp
class EmailClient{
    // abstract class to define the behvior of EmailClient Class
    public:
        virtual void sendmail(const string& to, const string& sub, const string& body) = 0;
        virtual ~EmailClient() = default;
};

// GMail implementation
class GmailClient : public EmailClient{
    public:
        void sendmail(const string& to, const string& sub, const string& body) override {
            // gmail client API handshake code
        }
};

// OutlookMail implementation
class OutlookClient : public EmailClient {
    public:
        void sendmail(const string& to, const string& sub, const string& body) override {
            // outlook client API handshake code
        }
};

// now the high level class interacts with these implementations
class EmailService{
    private:
        shared_ptr<EmailClient> emailclient;
    public:
        EmailService(shared_ptr<EmailClient> client) : emailclient(move(client)) {}
        void sendWelcomeEmail(const string& to, const string& sub, const string& body){
            emailclient->sendmail(to, "welcome", "Hi, welcome to this universe");
        }
        void sendPasswdResetMail(const string& to, const string& sub, const string& body){
            emailclient->sendmail(to, "reset passwd", "Hi, find link to reset passwd");
        }
};

// now we can use it in application code
int main(){
    cout<<"-----using GMAIL -------"<<endl;
    shared_ptr<EmailClient> gmail = make_shared<GmailClient>();
    EmailService gmailSrvc(gmail);
    gmailSrvc.sendmail("a@b.com");

    cout<<"----using outlook -------"<<endl;
    shared_ptr<EmailClient> outlook = make_shared<OutlookClient>();
    EmailSrvc outlookSrvc(outlook);
    outlookSrvc.sendmail("a@b.com");

    return 0;
}

```