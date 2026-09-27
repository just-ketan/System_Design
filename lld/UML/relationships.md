# CLASS RELATIONSHIPS

## Dependency (Weakest)
A dependency means one class temporarily uses another, typically via method parameter, local variable or return type. the dependent class doesnt sotre a reference to other class as a field, it just needs it for a specific operation
```yaml
        ______________________________                        ____________________________________
       |         OrderServc           |                      |          EmailSrvc                 |
       |______________________________| ------- uses ---->   |____________________________________|
       |______________________________|                      |____________________________________|
       |+placeOrder(order:Order)::void|                      | +sendConfirmation(to:string)::void |
       |______________________________|                      |____________________________________|
```
the dashed arrow `....>` is UML representation for `dependency`. the `OrderSrvc` class depends on `EmailSrvc` class to call `EmailSrvc.sendConfirmation()` insider the `placeOrder()` method. but `OrderService` does'nt hold `EmailService` field, it might revcieve it as parameter or create it locally or look it up from service locator. `if class A calls a method of class B, but doesnt have reference in method body, its dependency`

## Association
Association means one class knows about another and holds a referece to it as a field. models `has-a` or `uses-a` relationship where the connection is persistent.

```yaml
        ______________________________                        ____________________________________
       |         Student              |                      |          Teacher                   |
       |______________________________| ____learns from__>   |____________________________________|
       | -name:String                 |                      |  -name:String                      |
       | -teacher: Teacher            |                      |  -students:List<students>          |
       |______________________________|                      |____________________________________|
       |______________________________|                      |____________________________________|
```
solid `__>` notation is for Association, `student` holds reference to `Teacher` as a field. the multiplicity labels tells us that many students can be associated with one or more teachers. `students:List<students>` under `Teacher` class tells the above. both have their own scope of existence and can exist independently, `Teacher` and `Student` objects live without an implication from each other. `USE ASSOCIATION WHEN CLASS A STORES REFERENCE TO CLASS B AS A FIELD AND BOTH HAVE INDEPENDENT LIFECYCLES`


## Aggregation
Aggregation is a special form of association that madels a "whole-part" relationship with `weak ownership`, the whole contains the parts, but the parts can exist independently, id the lifespan of `whole` is over, the parts survive.
```yaml
        ______________________________                        _______________________
       |         Playlist             |                      |          Song         |
       |______________________________|     <>contains---    |_______________________|
       | -name:String                 |                      | -title: String        |
       | -songs:List<Song>            |                      | -artist: String       |
       |______________________________|                      | -duration: int        |
       | +addSong(song:Song)::void    |                      |_______________________|
       | +removeSong(song:Song)::void |                      |_______________________|
       |______________________________|                      
```
The `hollow diamond` on the `Playlist` sied is UML notation for `aggregation`, `playlist` is `whole` while `song` is a `part`. if we delete the playlist, the songs wont cease to exist, they still exist in the music library. furthermore, a song can belong to multiple playlists. `USE AGGREGATION WHEN A CLASS CONTAINS OBJECT OF OTHER CLASS BUT THE CONTAINED OBJECT HAVE THEIR OWN INDEPENDENT LIFECYCLE AND CAN BE SHARED ACROSS MULTIPLE CONTAINERS`

## COMPOSITION
composition is the stronger version of aggregation, its a "whole-part" relationship with `strong ownership`, the whole creates, amanger and destroys the parts. if the whole is destroyed, the parts go with it.
```yaml
        ___________________________________________________              _______________________
       |         Order                                     |            |          Song         |
       |___________________________________________________|<.>contains-|_______________________|
       | -orderID:String                                   |            | -Pname: String        |
       | -Items:List<Item>                                 |            | -quantt: String       |
       |___________________________________________________|            | -unitPrice: int       |
       | +addItem(name:String, qty:int, price:double)::void|            |_______________________|
       | +getTotal()::double                               |            | +getSubTotal()::double|
       |___________________________________________________|            |_______________________|
```
the `filled diamond` on `Order` side is UML representation for `COMPOSITION` it highlights whole-part assocaition with strong-ownership. now each `order` is associated with a list of `items` these `items` have no meaning outside the scope of `order`, thus once `order` lifetime terminates `items` perish as well.

## INHERITANCE

inheritance represents an "is-a" relationsip where subclass extends a superclass, inheriting its attributes and methods. the subclass can add its own fields and methods, and can override inherited behavior. `its represented with solid line and hollow triangle ending towards the superclass`
```yaml
        ________________________                   _____________________
       |        ANIMAL          |                 |       DOG           |
       |________________________|                 |_____________________|
       | #name: String          |                 | -breed:String       |
       | #age: int              |                 |_____________________|
       |________________________|_______________|>| +makeSound():string |
       | +makeSound():String    |                 | +fetch()::void      |
       | +move():String         |                 |_____________________|
       |________________________|
```
here `DOG` inherits the `name` and `age` attributes of superclass `Animal` and has additional attribute of its own as well, it them implements or overrides the `superclass methods` to have custom behavior wrt to `Dog` class.

## REALIZATION (IMPLEMENTATION OF INTERFACE)

Realization is the relationship betweeb a class an an interface it implements. the classs promises to provide concrete implementations and define the behviors mentioned in the Interface contracts. `THE DASHED LINE WITH HOLLOW TRAINGLE` is the notation in UML for ralization of an interface.
```yaml
        _______________________________________       __________________________________________
       |      <<interface>>                    |     |       AudioPlayer                        |
       |         PLAYER                        |     |__________________________________________|
       |_______________________________________|     | -type:String                             |
       |_______________________________________|     |__________________________________________|
       | +play()::void                         |---|>| +play()::void                            |
       | +seek(dir:boolean, qty:int)::boolean  |     | +seek(dir:boolean, qty:int)::boolean     |________________________________________|     |__________________________________________|
```

The strength of a class realtionship can be reallized as this -
```
[Dependency] -> [Assocation] -> [Aggregation] -> [Composition] -> [Interface] -> [Realization]
```