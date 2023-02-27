#ifndef UNIQUEPTR_CPP
#define UNIQUEPTR_CPP

template<typename T>
class UniquePtr {

public:

    // Constructor
    UniquePtr(T* ptr = nullptr) : ptr_(ptr) {}

    // destructor 
    ~UniquePtr() { delete ptr_; }

    // explicitly deletes the copy constructor as uniqueptr is not copyable
    UniquePtr(const UniquePtr&) = delete;

    // explicitly deletes the copy assignment operator
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor
    UniquePtr(UniquePtr&& other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    
    // move assignment operator
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // dereferences the raw pointer
    T& operator*() const { return *ptr_; }

    // provides access to the members of the object
    T* operator->() const { return ptr_; }

    // returns a pointer to the managed object
    T* get() const { return ptr_; }

    // replaces the object owned by the UniquePtr with another object pointed to by the 
    // provided raw pointer ptr, or with a null pointer if no pointer is provided.
    void reset(T* ptr = nullptr) {
        delete ptr_;
        ptr_ = ptr;
    }

    
    T* release() {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    operator bool() const {
        return ptr_ != nullptr;
    }

    void swap(UniquePtr& other) noexcept {
        T* temp = ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = temp;
    }


    
    
private:
    T* ptr_;


};


#endif

