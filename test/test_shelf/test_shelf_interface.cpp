#include <gtest/gtest.h>

#include "Modules/ShelfsInterface.h"
#include "Hardware/TimerInterrupt.h"

#include <stdio.h>

TEST(ShelfInterfaceTests, TestBuyShelf) {
    double shelf_debit = 5.0;
    ShelfsInterface interface;

    bool bought_successfully = interface.buy_shelf(SHELF_1, shelf_debit);

    EXPECT_EQ(true, bought_successfully);
    EXPECT_EQ(0.0, shelf_debit);
}

TEST(ShelfInterfaceTests, TestCannotBuyTwice) {
    double shelf_debit = 10.0;
    ShelfsInterface interface;

    bool bought_successfully = interface.buy_shelf(SHELF_1, shelf_debit);

    EXPECT_EQ(true, bought_successfully);

    bought_successfully = interface.buy_shelf(SHELF_1, shelf_debit);
    EXPECT_EQ(false, bought_successfully);
}

TEST(ShelfInterfaceTests, TestCannotBuyWithTooLessMoney) {
    double shelf_debit = 4.0;
    ShelfsInterface interface;

    bool bought_successfully = interface.buy_shelf(SHELF_2, shelf_debit);

    EXPECT_EQ(false, bought_successfully);
}

TEST(ShelfInterfaceTests, TestCannotBuyNotAdded) {
    double shelf_debit = 5.0;
    ShelfsInterface interface;

    bool bought_successfully = interface.buy_shelf(NO_SHELF, shelf_debit);

    EXPECT_EQ(false, bought_successfully);
}

TEST(ShelfInterfaceTests, TestNothingClosedWhenNothingOverdue) {
    double shelf_debit = 5.0;
    ShelfsInterface interface;
    
    bool bought_successfully = interface.buy_shelf(SHELF_1, shelf_debit);

    EXPECT_EQ(true, bought_successfully);

    uint8_t number_closed = interface.close_overdue_shelfs();

    EXPECT_EQ(0, number_closed);
}

TEST(ShelfInterfaceTests, CloseWhenOverdue) {
    double shelf_debit = 15.0;
    ShelfsInterface interface;

    EXPECT_EQ(0, interface.open_shelfs_to_bit_mask());

    interface.buy_shelf(SHELF_1, shelf_debit);
    EXPECT_EQ(1, interface.open_shelfs_to_bit_mask());
    interface.buy_shelf(SHELF_2, shelf_debit);
    EXPECT_EQ(3, interface.open_shelfs_to_bit_mask());

    tick_timer_interrupt();
    tick_timer_interrupt();
    tick_timer_interrupt();

    uint8_t number_closed = interface.close_overdue_shelfs();
    EXPECT_EQ(0, number_closed);

    interface.buy_shelf(SHELF_3, shelf_debit);
    EXPECT_EQ(7, interface.open_shelfs_to_bit_mask());

    tick_timer_interrupt();
    number_closed = interface.close_overdue_shelfs();
    EXPECT_EQ(4, interface.open_shelfs_to_bit_mask());

    EXPECT_EQ(2, number_closed);

    tick_timer_interrupt();
    tick_timer_interrupt();
    tick_timer_interrupt();

    number_closed = interface.close_overdue_shelfs();
    EXPECT_EQ(0, interface.open_shelfs_to_bit_mask());

    EXPECT_EQ(1, number_closed);
}