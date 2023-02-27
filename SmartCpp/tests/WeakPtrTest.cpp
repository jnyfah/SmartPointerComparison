#include <gtest/gtest.h>
#include "../src/WeakPtr.cpp"
#include "../src/SharedPtr.cpp"


class TestObject {
public:
    int value;
};

TEST(WeakPtrTest, Constructor) {
    TestObject* obj = new TestObject();
    SharedPtr<TestObject> SharedPtr(obj);
    WeakPtr<TestObject> weak_ptr(SharedPtr);

    EXPECT_EQ(weak_ptr.use_count(), 1);
}

TEST(WeakPtrTest, CopyConstructor) {
    TestObject* obj = new TestObject();
    SharedPtr<TestObject> SharedPtr(obj);
    WeakPtr<TestObject> weak_ptr(SharedPtr);
    WeakPtr<TestObject> weak_ptr_copy(weak_ptr);

    EXPECT_EQ(weak_ptr.use_count(), 1);
    EXPECT_EQ(weak_ptr_copy.use_count(), 1);
}

TEST(WeakPtrTest, MoveConstructor) {
    TestObject* obj = new TestObject();
    SharedPtr<TestObject> SharedPtr(obj);
    WeakPtr<TestObject> weak_ptr(SharedPtr);
    WeakPtr<TestObject> weak_ptr_moved(std::move(weak_ptr));

    EXPECT_EQ(weak_ptr.use_count(), 0);
    EXPECT_EQ(weak_ptr_moved.use_count(), 1);
}

TEST(WeakPtrTest, CopyAssignment) {
    TestObject* obj1 = new TestObject();
    TestObject* obj2 = new TestObject();
    SharedPtr<TestObject> SharedPtr1(obj1);
    SharedPtr<TestObject> SharedPtr2(obj2);
    WeakPtr<TestObject> weak_ptr(SharedPtr1);
    WeakPtr<TestObject> weak_ptr_copy(SharedPtr2);
    weak_ptr_copy = weak_ptr;

    EXPECT_EQ(weak_ptr.use_count(), 1);
    EXPECT_EQ(weak_ptr_copy.use_count(), 1);
}

TEST(WeakPtrTest, MoveAssignment) {
    TestObject* obj1 = new TestObject();
    TestObject* obj2 = new TestObject();
    SharedPtr<TestObject> SharedPtr1(obj1);
    SharedPtr<TestObject> SharedPtr2(obj2);
    WeakPtr<TestObject> weak_ptr(SharedPtr1);
    WeakPtr<TestObject> weak_ptr_copy(SharedPtr2);
    weak_ptr_copy = std::move(weak_ptr);

    EXPECT_EQ(weak_ptr.use_count(), 0);
    EXPECT_EQ(weak_ptr_copy.use_count(), 1);
}

TEST(WeakPtrTest, Expired) {
    TestObject* obj = new TestObject();
    SharedPtr<TestObject> SharedPtr(obj);
    WeakPtr<TestObject> weak_ptr(SharedPtr);

    EXPECT_FALSE(weak_ptr.expired());

    SharedPtr.reset();

    EXPECT_EQ(weak_ptr.use_count(), 1);
}


TEST(WeakPtrTest, UseCount) {
    TestObject* obj = new TestObject();
    SharedPtr<TestObject> SharedPtr(obj);
    WeakPtr<TestObject> weak_ptr(SharedPtr);

    EXPECT_EQ(weak_ptr.use_count(), 1);

    SharedPtr.reset();

    EXPECT_NE(weak_ptr.use_count(), 0);
}

