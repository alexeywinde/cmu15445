if(EXISTS "/home/yangwende/cmu15445/build/test/binder_test[1]_tests.cmake")
  include("/home/yangwende/cmu15445/build/test/binder_test[1]_tests.cmake")
else()
  add_test(binder_test_NOT_BUILT binder_test_NOT_BUILT)
endif()
