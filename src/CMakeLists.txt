##################################################################################

# --[ BuzzDB library

file(GLOB SRC_FILES
    "database/*.cpp"
)

# Create our library
add_library (buzzdb_library ${SRC_FILES})

# Make sure the compiler can find include files for our machine library
# when other libraries or executables link to machine
target_include_directories (buzzdb_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
