if(EXISTS "/home/yangwende/cmu15445/build/test/disk_manager_test[1]_tests.cmake")
  include("/home/yangwende/cmu15445/build/test/disk_manager_test[1]_tests.cmake")
else()
  add_test(disk_manager_test_NOT_BUILT disk_manager_test_NOT_BUILT)
endif()
