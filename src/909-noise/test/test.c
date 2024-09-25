#include "greatest.h"

TEST dummy(void) {
    ASSERT_TRUE(true);
    PASS();
}

SUITE(testsuite) {
    RUN_TEST(dummy);
}

int main(int argv, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(testsuite);

    GREATEST_MAIN_END();
}
