cmake_minimum_required(VERSION 3.13.4)
project(frontend)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(scanner
    lexic.l
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

bison_target(parser
    compiler.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/grammar.tab.hpp")

add_flex_bison_dependency(scanner parser)

add_executable(${PROJECT_NAME}
    # ../inode/inode.cpp
    driver.cpp
    ${BISON_parser_OUTPUTS}
    ${FLEX_scanner_OUTPUTS}
)

set(CMAKE_CXX_FLAGS  -fsanitize=address,leak)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20 )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                                    ../../include/backend/tokens/
                                                    ../../include/inode/)
