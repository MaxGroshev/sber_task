set(SRCS
        operators.cpp
        elems.cpp
        cond_operators.cpp
        scope.cpp
        io.cpp
        symtable.cpp
        utils.cpp
)

add_library(tokens ${SRCS})
target_include_directories(tokens PRIVATE ${CMAKE_BINARY_DIR})
