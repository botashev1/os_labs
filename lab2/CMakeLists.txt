set(CMAKE_C_STANDARD 11)


add_executable(lab2
        main.cpp
        src/parent.cpp
        include/parent.h
        src/utils.cpp include/utils.h)

target_include_directories(lab2 PRIVATE include)

add_executable(child1
        src/child1.cpp
        src/utils.cpp include/utils.h)

target_include_directories(child1 PRIVATE include)

add_executable(child2
        src/child2.cpp
        src/utils.cpp include/utils.h)

target_include_directories(child2 PRIVATE include)