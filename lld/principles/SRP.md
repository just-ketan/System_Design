# SRP : Single Responsibility Principle

A `God Class` is a class that tries to do everything, and in an attempt to do everything at once, it does nothing well.
```cpp
class UserService{
    private:
        string uname;
        string email;
        string password;

    public:
        UserService(const string& uname, const string& email, const string& password):uname(uname), email(email), password(password) {}

        string validateAndHashPassword(){
            // check strngth
            // generate salt
            // hash with bcrypt
        }

        void saveToDB(){
            // connect to DB
            // prepare SQL
            // execute query
        }

        string generateAuthToken(){
            // create JWT payload
            // sign with secret key
            // return token string
        }

        void sendWelcomeEmail(){
            // connect to Email Server
            // build welcome template
            // send email
        }
};
```
This looks convienient, but the four responsibilites are `tightly coupled`. we have 4 reasons to change the class definitions.

---

## Single Responsibility Principle
responsibility : reason for a class to change. "How many reasons might emerge from this definition, that causes me to change class strucutre or modify the class?", if answer is `more than one`, then we are violating `SRP`

### Consider `UserService` from above
```cpp
class UserService{
    private:
        string uname;
        string email;
        string pass;

    public:
        UserService(const string& uname, const string& email, const string& pass) : uname(uname), email(email), pass(pass) {}

        string getUsername() const  {   return username;}
        string getEmail() const     {   return email;   }
        string getPassword() const  {   return pass;    }
};
```
now this class does one job : `represent a user`

#### Responsibility 1 : Password Hashing
```cpp
class PasswordHasher{
    public:
        string ValidateAndHash(const string& pass){
            if(pass.length() < 8)   throw std::invalid_argument("size less than 8");
            // generate salt and hash with bcrypy
            return "bcrypt_hashed_"+password;
        }
};
```
if hasing algorithm changes, from bcrypt to argon2, we only need to update this class.

#### Responsibility 2 : Persistence to DB
```cpp
class UserRepository{
    public:
        void save(const User& user){
            // do db save
        }
};
```
we can swap out `JDBC for JPA`, switch from `SQL to NoSQL` or change `ORM entirely` without touching rest of system.

#### Responsibility 3 : Auth Token Generation
```cpp
class AuthTokenService{
    public:
        string generateToken(const User& user){
            // create JWT payload with user claims
            string payload = "{\"username\":\""+user.getUsername()+ "\",\"email\":\"" + user.getEmail() + "\"}";
            // sign with secret kry
            return "---some bearer token--- "+ payload + ".signature";
        }
};
```
now we can switch from JWT to opaque tokens, change signature algorithm or adjust token charachteristics without changing the rest if codebase.

#### Responsibility 4 : Sending welcome mail
```cpp
class EmailService{
    public:
        void sendWelcomeEmail(const User& user) {
            cout<<"Sending mail to: "<<user.getEmail()<<endl;
            cout<<"Welcome to out platform "<<user.getUsername()<<endl;
        }
};
```
