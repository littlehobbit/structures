
project(word-counter)

file(
    GLOB
        CXX_SOURCES "*.cpp"
)

add_executable(${PROJECT_NAME} ${CXX_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ../lib/includes)
