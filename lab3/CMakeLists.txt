add_executable(lab3
        main.cpp
        src/lab3.cpp include/lab3.h
        src/utils.cpp include/utils.h)

target_include_directories(lab3 PRIVATE include)
