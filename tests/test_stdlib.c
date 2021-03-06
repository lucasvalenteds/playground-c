#include <check.h>
#include <ctype.h>
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

START_TEST(test_log_two) { ck_assert_int_eq(log2(16), 4); }
END_TEST

START_TEST(test_changing_string_case_to_uppercase) {
    char lowercase_word[] = "heLLo";
    char uppercase_word[sizeof(lowercase_word)] = "";

    for (int i = 0; i < sizeof(lowercase_word); i++) {
        uppercase_word[i] = toupper(lowercase_word[i]);
    }

    ck_assert_str_eq("HELLO", uppercase_word);
    ck_assert_msg(islower(lowercase_word[0]),
                  "First letter should be lowercase");
}
END_TEST

START_TEST(test_changing_string_case_to_lowercase) {
    char upercase_word[] = "HEll0";
    char lowercase_word[sizeof(upercase_word)] = "";

    for (int i = 0; i < sizeof(upercase_word); i++) {
        lowercase_word[i] = tolower(upercase_word[i]);
    }

    ck_assert_str_eq("hell0", lowercase_word);
    ck_assert_msg(isupper(upercase_word[0]),
                  "First letter should be uppercase");
}
END_TEST

START_TEST(test_reading_file_content) {
    char current_work_directory[PATH_MAX];
    ck_assert_msg(
        getcwd(current_work_directory, sizeof(current_work_directory)) != NULL,
        "Error while getting current work directory: %s\n", strerror(errno));

    char filename[PATH_MAX] = "";
    strcat(filename, current_work_directory);
    strcat(filename, "/resources/regular-file.txt");

    FILE *file = fopen(filename, "r");
    ck_assert_msg(file != NULL, "Error while reading file: %s %s",
                  strerror(errno), filename);

    char content[100] = "";
    while (!feof(file)) {
        fread(content, sizeof(content), 1, file);
    }

    char line[6] = "line 1";
    for (int i = 0; i < sizeof(line); i++) {
        ck_assert(content[i] == line[i]);
    }

    fclose(file);
}
END_TEST

START_TEST(test_reading_file_size) {
    char current_work_directory[PATH_MAX];
    ck_assert_msg(
        getcwd(current_work_directory, sizeof(current_work_directory)) != NULL,
        "Error while getting current work directory: %s", strerror(errno));

    char filename[PATH_MAX] = "";
    strcat(filename, current_work_directory);
    strcat(filename, "/resources/huge-file.txt");

    FILE *file = fopen(filename, "r");
    ck_assert_msg(file != NULL, "Error while reading file: %s %s",
                  strerror(errno), filename);
    ck_assert_msg(fseek(file, 0, SEEK_END) == 0,
                  "Error while seeking file: %s %s", strerror(errno), filename);

    int long size = ftell(file);
    int long size_in_mb = size / 1024;
    ck_assert_int_eq(size_in_mb, 37197);

    fclose(file);
}
END_TEST

START_TEST(test_reading_file_error_handling) {
    const char *name = "unknown-file.txt";
    const char *mode = "r";

    FILE *file = fopen(name, mode);
    const char *error_message = strerror(errno);

    ck_assert_ptr_null(file);
    ck_assert_str_eq(error_message, "No such file or directory");
}
END_TEST

START_TEST(test_writing_new_file) {
    char current_work_directory[PATH_MAX];
    ck_assert_msg(
        getcwd(current_work_directory, sizeof(current_work_directory)) != NULL,
        "Error while getting current work directory: %s", strerror(errno));

    char filename[PATH_MAX] = "";
    strcat(filename, current_work_directory);
    strcat(filename, "/resources/new-empty-file.txt");

    FILE *file;

    file = fopen(filename, "w");
    ck_assert_msg(file != NULL, "Error while creating a new empty file: %s",
                  strerror(errno));
    fclose(file);

    file = fopen(filename, "r");
    ck_assert_msg(fseek(file, 0, SEEK_END) == 0,
                  "The new file created should be empty");
    ck_assert_msg(file != NULL, "Error while reading a new empty file: %s",
                  strerror(errno));
    fclose(file);

    ck_assert_msg(remove(filename) == 0,
                  "Error while removing a new empty file: %s", strerror(errno));
}
END_TEST

START_TEST(test_generating_random_number) {
    srand(time(NULL));

    const int random_integer = rand();

    ck_assert_msg(random_integer >= 0,
                  "Random number should be greater than zero");
    ck_assert_msg(random_integer <= RAND_MAX,
                  "Random number should be smaller than %d", RAND_MAX);
}
END_TEST

START_TEST(test_generating_random_number_between_zero_and_n) {
    const int n = 10;
    srand(time(NULL));

    const int random_integer = rand() % n;

    ck_assert_msg(random_integer >= 0,
                  "Random number should be greater than zero");
    ck_assert_msg(random_integer <= n,
                  "Random number should be smaller than %d", n);
}
END_TEST

Suite *stdlib_suite(void) {
    Suite *suite = suite_create("Standard library");
    TCase *tcase = tcase_create("Core");

    tcase_add_test(tcase, test_log_two);
    tcase_add_test(tcase, test_changing_string_case_to_uppercase);
    tcase_add_test(tcase, test_changing_string_case_to_lowercase);
    tcase_add_test(tcase, test_reading_file_content);
    tcase_add_test(tcase, test_reading_file_size);
    tcase_add_test(tcase, test_reading_file_error_handling);
    tcase_add_test(tcase, test_writing_new_file);
    tcase_add_test(tcase, test_generating_random_number);
    tcase_add_test(tcase, test_generating_random_number_between_zero_and_n);
    suite_add_tcase(suite, tcase);

    return suite;
}
