#include "cassert"
#include "fstream"
#include "iostream"
#include "CUnit/Basic.h"

using namespace std;
/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
    if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
        return -1;
    }
    else {
        return 0;
    }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    if (0 != fclose(temp_file)) {
        return -1;
    }
    else {
        temp_file = NULL;
        return 0;
    }
}
bool testAll() {
    std::ifstream stu, ans;
    std::string s_stu, s_ans;
    int lineno = 0;

    std::string name = "./case_test_ans.txt";
    stu.open(name, std::ios::in);
    if (!stu.is_open()) {
        cout << "ooo" << endl;
        return false;
    }

    name = "./case_test_res.txt";
    ans.open(name, std::ios::in);
    if (!ans.is_open()) {
        cout << "ooo" << endl;
        return false;
    }

    while (getline(stu, s_stu) && getline(ans, s_ans)) {
        lineno++;
        if (s_stu != s_ans && (s_stu.size() - s_ans.size() != 1 && s_stu.size() - s_ans.size() != -1)) {
            cout << "line " << lineno << " mismatch:\n" << s_stu << "\n(stu) vs.\n"
                 << s_ans << "\n(ans)" << std::endl;
            return false;
        }
    }

    stu.close();
    ans.close();
    return true;
}

int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if (NULL == CU_add_test(pSuite, "test of spot-palm", testAll)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}