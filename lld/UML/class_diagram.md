# UNIFIED MODELLING LANGAUAGE (UML)

UML class diagram provide a static view of an object oreiented system, showcasing its classes, attributes, methods and relationship amongst objects.

## Class

a class is drawn as rectangle divied into `three compartments`, `class name at top`, `attributes in the middle` and `methods at bottom`
```yaml
            ____________________________________________
           |                                            |    
           |       CLASS NAME : BankAccount             |
           |____________________________________________|
           |  -accountNumber:string                     |    
           |  -ownerName: string                        |
           |  -balance: double                          |
           |____________________________________________|
           |  +deposit(amt:double)::void                |
           |  +withdraw(amt:double)::boolean            |
           |  +getBalance()::double                     |
           |____________________________________________|
```
the attributes are declared in the form `visiblility name: type`, so -accountNumber:String, means that `accountNumber` is a `private member` of class and is of type `string`. the `"-"` is the indicator of `private member`. the methods are declared at the very bottom of the form `visibility name(params) : retrunType`, so `+deposit(amt:double)::boolean` suggests that `deposit()` is a `public method indicated by '+'` and that accepts `amt` as paramter of type `double` and return `boolean` indicating the method outcome.
```yaml
    '+' => public   -> accessible from any class
    '-' => private  -> only accessible within same class
    '#' => protected-> accessible within same class or subclasses
    '~' => package  -> accessible within same package (wrt java)
```

## Interfaces
interface defines what a class must do, without saying how. interfaces look like a class rectangle with `<<interface>>` stereotype above the name. there are no attributes associated with interfaces, so the attributes section is usually empty
```yaml
            ____________________________________________
           |            <<interface>>                   |    
           |                Payable                     |
           |____________________________________________| 
           | +calculateAmount()::double                 |    
           | +processPayment(method:string)::boolean    |
           |____________________________________________|
```
the `<<interface>>` label is key visual signal, we know that class `Payable` exposes an interface, and the derived classes must provide their implementation of public classes `calculateAmount()` and `processPayment()`.

## Abstract Class
sits between a concrete class and an interface, there have both implemented behaviors that acts as sahred behavior and some abstract methods defined by pure virtual functions. they are marked with `<<abstract>>` stereotype and abstract method names are written in *Italic*.

```yaml
            ________________________________
           |         <<abstract>>           |    
           |             Shape              | 
           |________________________________| 
           |  #color:String                 |    -> protected variable color
           |________________________________|
           |  +*getArea()::double*          |    
           |  +*getPerimeter()::double*     |
           |  +getColor()::string           |           
           |________________________________|
```
the `color` is only visible within class and subclasses. the `getArea()` and `getPerimeter()` are abstract methods whose behvior must be defined by Implementation classes. the `getColor()` is concrete method that gives up the color specified in that `Shape` class instance. A subclass `Circle` or `Rectangle` must override abstract classes with its own logic.

## ENUMS
enumeration defines a fixed set of named constants, we use `<<enumeration>>` stereotype and values are list in attributes compartment.
```yaml
            _________________________
           |  <<enumeration>>        |    
           |    OrderStatus          | 
           |_________________________|
           |    PENDING              |
           |    CONFIRMED            |
           |    PREPARING            |
           |    SHIPPED              |
           |    DELIVERED            |
           |    CANCELLED            |
           ---------------------------
           |                         |
           --------------------------- 
```
