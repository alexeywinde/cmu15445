if(EXISTS "/home/yangwende/cmu15445/cmu15445/build/test/hash_table_test[1]_tests.cmake")
  include("/home/yangwende/cmu15445/cmu15445/build/test/hash_table_test[1]_tests.cmake")
else()
  add_test(hash_table_test_NOT_BUILT hash_table_test_NOT_BUILT)
endif()
