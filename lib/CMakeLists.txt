
project(lib)

#file(GLOB
#        HEADERS "includes/*.h"
#)

# add_library(${PROJECT_NAME} ${HEADERS})

include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
