#include "Artefacts.h"

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

	if ((NULL == CU_add_test(pSuite, "encrypt_test_1"))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	printf("\n");
	CU_automated_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
