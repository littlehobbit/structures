
project(lib CXX)

file(GLOB
        HEADERS "includes/*.h"
)

add_library(${PROJECT_NAME} ${HEADERS})

set_target_properties(lib PROPERTIES LINKER_LANGUAGE CXX)

include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
