if(EXISTS "/home/yangwende/cmu15445/cmu15445/build/test/transaction_test[1]_tests.cmake")
  include("/home/yangwende/cmu15445/cmu15445/build/test/transaction_test[1]_tests.cmake")
else()
  add_test(transaction_test_NOT_BUILT transaction_test_NOT_BUILT)
endif()
