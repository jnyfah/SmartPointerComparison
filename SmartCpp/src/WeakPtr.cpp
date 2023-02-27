#ifndef WEAKPTR_CPP
#define WEAKPTR_CPP

#include <iostream>
#include "SharedPtr.cpp"

template<typename T>
class WeakPtr {
public:
    WeakPtr() : ptr_(nullptr), ref_count_(nullptr) {}
    WeakPtr(const SharedPtr<T>& shared_ptr) : ptr_(shared_ptr.get()), ref_count_(shared_ptr.weak_count()) {}

    // Copy constructor
    WeakPtr(const WeakPtr<T>& other) : ptr_(other.ptr_), ref_count_(nullptr) {
        if (other.ref_count_ != nullptr) {
        ref_count_ = new size_t(*other.ref_count_);
        }
    }


    // Move constructor
    WeakPtr(WeakPtr<T>&& other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    // Copy assignment
    WeakPtr<T>& operator=(const WeakPtr<T>& other) {
        if (this != &other) {
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
        }
        return *this;
    }

    // Move assignment
    WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept {
        if (this != &other) {
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            other.ptr_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

    // Destructor
    ~WeakPtr() = default;

    // Check if pointer is valid
    bool expired() const {
        return ref_count_ == nullptr || *ref_count_ == 0;
    }

    // Getters
    SharedPtr<T> lock() const {
        return expired() ? SharedPtr<T>() : SharedPtr<T>(ptr_);
    }

    size_t use_count() const noexcept {
        return ref_count_ ? *ref_count_ : 0;
    }

    void swap(WeakPtr<T>& r) noexcept {
        T* temp_ptr = ptr_;
        ptr_ = r.ptr_;
        r.ptr_ = temp_ptr;

        size_t* temp_ref_count = ref_count_;
        ref_count_ = r.ref_count_;
        r.ref_count_ = temp_ref_count;
    }

    // Reset function
    void reset() {
        ptr_ = nullptr;
        ref_count_ = nullptr;
    }

private:
    T* ptr_;
    size_t* ref_count_;
};




class MyClass {
public:
    MyClass() {
        std::cout << "MyClass created" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destroyed" << std::endl;
    }

    void print() const {
        std::cout << "Hello, world!" << std::endl;
    }
};

// int main() {
//     // Create a shared pointer to a MyClass object
//     SharedPtr<MyClass> shared_ptr(new MyClass);

//     // Create a weak pointer to the same object
//     WeakPtr<MyClass> weak_ptr(shared_ptr);

//     // Print the use count of the shared pointer and the weak pointer
//     std::cout << "Use count: " << shared_ptr.use_count() << std::endl;
//     std::cout << "Weak count: " << weak_ptr.use_count() << std::endl;

//     // Lock the weak pointer to create a new shared pointer to the same object
//     SharedPtr<MyClass> locked_ptr = weak_ptr.lock();

//     // Print the use count of the shared pointer and the weak pointer
//     std::cout << "Use count: " << shared_ptr.use_count() << std::endl;
//     std::cout << "Weak count: " << weak_ptr.use_count() << std::endl;

//     // Reset the shared pointer
//     shared_ptr.reset();

//     // Print the use count of the locked pointer and the weak pointer
//     std::cout << "Use count: " << locked_ptr.use_count() << std::endl;
//     std::cout << "Weak count: " << weak_ptr.use_count() << std::endl;

//     // Lock the weak pointer again to create another shared pointer to the same object
//     SharedPtr<MyClass> new_locked_ptr = weak_ptr.lock();

//     // Print the use count of the locked pointer and the weak pointer
//     std::cout << "Use count: " << locked_ptr.use_count() << std::endl;
//     std::cout << "Weak count: " << weak_ptr.use_count() << std::endl;

//     // Call the print function on the locked pointer to check if it still works
//     locked_ptr->print();

//     return 0;
// }


#endif