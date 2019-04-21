##################################################################################

## TESTS
# ---[HEAPPAGEID TEST
add_executable(heap_page_id_unit_test heap_page_id_unit_test.cpp)
target_link_libraries(heap_page_id_unit_test buzzdb_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME HeapPageIdUnitTestSuite COMMAND heap_page_id_unit_test)

# ---[RECORDID TEST
add_executable(record_id_unit_test record_id_unit_test.cpp)
target_link_libraries(record_id_unit_test buzzdb_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME RecordIdUnitTestSuite COMMAND record_id_unit_test)

# --[ Add "make check" target

set(CTEST_FLAGS "")
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_FLAGS} --verbose)

