include(FetchContent)

FetchContent_Declare(
    GSL
    GIT_REPOSITORY https://github.com/microsoft/GSL.git
    GIT_TAG v3.1.0
)
FetchContent_MakeAvailable(GSL)

FetchContent_Declare(
    abseil
    GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
)
if (NOT absail_POPULATED)
    set(ABSL_BUILD_DLL OFF)
    set(ABSL_ENABLE_INSTALL OFF)
    FetchContent_Populate(abseil)
    add_subdirectory(${abseil_SOURCE_DIR} ${abseil_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()