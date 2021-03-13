#include <check.h>

START_TEST(test_iterating_array_using_pointers) {
    char word[] = "pineapple";
    char word_uppercased[sizeof(word)];

    for (int i = 0; i < sizeof(word) - 1; i++) {
        word_uppercased[i] = *(word + i) - 32;
    }

    ck_assert_str_eq("PINEAPPLE", word_uppercased);
}
END_TEST

Suite *language_suite(void) {
    Suite *suite = suite_create("Language features");
    TCase *tcase = tcase_create("Core");

    tcase_add_test(tcase, test_iterating_array_using_pointers);
    suite_add_tcase(suite, tcase);

    return suite;
}
