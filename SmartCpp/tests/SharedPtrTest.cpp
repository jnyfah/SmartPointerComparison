#include <gtest/gtest.h>
#include "../src/SharedPtr.cpp"

// Test case for default constructor
TEST(SharedPtrTest, DefaultConstructor) {
    SharedPtr<int> ptr;
    EXPECT_FALSE(ptr);
}

// Test case for constructor with pointer
TEST(SharedPtrTest, ConstructorWithPointer) {
    int* num = new int(42);
    SharedPtr<int> ptr(num);
    EXPECT_EQ(*ptr, 42);
    EXPECT_EQ(ptr.use_count(), 1);
}

// Test case for copy constructor
TEST(SharedPtrTest, CopyConstructor) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(ptr1);
    EXPECT_EQ(*ptr2, 42);
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}

// Test case for move constructor
TEST(SharedPtrTest, MoveConstructor) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(*ptr2, 42);
    EXPECT_EQ(ptr1.use_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 1);
}

// Test case for copy assignment operator
TEST(SharedPtrTest, CopyAssignmentOperator) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(new int(0));
    ptr2 = ptr1;
    EXPECT_EQ(*ptr2, 42);
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}

// Test case for move assignment operator
TEST(SharedPtrTest, MoveAssignmentOperator) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(new int(0));
    ptr2 = std::move(ptr1);
    EXPECT_EQ(*ptr2, 42);
    EXPECT_EQ(ptr1.use_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 1);
}

// Test case for getter functions
TEST(SharedPtrTest, GetterFunctions) {
    SharedPtr<int> ptr(new int(42));
    EXPECT_EQ(*ptr, 42);
    EXPECT_EQ(ptr.use_count(), 1);
    EXPECT_EQ(ptr.get(), &(*ptr));
}

// Test case for explicit operator bool
TEST(SharedPtrTest, ExplicitOperatorBool) {
    SharedPtr<int> ptr;
    EXPECT_FALSE(ptr);
    ptr.reset(new int(42));
    EXPECT_TRUE(ptr);
}

// Test case for use_count function
TEST(SharedPtrTest, UseCountFunction) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(ptr1);
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}

// Test case for swap function
TEST(SharedPtrTest, SwapFunction) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(new int(0));
    ptr1.swap(ptr2);
    EXPECT_EQ(*ptr1, 0);
    EXPECT_EQ(*ptr2, 42);
}

// Test case for reset function
TEST(SharedPtrTest, ResetFunction) {
    SharedPtr<int> ptr(new int(42));
    ptr.reset();
    EXPECT_FALSE(ptr);
    EXPECT_EQ(ptr.use_count(), 0);
    int* num = new int(0);
    ptr.reset(num);
    EXPECT_EQ(*ptr, 0);
}
