#include <stdbool.h>
#include "greatest.h"

#include "lfsr.h"

TEST test_lfsr(void) {
    uint32_t lfsr = 0xFFFFFFFF;
    uint32_t output;
    lfsr_step(&lfsr, &output);
    ASSERT_EQ(lfsr, 0xFFFFFFFE);
    lfsr_step(&lfsr, &output);
    ASSERT_EQ(lfsr, 0xFFFFFFFC);
    for (int i = 2; i < 13; ++i) {
        lfsr_step(&lfsr, &output);
    }
    ASSERT_EQ(lfsr, 0xFFFFE000);
    lfsr_step(&lfsr, &output);
    ASSERT_EQ(lfsr, 0xFFFFC001);
    PASS();
}

SUITE(testsuite) {
    RUN_TEST(test_lfsr);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(testsuite);

    GREATEST_MAIN_END();
}
