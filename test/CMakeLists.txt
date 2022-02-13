set(target unittest)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

FetchContent_MakeAvailable(googletest)

set(include_path 
    "../lib/ShelfsInterface"
)
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(sources
    ${source_path}/test_shelf/mocks/Shift74HC595Mock.cpp
    ${source_path}/test_shelf/mocks/TimerInterruptMock.cpp
    ${source_path}/test_shelf/test_shelf.cpp
    ${source_path}/test_shelf/test_open_shelf_list.cpp
    ${source_path}/test_shelf/test_shelf_interface.cpp
)
add_executable(${target}
    ${sources}
)

target_include_directories(${target}
  PRIVATE
  ${include_path}
)

target_link_libraries(${target} PUBLIC
    honeyvending
    gtest_main
)

include(GoogleTest)
gtest_add_tests(TARGET      ${target}
                TEST_PREFIX test
                TEST_LIST   allTests
)
