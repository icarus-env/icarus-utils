# CMakeLists.txt of the library "icarus-utils"

# =====================================
# Library build
# =====================================
set(UTILS_LIB_SOURCES
    "data_node.cpp"
    "logging_module.cpp"
    "str_processing.cpp"
    "system_ops.cpp")

# Find external libraries
find_package(spdlog CONFIG REQUIRED)
find_package(ryml CONFIG REQUIRED)

# Add library (shared)
add_library(icarus-utils SHARED ${UTILS_LIB_SOURCES})
add_library(icarus::utils ALIAS icarus-utils)
target_include_directories(icarus-utils PUBLIC ${ICARUS-UTILS_ROOT_DIR}/include)
target_link_libraries(icarus-utils
                      PUBLIC ryml::ryml spdlog::spdlog)

# =====================================
# Library installation
# =====================================
install(TARGETS icarus-utils
	    RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
# Install linked libraries (.dll/.so)
if (WIN32)
    install(IMPORTED_RUNTIME_ARTIFACTS)
endif()
