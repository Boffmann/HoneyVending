set(target honeyvending)

set(include_path 
)
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(sources
    ${source_path}/Shelf.cpp
    ${source_path}/OpenShelfList.cpp
    ${source_path}/ShelfsInterface.cpp
)

add_library(${target} SHARED 
    ${sources}
)

target_include_directories(${target}
  PRIVATE
  ${include_path}
)