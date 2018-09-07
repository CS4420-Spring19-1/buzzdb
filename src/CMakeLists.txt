##################################################################################

# --[ Engine library

# Create our library
add_library (engine_library engine.cpp configuration.cpp types.cpp)

# Make sure the compiler can find include files for our machine library
# when other libraries or executables link to machine
target_include_directories (engine_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
