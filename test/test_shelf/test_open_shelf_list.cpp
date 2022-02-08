#include <gtest/gtest.h>

#include "Data/Shelf.h"
#include "Data/OpenShelfList.h"

TEST(OpenShelfListTest, TestInitialisation) {
    OpenShelfList list;

    const node_t *head = list.get_first();

    EXPECT_EQ(nullptr, head);
}

TEST(OpenShelfListTest, TestInsert) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    list.insert(shelf1);

    const node_t *head = list.get_first();

    EXPECT_EQ(nullptr, list.get_next(head));
    EXPECT_EQ(shelf1, list.get_shelf(head));

    list.insert(shelf2);
    EXPECT_EQ(shelf2, list.get_shelf(list.get_next(head)));
}

TEST(OpenShelfListTest, DontAllowMultiple) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_1, 5);
    
    bool insert_successful = list.insert(shelf1);
    EXPECT_EQ(true, insert_successful);
    EXPECT_EQ(shelf1, list.get_shelf(list.get_first()));

    insert_successful = list.insert(shelf2);
    EXPECT_EQ(false, insert_successful);
    EXPECT_EQ(shelf1, list.get_shelf(list.get_first()));
}

TEST(OpenShelfListTest, DoNotInsertWhenMaxReached) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    Shelf shelf3(SHELF_3, 5);
    Shelf shelf4(SHELF_4, 5);
    Shelf shelf5(SHELF_5, 5);
    Shelf shelf6(SHELF_6, 5);
    Shelf shelf7(7, 5);
    
    list.insert(shelf1);
    list.insert(shelf2);
    list.insert(shelf3);
    list.insert(shelf4);
    list.insert(shelf5);
    bool insert_successful = list.insert(shelf6);
    EXPECT_EQ(true, insert_successful);

    insert_successful = list.insert(shelf7);
    EXPECT_EQ(false, insert_successful);
}

TEST(OpenShelfListTest, RemoveFromEmptyList) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);

    EXPECT_EQ(nullptr, list.get_first());

    // Should not throw
    list.remove(shelf1);    
}

TEST(OpenShelfListTest, RemoveTail) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    Shelf shelf3(SHELF_3, 5);
    list.insert(shelf1);
    list.insert(shelf2);
    list.insert(shelf3);

    const node_t *head = list.get_first();
    const node_t *intermediate = list.get_next(head);

    EXPECT_EQ(shelf3, list.get_shelf(list.get_next(intermediate)));

    list.remove(shelf3);

    EXPECT_EQ(nullptr, list.get_next(intermediate));
    
}

TEST(OpenShelfListTest, RemoveIntermediate) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    Shelf shelf3(SHELF_3, 5);
    list.insert(shelf1);
    list.insert(shelf2);
    list.insert(shelf3);

    const node_t *head = list.get_first();

    EXPECT_EQ(shelf2, list.get_shelf(list.get_next(head)));

    list.remove(shelf2);

    EXPECT_EQ(shelf3, list.get_shelf(list.get_next(head)));
}

TEST(OpenShelfListTest, RemoveHead) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    Shelf shelf3(SHELF_3, 5);
    list.insert(shelf1);
    list.insert(shelf2);
    list.insert(shelf3);

    EXPECT_EQ(shelf1, list.get_shelf(list.get_first()));

    list.remove(shelf1);

    EXPECT_EQ(shelf2, list.get_shelf(list.get_first()));
}

TEST(OpenShelfListTest, ReinsertAfterRemoveTail) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    Shelf shelf3(SHELF_3, 5);
    Shelf shelf4(SHELF_4, 5);
    list.insert(shelf1);
    list.insert(shelf2);
    list.insert(shelf3);

    list.remove(shelf3);

    list.insert(shelf4);
    const node_t *intermediate = list.get_next(list.get_first());
    EXPECT_EQ(shelf4, list.get_shelf(list.get_next(intermediate)));
}

TEST(OpenShelfListTest, ReinsertAfterRemoveIntermediate) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    Shelf shelf3(SHELF_3, 5);
    Shelf shelf4(SHELF_4, 5);
    list.insert(shelf1);
    list.insert(shelf2);
    list.insert(shelf3);
    
    const node_t *head = list.get_first();

    list.remove(shelf2);

    list.insert(shelf4);
    const node_t *intermediate = list.get_next(head);
    EXPECT_EQ(shelf4, list.get_shelf(list.get_next(intermediate)));
}

TEST(OpenShelfListTest, ReinsertAfterRemoveHead) {
    OpenShelfList list;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    Shelf shelf3(SHELF_3, 5);
    Shelf shelf4(SHELF_4, 5);
    list.insert(shelf1);
    list.insert(shelf2);
    list.insert(shelf3);

    list.remove(shelf1);

    list.insert(shelf4);
    const node_t *head = list.get_first();
    const node_t *intermediate = list.get_next(head);
    EXPECT_EQ(shelf4, list.get_shelf(list.get_next(intermediate)));
}

TEST(OpenShelfListTest, IndependentLists) {
    OpenShelfList list;
    OpenShelfList list2;
    Shelf shelf1(SHELF_1, 5);
    Shelf shelf2(SHELF_2, 5);
    list.insert(shelf1);
    list2.insert(shelf2);

    EXPECT_EQ(shelf1, list.get_shelf(list.get_first()));
    EXPECT_EQ(shelf2, list2.get_shelf(list2.get_first()));
}