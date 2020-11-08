#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <errno.h>

START_TEST(test_reading_file_content) {
	char current_work_directory[PATH_MAX];
	ck_assert_msg(
			getcwd(current_work_directory, sizeof(current_work_directory)) != NULL,
			"Error while getting current work directory: %s\n", strerror(errno));

	char filename[PATH_MAX] = "";
	strcat(filename, current_work_directory);
	strcat(filename, "/resources/regular-file.txt");

	FILE *file = fopen(filename, "r");
	ck_assert_msg(file != NULL,
			"Error while reading file: %s %s", strerror(errno), filename);

	char content[100] = "";
	while (!feof(file)) {
		fread(content, sizeof(content), 1, file);
	}

	char line[6] = "line 1";
	for (int i = 0; i < sizeof(line); i++) {
		ck_assert(content[i] == line[i]);
	}

	fclose(file);
} END_TEST

START_TEST(test_reading_file_size) {
	char current_work_directory[PATH_MAX];
	ck_assert_msg(
			getcwd(current_work_directory, sizeof(current_work_directory)) != NULL,
			"Error while getting current work directory: %s", strerror(errno));

	char filename[PATH_MAX] = "";
	strcat(filename, current_work_directory);
	strcat(filename, "/resources/huge-file.txt");

	FILE *file = fopen(filename, "r");
	ck_assert_msg(file != NULL, 
			"Error while reading file: %s %s", strerror(errno), filename);
	ck_assert_msg(
			fseek(file, 0, SEEK_END) == 0,
			"Error while seeking file: %s %s", strerror(errno), filename);

	int long size = ftell(file);
	int long size_in_mb = size / 1024;
	ck_assert_int_eq(size_in_mb, 37197);

	fclose(file);
} END_TEST

Suite *stdio_suite(void) {
	Suite *suite;
	TCase *tcase;

	suite = suite_create("I/O Standard Library");
	tcase = tcase_create("Core");

	tcase_add_test(tcase, test_reading_file_content);
	tcase_add_test(tcase, test_reading_file_size);
	suite_add_tcase(suite, tcase);

	return suite;
}
