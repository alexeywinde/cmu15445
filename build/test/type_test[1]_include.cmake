if(EXISTS "/home/yangwende/cmu15445/cmu15445/build/test/type_test[1]_tests.cmake")
  include("/home/yangwende/cmu15445/cmu15445/build/test/type_test[1]_tests.cmake")
else()
  add_test(type_test_NOT_BUILT type_test_NOT_BUILT)
endif()
