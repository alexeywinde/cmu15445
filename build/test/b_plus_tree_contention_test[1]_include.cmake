if(EXISTS "/home/yangwende/cmu15445/build/test/b_plus_tree_contention_test[1]_tests.cmake")
  include("/home/yangwende/cmu15445/build/test/b_plus_tree_contention_test[1]_tests.cmake")
else()
  add_test(b_plus_tree_contention_test_NOT_BUILT b_plus_tree_contention_test_NOT_BUILT)
endif()
