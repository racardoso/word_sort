#include <check.h>
#include <stdlib.h>

#include "word_sort.h"

START_TEST(test_word_sort_base)
{
    const char *src = "The   \t\n cat  sat";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), 0);
    ck_assert_str_eq(dst, "The cat sat");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_base_capital)
{
    const char *src = "THE   \t\n CAT  SAT";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), 0);
    ck_assert_str_eq(dst, "CAT SAT THE");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_base_lower_case)
{
    const char *src = "the   \t\n cat  sat";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), 0);
    ck_assert_str_eq(dst, "cat sat the");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_base_reversed)
{
    const char *src = "sat  \t\n cat  The";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), 0);
    ck_assert_str_eq(dst, "The cat sat");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_base_reversed_capital)
{
    const char *src = "SAT \t\n CAT  THE";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_REVERSE);
    ck_assert_str_eq(dst, "THE SAT CAT");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_base_reversed_lower_case)
{
    const char *src = "sat \t\n cat  the";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_REVERSE);
    ck_assert_str_eq(dst, "the sat cat");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_reverse)
{
    const char *src = "The   \t\n cat  sat";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_REVERSE);
    ck_assert_str_eq(dst, "sat cat The");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_empty)
{
    const char *src = "";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), 0);
    ck_assert_str_eq(dst, "");
    ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(test_word_sort_ignore_case)
{
    const char *src = "The   \t\n cat  sat";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_IGNORE_CASE);
    ck_assert_str_eq(dst, "cat sat The");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_ignore_case_capital)
{
    const char *src = "THE   \t\n CAT  SAT";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_IGNORE_CASE);
    ck_assert_str_eq(dst, "CAT SAT THE");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_ignore_case_lower_case)
{
    const char *src = "the   \t\n cat  sat";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_IGNORE_CASE);
    ck_assert_str_eq(dst, "cat sat the");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_ignore_case_reverse)
{
    const char *src = "The   \t\n cat  sat";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_IGNORE_CASE | WORD_SORT_REVERSE);
    ck_assert_str_eq(dst, "The sat cat");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_ignore_case_reverse_2)
{
    const char *src = "The   \t\n Cat  sat";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_IGNORE_CASE | WORD_SORT_REVERSE);
    ck_assert_str_eq(dst, "The sat Cat");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_string_terminator)
{
    const char *src = "The   \t\n cat  sat  \0  not those";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), 0);
    ck_assert_str_eq(dst, "The cat sat");
    ck_assert_int_eq(ret, 12);
}
END_TEST

START_TEST(test_word_sort_small_buffer)
{
    const char *src = "The   \t\n cat  sat  \0  not those";
    char dst[5];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), 0);
    ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(test_word_sort_only_space)
{
    const char *src = "         ";
    char dst[100];
    unsigned int ret = 0;
    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_IGNORE_CASE);
    ck_assert_str_eq(dst, "");
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq((dst[0] == '\0'), 1);
}
END_TEST

Suite *word_sort_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("WordSort");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_word_sort_base);
    tcase_add_test(tc_core, test_word_sort_base_capital);
    tcase_add_test(tc_core, test_word_sort_base_lower_case);
    tcase_add_test(tc_core, test_word_sort_base_reversed);
    tcase_add_test(tc_core, test_word_sort_empty);
    tcase_add_test(tc_core, test_word_sort_reverse);
    tcase_add_test(tc_core, test_word_sort_base_reversed_capital);
    tcase_add_test(tc_core, test_word_sort_base_reversed_lower_case);
    tcase_add_test(tc_core, test_word_sort_ignore_case);
    tcase_add_test(tc_core, test_word_sort_ignore_case_capital);
    tcase_add_test(tc_core, test_word_sort_ignore_case_lower_case);
    tcase_add_test(tc_core, test_word_sort_ignore_case_reverse);
    tcase_add_test(tc_core, test_word_sort_ignore_case_reverse_2);
    tcase_add_test(tc_core, test_word_sort_string_terminator);
    tcase_add_test(tc_core, test_word_sort_small_buffer);
    tcase_add_test(tc_core, test_word_sort_only_space);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = word_sort_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}