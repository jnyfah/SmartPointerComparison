#include <memory>
#include "gtest/gtest.h"
#include "../src/UniquePtr.cpp"

TEST(UniquePtrTest, Constructor) {
  UniquePtr<int> ptr1;
  EXPECT_EQ(ptr1.get(), nullptr);

  int* ptr2 = new int(42);
  UniquePtr<int> ptr3(ptr2);
  EXPECT_EQ(ptr3.get(), ptr2);
}

TEST(UniquePtrTest, MoveConstructor) {
  UniquePtr<int> ptr1(new int(42));
  UniquePtr<int> ptr2(std::move(ptr1));
  EXPECT_EQ(ptr1.get(), nullptr);
  EXPECT_EQ(*ptr2, 42);
}

TEST(UniquePtrTest, MoveAssignment) {
  UniquePtr<int> ptr1(new int(42));
  UniquePtr<int> ptr2;
  ptr2 = std::move(ptr1);
  EXPECT_EQ(ptr1.get(), nullptr);
  EXPECT_EQ(*ptr2, 42);
}

TEST(UniquePtrTest, OperatorDereference) {
  UniquePtr<int> ptr(new int(42));
  EXPECT_EQ(*ptr, 42);
}

TEST(UniquePtrTest, OperatorArrow) {
  struct Foo {
    int x;
    int y;
  };
  UniquePtr<Foo> ptr(new Foo{1, 2});
  EXPECT_EQ(ptr->x, 1);
  EXPECT_EQ(ptr->y, 2);
}

TEST(UniquePtrTest, Get) {
  UniquePtr<int> ptr(new int(42));
  EXPECT_EQ(ptr.get(), ptr.get());
}

TEST(UniquePtrTest, Reset) {
  UniquePtr<int> ptr(new int(42));
  ptr.reset(new int(43));
  EXPECT_EQ(*ptr, 43);
  ptr.reset();
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTest, Release) {
  UniquePtr<int> ptr(new int(42));
  int* raw_ptr = ptr.release();
  EXPECT_EQ(*raw_ptr, 42);
  EXPECT_EQ(ptr.get(), nullptr);
}


TEST(UniquePtrTest, OperatorBool) {
  UniquePtr<int> ptr;
  EXPECT_FALSE(ptr);
  ptr.reset(new int(42));
  EXPECT_TRUE(ptr);
}

TEST(UniquePtrTest, Swap) {
  UniquePtr<int> ptr1(new int(42));
  UniquePtr<int> ptr2(new int(43));
  ptr1.swap(ptr2);
  EXPECT_EQ(*ptr1, 43);
  EXPECT_EQ(*ptr2, 42);
}
