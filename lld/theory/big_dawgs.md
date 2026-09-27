## interface: access modifierws control visibility within a class, interface defines behavior that different classes can provide on their own way.

interface defines a contracct, it tells us what a class must do without deciding exactly how it should do. the extending implmentation has to define and implement the logic.

```cpp

class FileStorage{
    public:
        // virtual = 0; makes this class abstract, gives the contract
        // the implemntation must define the behavior
        virtual void save(std::string fname, std::vector<char> data) = 0;
        virtual ~FileStorage() = default;
};
```
now we know FileStorage class have a behavior of "save", we must implement it separately for all types
```cpp
class CloudStorage : public FileStorage{
    public:
        void save(std::string fname, std::vector<char> data) override {
            std::cout<<"saving "<<fname<<" to cloud"<<std::endl;
        };
};

class FlashStorage : public FileStorage{
    public:
        void save(std::string fname, std::vector<char> data) override {
            std::cout<<"saving "<<fname<<"to local flash storage"<<std::endl;
        }
};
```

the rest of the application can use this interface instead of specific storage system
```cpp
class BackupService{
    private:
        FileStorage* storage;

    public:
        BackupService(FileStorage* fs){
            this->storage = fs;
        }

        void backup(std::string fname, std::vector<char> data){
            storage->save(fname, data);
        }
}
```
now `BackupService` can work with any implementation of `FileStorage`, or any future implementation as well.

## Abstract Class: we need common state to be shared across classes. Abstract cannot be instantiated directly, provides shared fields and behavior while leaving some behavior for child to implement.
```cpp
class ReportGenerator{
    public:
        void generate(std::vector<std::string> data){
            std::string content = format(data);
            save(content);
        }
        void save(std::string content){
            std::cout<<"Saving report: "<<content<<std::endl;
        }
        virtual std::string format(std::vector<std::string> data) = 0;  // making abstract
        virtual ~ReportGenerator() = default;
};
```
now `ReportGenerator` class has handed out the `generate` and `save` behavior, these two behaviors stay common across child classes. but we have an abstract exposing an interface for additional behavior that the child classes can indulge in defining.
```cpp
class CSVFormatter : public ReportGenerator{
    public: 
        std::string format(std::vector<std::string> data) override {
            std::string res;
            for(size_t i=0; i<data.size(); i++){
                if(i>0) res += ",";
                res+=data[i];
            }
            return res;
        }
};

class JSONFormatter : public ReportGenerator{
    public:
        std::string format(std::vector<std::string> data) override {
            std::string res="[";
            for(size_t i=0; i<data.size(); i++){
                if(i>0) res+=",";
                res+="\"+data[i]+"\"";
            }
            return res+"]";
        }
};
```
now `CSVFormatter` and `JSONFormatter` both expose their own overridden behaviors for formatting the text.