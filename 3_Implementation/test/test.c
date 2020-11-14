#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include<tourism.h>
#define PROJECT_NAME    "Tourism_Management_System"

void test_adduser(void);
void test_loginuser(void);
void test_brochure(void);
void test_exit(void);


int main() {

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
  CU_pSuite suite = CU_add_suite(PROJECT_NAME, 0, 0);
  
  CU_add_test(suite, "adduser", test_adduser);
  CU_add_test(suite, "loginuser", test_loginuser);
  CU_add_test(suite, "brochure", test_brochure);
  CU_add_test(suite, "exit", test_exit);
  
 

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return 0;
}
void test_adduser(void){
  CU_ASSERT(abcd == add(abcd));          //adding username
  CU_ASSERT(abcd@123 == add(abcd@123));  //adding password
  CU_ASSERT(def == add(def));           //adding username
  CU_ASSERT(def@123 == add(def@123));   //adding  password
 }

void test_loginuser(void){
  CU_ASSERT(abcd ==login(abcd));           //login username
  CU_ASSERT(abcd@123 == login(abcd@123));  //login password
  CU_ASSERT(def == login(def));           //login  username
  CU_ASSERT(def@123 == login(def@123));   //login   password
 
  
}




