##################################################################################

# --[ Emerald library

file(GLOB SRC_FILES
    "database/*.cpp"
    "configuration.cpp"
    "types.cpp"
    "zipfian.cpp"
    "key_vector.cpp"
    "inverted_index.cpp"
    "interval.cpp"
    "interval_index.cpp"
    "benchmark.cpp"

)

# Create our library
add_library (emerald_library ${SRC_FILES})

# Make sure the compiler can find include files for our machine library
# when other libraries or executables link to machine
target_include_directories (emerald_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
