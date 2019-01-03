cmake_minimum_required(VERSION 3.8)
project(finalproject)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c board.c board.h command.c command.h inputvalidation.c inputvalidation.h write.c write.h help.c help.h resize.c resize.h save.c save.h load.c load.h)
add_executable(finalproject ${SOURCE_FILES} board.c board.h command.c command.h inputvalidation.c inputvalidation.h write.c write.h help.c help.h resize.c resize.h save.c save.h load.c load.h)