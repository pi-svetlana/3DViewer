include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



add_executable(
        viewer_tests
        parser_tests.cc
        converter_tests.cc
)

target_link_libraries(
        viewer_tests
        viewer_models_lib
        GTest::gtest_main
)

 file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/samples" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")



include(GoogleTest)
gtest_discover_tests(viewer_tests)
