cmake_minimum_required(VERSION 3.22)
project(courseworkex C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(courseworkex
        main.c
        menu.c
        menu.h
        patientsList.c
        patientsList.h)
