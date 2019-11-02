// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "../include/SharedPtr.h"

TEST(SharedPtr_Test,Value_Test)
{
    int* int_value_ptr=new int{5};
    SharedPtr<int>ptr1(int_value_ptr);
    EXPECT_EQ(*ptr1.get(),5);
    EXPECT_EQ(ptr1.get(),int_value_ptr);
}

TEST(SharedPtr_Test, Swap_Test)
{
    int* int_value_ptr=new int{5};
    int* int_value2_ptr=new int{13};

    SharedPtr<int>ptr1(int_value_ptr);
    SharedPtr<int>ptr2(int_value2_ptr);
    ptr2.swap(ptr1);
    EXPECT_EQ(*ptr2.get(),5);
    EXPECT_EQ(*ptr1.get(),13);
}

TEST(SharedPtr_Test,ResetTest)
{
    int* int_value_ptr=new int{5};

    SharedPtr<int>ptr1(int_value_ptr);

    ptr1.reset(int_value_ptr);
    EXPECT_EQ(ptr1.get(),int_value_ptr);

    ptr1.reset();
    EXPECT_EQ(ptr1.get(),nullptr);
}
