##################################################################################

## TESTS

# ---[ BASIC TEST
add_executable(basic_test basic_test.cpp)
target_link_libraries(basic_test engine_library
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME BasicTest COMMAND basic_test)

## ENGINE 

# ---[ ENGINE
add_executable(engine engine.cpp)
target_link_libraries(engine engine_library 
${GTEST_BOTH_LIBRARIES} 
${GLOG_LIBRARIES} 
${CMAKE_THREAD_LIBS_INIT}
)
add_test(NAME EngineTest COMMAND engine)

# --[ Add "make check" target

set(CTEST_FLAGS "")
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_FLAGS} --verbose)

