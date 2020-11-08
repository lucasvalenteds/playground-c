#include <check.h>
#include <math.h>
#include <stdlib.h>

START_TEST(test_log_two) {
    ck_assert_int_eq(log2(16), 4);
} END_TEST

Suite *math_suite(void) {
    Suite *suite;
    TCase *tcase;

    suite = suite_create("Math Standard Library");
    tcase = tcase_create("Core");

    tcase_add_test(tcase, test_log_two);
    suite_add_tcase(suite, tcase);

    return suite;
}
