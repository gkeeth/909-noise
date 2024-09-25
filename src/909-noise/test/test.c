#include <stdbool.h>
#include "greatest.h"

TEST dummy(void) {
    ASSERT(true);
    PASS();
}

SUITE(testsuite) {
    RUN_TEST(dummy);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(testsuite);

    GREATEST_MAIN_END();
}
