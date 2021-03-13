#include "tests/test_language.c"
#include "tests/test_stdlib.c"
#include <check.h>
#include <stdio.h>

int main(void) {
    int no_failed = 0;
    Suite *suite = suite_create("");
    SRunner *runner = srunner_create(suite);

    srunner_add_suite(runner, language_suite());
    srunner_add_suite(runner, stdlib_suite());

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (no_failed > 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
