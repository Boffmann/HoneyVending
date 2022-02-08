#include <gtest/gtest.h>

#include "Data/Shelf.h"

double shelf_price = 5.0;

TEST(ShelfTests, TestOpenCostsMoney) {
    Shelf shelf(SHELF_1, 5.0);

    double debit = 6.0;

    shelf.open(debit);

    EXPECT_EQ(1.0, debit);
}

TEST(ShelfTests, TestEquals) {
    Shelf shelf1(SHELF_1, 5.0);
    Shelf shelf1_1(SHELF_1, 5.0);
    Shelf shelf2(SHELF_2, 5.0);

    EXPECT_EQ(true, shelf1 == shelf1_1);
    EXPECT_EQ(false, shelf1 == shelf2);
}

TEST(ShelfTests, TestSetOpenFor) {
    double open_debit = 5.0;
    Shelf shelf(SHELF_1, 5.0);

    EXPECT_EQ(0, shelf.get_is_open_time());

    shelf.open(open_debit);

    EXPECT_EQ(0, shelf.get_is_open_time());

    shelf.add_is_open_for(3);

    EXPECT_EQ(3, shelf.get_is_open_time());

    shelf.close();

    EXPECT_EQ(0, shelf.get_is_open_time());
}

TEST(ShelfTests, TestCannotOpenWhenEmptyOrOpen) {
    double open_debit = 15.0;
    Shelf shelf1(SHELF_1, 5.0);

    bool open_successful = shelf1.open(open_debit);
    EXPECT_EQ(true, open_successful);

    open_successful = shelf1.open(open_debit);
    EXPECT_EQ(false, open_successful);

    shelf1.close();

    open_successful = shelf1.open(open_debit);
    EXPECT_EQ(false, open_successful);

}

TEST(ShelfTests, TestCannotOpenWhenNotEnoughMoney) {
    double open_debit = 4.0;
    Shelf shelf1(SHELF_1, 5.0);

    bool open_successful = shelf1.open(open_debit);
    EXPECT_EQ(false, open_successful);

}