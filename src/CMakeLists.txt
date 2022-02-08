set(target honeyvending)

set(include_path 
    "../include"
)
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(sources
    ${source_path}/Shelf.cpp
    ${source_path}/OpenShelfList.cpp
    ${source_path}/ShelfsInterface.cpp
    ${source_path}/mocks/Shift74HC595Mock.cpp
    ${source_path}/mocks/TimerInterruptMock.cpp
)

add_library(${target} SHARED 
    ${sources}
)

target_include_directories(${target}
  PRIVATE
  ${include_path}
)