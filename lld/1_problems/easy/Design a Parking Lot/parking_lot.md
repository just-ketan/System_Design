# DESIGN A PARKING LOT

a generic parking lot is a system surrounding resource constraint, we have limited space, and each object, may it be car, bike or something else, will occupy some space, and we can only fit soo many vehicles.

## Clarifying requirements
```
Q. What types of vehicles should the parking lot support ?
=> lets support motorcycles, cars and trucks

F. okay, should different vehicles types require different parking spot types?
=> yes, motorcycles can use motorcycle spots, cars can use cars' and so the truck. a large vehicle should'nt occupy smaller spot.
```

```
Q. can parking lot have multiple floors ?
=> yes, parking lot can have multiple floors and each floor can have different types of parking spots
```

```
Q. how does a vehicle enter or leave this system, what's the entry and exit points?
=> there are dedicated entry and exit gates, when vehicle enters, it gets a parking ticket and when it leaves, the ticket is used to calulate parking fees
```

```
Q. hows parking spot assigned?
=> system should automatically find an appropriate available spot and ssign it to vehicle
F. do user choose parking spots ?
=> no system assigns it
```

```
Q. do we need to handle parking fees, and if so, are we supposed to handle multiple payment methods ?
=> yes, fees should depend on how long vehicle stayed and there should be support of cash and card payments
```

```
Q. what happens if no spots are available for that vehicle type ?
=> it should deny entry and display unavailability of slots
```

```
Q. do we need to worry about multiple vehicles entering/leaving simultaneously ?
=> yes, assume multiple gates exist and operate concurrently, so two vehicles shouldn't be assigned the same parking spot
```

## Requirement Summary
### Functional Requirements
1. parking lot has multiple floors
2. each floor has different types of parking spot for cars, bikes and trucks.
3. vehicle enter through entry gates
4. on entry, we check for suitable available spot, assign the spot, and genereate a parking ticket.
5. vehicle exit through exit gates
6. upon exit, identify the ticket, calculate parking fees based on duration, process payment, free the parking spot
7. multiple entry/exit points operate concurrently, so spot mustnt be alotted to two vehicles.

## Class Design

### `ParkingLot` class
follows singleton pattern to ensure only one instance of parking lot exists, it maintains a list of levles and provies methods to park and unpark vehicles

### `Level` class
represents a level in parking lot and contains a list of parking spots, it handles parking and unparking of vehicles within levels.

### `ParkingSpot` class
represetns an individual parking spot and tracks the availability and the parked vehicle

### `Vehicle` class
is abstract class that determines behavior of vehicles, car truck and bikes extend this and defines their own behaviors.

### `VehicleType` enum
defines the list of allowed vehicle types, that can enter and have a spot in parking lot

```
multi-threading is achieved through use of synchronization primitives on critical sections to ensure thread safety
```