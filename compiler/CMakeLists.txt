cmake_minimum_required(VERSION 3.13.4)
project(compiler)

# Build flags
# include(cmake/build_flags.cmake)

#FLEX/BISON--------------------------------------------------------------------

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(scanner
    ./include/frontend/lexic.l
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

bison_target(parser
    ./include/frontend/compiler.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/grammar.tab.hpp" )

add_flex_bison_dependency(scanner parser ./src/inode/inode.cpp)

#------------------------------------------------------------------------------

# collect srcs

add_subdirectory(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# srcs
foreach(SRC ${SRC_LIST})
    target_compile_options(${SRC} PUBLIC "$<$<CONFIG:Debug>:${DEBUG_BUILD}>")
    target_link_options(${SRC}    PUBLIC "$<$<CONFIG:Debug>:${DEBUG_LINK}>")

    target_compile_features(${SRC} PUBLIC cxx_std_20)
    target_include_directories(${SRC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${SRC})
    target_include_directories(${SRC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    install(TARGETS ${SRC} DESTINATION bin)
endforeach()


# Create main.cpp
add_executable(${PROJECT_NAME} main.cpp ${FLEX_scanner_OUTPUTS} ${BISON_parser_OUTPUTS})

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${DEBUG_BUILD}>")
target_link_options(${PROJECT_NAME}    PUBLIC "$<$<CONFIG:Debug>:${DEBUG_LINK}>")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_link_libraries(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#------------------------------------------------------------------------------

install(TARGETS ${PROJECT_NAME})
install()
