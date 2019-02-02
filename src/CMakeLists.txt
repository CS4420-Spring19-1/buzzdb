##################################################################################

# --[ Emerald library

file(GLOB SRC_FILES
    "database/*.cpp"
    "emerald_db.cpp"
    "configuration.cpp"
    "types.cpp"
)

# Create our library
add_library (emerald_library ${SRC_FILES})

# Make sure the compiler can find include files for our machine library
# when other libraries or executables link to machine
target_include_directories (emerald_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
