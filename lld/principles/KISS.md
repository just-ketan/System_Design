# KISS - KEEP IT SIMPLE STUPID
KISS means writing code that is `easy to read`, `easy to understand` and `easy to change`.

## consider a calculator
now suppose we expose an interface for operations and this can be extended to implement the respective operations on the calculator object.
```cpp
class Operation{
    public:
        virtual double calculate(double a, double b) const = 0;
        virtual ~Operation() = default;
};

class Addition : public Operation{
    public:
        double calculate(double a, double b) const override {
            return a+b;
        }
};

class Subtraction : public Operation{
    public:
        double calculate(double a, double b) const override {
            return a-b;
        }
};

class Multiplication : public Operation{
    public:
        double calculate(double a, double b) const override {
            return a*b;
        }
};

class Division : public Operation {
    public:
        double calculate(double a, double b) const override {
            if(b==0)    throw std::invalid_argument("Division by zero");
            return a/b;
        }
};

// now our actual calculator class
class Calculator{
    public:
        // dependency injection from operation class to calculator
        double execute(const Opertaion& op, double a, double b) const {
            return op.calculate(a,b);
        }
};
```
now this is a very heavily engineered, future ready code, but its an overkill, the runtime complexity associated with runtime polymorphism is totally not worth for a 4 way actionable unit. a simpler code would be
```cpp
class Calculator{
    public:
        double calculate(const string& op, double a, double b) const {
            if(op == "+")   return a+b;
            else if(op == "-")  return a-b;
            else if(op == "*")  return a*b;
            else if(op == "/"){
                if(b == 0)  throw std::invalid_argument("Division by zero");
                else    return a/b;
            }else{
                throw std::invalid_argument("unknown operation");
            }
        }
};

```