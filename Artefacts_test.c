#include "CUnit.h"
#include "Artefacts.h"
#include "Basic.h"
#include <stdio.h>  // for printf
int init_suite(void) {
	return 0;
}
int clean_suite(void) {
	return 0;
}

void encrypt_test_1(void) {
	CU_ASSERT_EQUAL(encrypt("test"), "yjxy");
}

int main(void) {

	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("encrypt_test_suite", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite, "encrypt_test_1", encrypt_test_1))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	printf("\n");
	CU_basic_show_failures(CU_get_failure_list());
	printf("\n\n");
	/*
	 // Run all tests using the automated interface
	 CU_automated_run_tests();
	 CU_list_tests_to_file();

	 // Run all tests using the console interface
	 CU_console_run_tests();
	 */
	/* Clean up registry and return */
	CU_cleanup_registry();
	return CU_get_error();
}
