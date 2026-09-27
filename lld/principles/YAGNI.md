# YAGNI : YOU AINT GONNA NEED IT

this principle encourages us to `resist the tempatation to build features or forsee them that you need them`. DONT BUILD FOR TOMORROW, BUILD FOR TODAY.

---
Extereme Programming(XP) one of the earliest agile methodologies, XP was aimed at notion that software requirements are bound to change, so spending time building predictive future features is a waste.

## A Problem :  Uploading user profile pictures

suppose that project involves user uploading pictures. the current implementation is simple-
    1. accept image
    2. resize to 300x300
    3. store on local FS

thus a YAGNI applied class would look like
```cpp
class ImageUploader{
    private:
        ImageResizer* resizer;
        LocalStorage* storage;
    
    public:
        ImageUploader(ImagerResizer* ir, LocalStorage* ls){
            this->resizer = ir;
            this->storage = ls;
        }

        void upload(const File& image){
            File resized = resizer->resize(imageFile, 300, 300);
            storage->save(resized);
        }
};
```
this implements `current day requirement` and is `simple and easy to read`, `can be extended later on need basis` and `has no dead code, no stubs and no speculative abstractions`.
---
a poor design however would expose interfaces and abstractions for storage serivce, resizer etc etc and would something like and overengineered piece of fluff :-

```cpp
// interface handling different media types
class IMediaHandler{
    public:
        virtual ~IMediaHandler() = default;
        virtual bool canHandle(const std::string& fileType) = 0;
        virtual File process(const File& file) = 0;
};

// interface for different storage provides
class IStorageProvider{
    public:
        virtual ~IStorageProvider() = default;
        virtual void store(const File& file, const std::string& path) = 0;
        virtual File retrieve(const std::string& path) = 0;
        virtual void remove(const std::string& path) = 0;
};

// Factory for creating media handlers
class MediaHandlerFactory{
    private:
        std::unordered_map<std::string, IMediaHandler*> handlers;
    
    public:
        void registerHandler(std::string& type, IMediaHnadler* handler){
            handlers[type] = handler;
        }

        IMediaHandler* getHandler(const std::string& fileType){
            auto it = handlers.find(fileType);
            if(it == handlers.end()){
                throw std::runtime_error("No handler for type: " + filetype);
            }
            return it->second;
        }
};

// cloud storage adapter (NOT NEEDED YET)
class CloudStorageAdapter : public IStorageProvide{
    private:
        std::string bucket;
        std::string region;

    public:
        CloudStorageAdapter(const std::string& bucketName, const std::string& region){
            this->bucket = bucketName;
            this->region = region;
        }
        void store(const File& file, const std::string& path) override {
            // not implemented, not needed
        }
        File retrieve(const std::string& path) override {
            // not implemented, not needed
        }
        void remove(const std::string& path) override {
            // not implemented not needed
        }
};

// Image Handler [the only needed artifact]
class ImageMediaHandler : public IMediaHandler {
    public:
        bool canHandle(const std::string& filetype) override {
            return filetype == "image";
        }
        File process(const File& file) override {
            return resize(file, 300,300);
        }

    private:
        File resize(const File& file, int w, int h){
            // resize implementation
            return file;
        }
};

// the bloated driver that binds it all together
class MediaProcessingEngine{
    private;
        MediaHandlerFactory* handlerFactory;
        IStorageProvider* storageProvider;

    public:
        MediaProcessingEngine(MediaHandlerFactory* handler, IStorageProvider* provider) {
            this->handlerFactory = handler;
            this->storageProvider = provider;
        }

        void upload(const File& file, const std::string& filetype, const std::string& path){
            // get the media handler
            IMediaHandler* handler = handlerFactory->getHandler(filetype);
            // resize the image
            File processed = handler->process(file);
            // store it in specified storage
            storageProvider->store(processed, path);
        }
};
```