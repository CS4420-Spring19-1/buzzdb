##################################################################################

## TESTS


# --[ Add "make check" target

set(CTEST_FLAGS "")
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_FLAGS} --verbose)

