# LSP : Liskov Substitution Principle

consider a situtation, `DOCUMENT SYSTEM GONE WRONG`, we are building a system to manage different types of documents. lets start with simple base case

```cpp
class Document{
    protected:
        string data;

    public:
        Document(const string& data) : data(data) {}
        virtual void open() const {
            cout<<"Document Opened. data: "<<data.substr(0,min((size_t)20, data.length()))<<"..."<<endl;
        }   // print chunks of 20 chars in one go
        virtual void save(const string& newdata){
            data = newdata;
            cout<<"document saved"<<endl;
        }
        string getdata() const {
            return data;
        }
        virtual ~Document() = default;
};
```
and then, we get a new requirement: "we need read-only document type for sensitive content like govt reports or signed contracts". Now if we extend document, we would expose `save()` as well, that is totally against the contract. we can override it so that `save()` is rendered useless, but will it be ok ?

```cpp
class ReadOnlyDocument : public Document {
    public save(const string& \*newdata*\) override {
        throw runtime_error("cannot save RO document");
    }
};
```

Now comes the biggest `tunnelvision`, `Document` says that any and all document should have the said behaviors, `open()`, `save()` and `getdata()`. but, as soon as we extend Document to create `ReadOnlyDocument` we give away one of the behaviors of thie base class Document : `save()` as it throws runtime exception. lets see

```cpp
class DocumentProcessor{
    public:
        void processAndSave(Document* doc, const string& additionalInfo){
            doc->open();
            string curr = doc->getdata();
            string neww = curr + "| processed: " + additionalInfo;
            doc->dave(neww);
            cout<<"Document processing complete."<<endl;
        }
};

int main(){
    Document* regular = new Document("Intial project proposal");
    Document* confidential = new ReadOnlyDocument("confidential");

    DocumentProcess processor;
    cout<<"--------regular document------"<<endl;
    processor.processAndSave(regular, "reviewed by alice");

    cout<<"--------confidential--------"<<endl;
    try{
        processor.processAndSave(confidential, "reviewed by alexa");
    } catch (const exception& e){
        cerr<<"Error: "<<e.what()<<endl();
    }

    delete regular;
    delete confidential;

    return 0;
}
```
the client side code expected any `Document` to be savable, but when it recieved `ReadOnlyDocument`, it exploded as the `Document` contract got violated.

```
LSP says "if class `S` extends or implements class `T`, then you should be able to inhibit behaviors of `S` anywhere `T` is expected, without breaking program's logic or behavior. THIS ENABLES TRUE POLYMORPHISM"
```

## The LSP Solution:

the issue was Base Class `Document` assumed all documents are editable, but not all should be.
```cpp
// step 1 : define behavioral interfaces
class Document{
    public:
        // the virtual function make this class abstract, and thus behavior must be defines outside this class
        virtual void open() const = 0;
        virtual string getdata() const = 0;
        virtual ~Document() = default;
};

class Editable : public Document() {
    public: 
        // the editable classs extends Document, but adds a new behavior of modifying the data
        virtual void save(const string& newdata) = 0;
};

// EditableDocument extends the Editable behavior
class EditableDocument : public Editable{
private:
    string datal
    string preview() const {
        return data.substr(0, min((size_t)20, data.length()))+"....";
    }

public:
        EditableDocument(const string& data) : data(data) {} 
        void open() const override{
            cout<<"Editable document opened"<<endl;
        }
        void save(const string& newdata) override {
            data = newdata;
            cout<<"Document saved"<<endl;
        }
        string getdata() const override {
            return data;
        }
};

// ReadOnlyDocument extends the Base Document behavior
class ReadOnlyDocument : public Document{
    private:
        string data;
        string preview() const {
            return data.substr(0, min((size_t)20, data.length()))+"...";
        }
    public:
        ReadOnlyDocument(const string& data) : data(data) {}
        void open() const override {
            cout<<"Opened Read-Only Document"<<preview()<<endl;
        }
        string getdata() const override {
            return data;
        }
};
```
```
Editable extends Document to add editable behavior
then this Editable interface is consumed by Editable document
ReadOnly extends the base class behavior
```

thus the DocumentProcessor translates to
```cpp
class DocumentProcessor{
    public:
        void process(const Document* doc) cosnt {
            doc->open();
            cout<<"Document processed"<<endl;
        }

        void processAndSave(Editable& doc, const string& info){
            doc.open();
            string curr = doc->getdata();
            string newdata = curr + " | Processed: "+info;
            doc.save(newdata);
            cout<<"Editable document processed and save."<<endl;
        }
};

int main() {
    EditableDocument editable("Draft proposal for Q3.");
    ReadOnlyDocument readOnly("Top secret strategy.");
    DocumentProcessor processor;

    cout << "--- Processing Editable Document ---" << endl;
    processor.processAndSave(editable, "Reviewed by Alice");

    cout << "\n--- Processing Read-Only Document ---" << endl;
    processor.process(&readOnly); // Works fine

    // processor.processAndSave(readOnly, "Reviewed by Bob");
    // Won't compile! ReadOnlyDocument doesn't have save().

    return 0;
}
```

