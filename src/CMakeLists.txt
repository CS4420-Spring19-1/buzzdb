##################################################################################

# --[ Emerald library

# Create our library
add_library (emerald_library benchmark.cpp configuration.cpp types.cpp zipfian.cpp)

# Make sure the compiler can find include files for our machine library
# when other libraries or executables link to machine
target_include_directories (emerald_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
