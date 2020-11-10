#include <check.h>
#include <stdio.h>
#include "tests/check_math.c"
#include "tests/check_stdio.c"

int main(void) {
    int no_failed = 0;
    Suite *suite = suite_create("");
    SRunner *runner = srunner_create(suite);

    srunner_add_suite(runner, math_suite());
    srunner_add_suite(runner, stdio_suite());

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (no_failed > 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
