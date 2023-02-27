#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>


template<typename T>
class SharedPtr {
public:
    SharedPtr() : ptr_(nullptr), ref_count_(nullptr) {}
    SharedPtr(T* ptr) : ptr_(ptr), ref_count_(new size_t(1)) {}

    // Copy constructor
    SharedPtr(const SharedPtr<T>& other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        if (ref_count_) {
            ++(*ref_count_);
        }
    }

    // Move constructor
    SharedPtr(SharedPtr<T>&& other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    // Copy assignment
    SharedPtr<T>& operator=(const SharedPtr<T>& other) {
        if (this != &other) {
            if (ref_count_ && --(*ref_count_) == 0) {
                delete ptr_;
                delete ref_count_;
            }
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            if (ref_count_) {
                ++(*ref_count_);
            }
        }
        return *this;
    }

    // Move assignment
    SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
        if (this != &other) {
            if (ref_count_ && --(*ref_count_) == 0) {
                delete ptr_;
                delete ref_count_;
            }
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            other.ptr_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

    // Destructor
    ~SharedPtr() {
        if (ref_count_ && --(*ref_count_) == 0) {
            delete ptr_;
            delete ref_count_;
        }
    }

    // Getters
    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    T* get() const {
        return ptr_;
    }

    // Check if pointer is valid
    explicit operator bool() const {
        return ptr_ != nullptr;
    }

    size_t use_count() const noexcept {
    return ref_count_ ? *ref_count_ : 0;
    }

    size_t* weak_count() const noexcept {
    return ref_count_ ? ref_count_ : 0;
    }


    void swap(SharedPtr<T>& r) noexcept {
        T* temp_ptr = ptr_;
        ptr_ = r.ptr_;
        r.ptr_ = temp_ptr;

        size_t* temp_ref_count = ref_count_;
        ref_count_ = r.ref_count_;
        r.ref_count_ = temp_ref_count;
    }


    // Reset function
    void reset(T* ptr = nullptr) {
        if (ptr_ != ptr) {
            if (ref_count_ && --(*ref_count_) == 0) {
                delete ptr_;
                delete ref_count_;
            }
            ptr_ = ptr;
            ref_count_ = ptr ? new size_t(1) : nullptr;
        }
    }

private:
    T* ptr_;
    size_t* ref_count_;
};

#endif