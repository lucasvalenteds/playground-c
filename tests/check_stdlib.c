#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

START_TEST(test_generating_random_number) {
    srand(time(NULL));

    const int random_integer = rand();

    ck_assert_msg(random_integer >= 0, "Random number should be greater than zero");
    ck_assert_msg(random_integer <= RAND_MAX, "Random number should be smaller than %d", RAND_MAX);
} END_TEST

START_TEST(test_generating_random_number_between_zero_and_n) {
    const int n = 10;
    srand(time(NULL));

    const int random_integer = rand() % n;

    ck_assert_msg(random_integer >= 0, "Random number should be greater than zero");
    ck_assert_msg(random_integer <= n, "Random number should be smaller than %d", n);
} END_TEST

Suite *stdlib_suite(void) {
    Suite *suite = suite_create("Standard Library");
    TCase *tcase = tcase_create("Core");

    tcase_add_test(tcase, test_generating_random_number);
    tcase_add_test(tcase, test_generating_random_number_between_zero_and_n);
    suite_add_tcase(suite, tcase);

    return suite;
}
