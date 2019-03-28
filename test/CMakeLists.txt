##################################################################################

## TESTS

# ---[ SETUP TEST
add_executable(setup_db_test setup_db_test.cpp)
target_link_libraries(setup_db_test emerald_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME SetupDBTestSuite COMMAND setup_db_test "../../data/schema/catalog.txt" "../../data/database")

# ---[ JOIN TEST
add_executable(join_test join_test.cpp)
target_link_libraries(join_test emerald_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME JoinTestSuite COMMAND join_test "../../data/schema/catalog.txt" "../../data/database")

# ---[ GROUPING TEST
add_executable(grouping_test grouping_test.cpp)
target_link_libraries(grouping_test emerald_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME GroupTestSuite COMMAND grouping_test "../../data/schema/catalog.txt" "../../data/database")


# ---[ PROJECTION TEST
add_executable(projection_test projection_test.cpp)
target_link_libraries(projection_test emerald_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME ProjectionTestSuite COMMAND projection_test "../../data/schema/catalog.txt" "../../data/database")

# ---[ ORDERING TEST
add_executable(order_test order_test.cpp)
target_link_libraries(order_test emerald_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME OrderingTestSuite COMMAND order_test "../../data/schema/catalog.txt" "../../data/database")

# ---[ SCAN TEST
add_executable(scan_test scan_test.cpp)
target_link_libraries(scan_test emerald_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME ScanTestSuite COMMAND scan_test "../../data/schema/catalog.txt" "../../data/database")


# ---[ DATACUBE TEST
add_executable(datacube_test datacube_test.cpp)
target_link_libraries(datacube_test emerald_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME DatacubeTestSuite COMMAND datacube_test "../../data/schema/catalog.txt" "../../data/database")

# ---[ BENCHMARK 
add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark emerald_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME BenchmarkSuite COMMAND benchmark "../../data/schema/catalog.txt" "../../data/database")





# --[ Add "make check" target

set(CTEST_FLAGS "")
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_FLAGS} --verbose)

