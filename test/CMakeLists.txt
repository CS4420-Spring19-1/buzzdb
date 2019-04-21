##################################################################################

## TESTS
# ---[HEAPPAGEID TEST
add_executable(heap_page_id_test heap_page_id_test.cpp)
target_link_libraries(heap_page_id_test buzzdb_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME HeapPageIdTestSuite COMMAND heap_page_id_test)

# ---[RECORDID TEST
add_executable(record_id_test record_id_test.cpp)
target_link_libraries(record_id_test buzzdb_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME RecordIdTestSuite COMMAND record_id_test)

# --[ Add "make check" target

set(CTEST_FLAGS "")
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_FLAGS} --verbose)

