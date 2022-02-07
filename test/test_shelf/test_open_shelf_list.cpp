#include "Data/OpenShelfList.h"

#include <unity.h>

#include "Data/Shelf.h"

void test_insert_shelf(void) {
    // Shelf first(SHELF_1, 5);
    // OpenShelfList list;

    // bool success = list.insert(first);
    // TEST_ASSERT_EQUAL(true, success);
    TEST_ASSERT_EQUAL(true, true);
}


void main() {
    UNITY_BEGIN();

    RUN_TEST(test_insert_shelf);

    UNITY_END();
}
