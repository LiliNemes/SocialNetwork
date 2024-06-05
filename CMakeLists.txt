cmake_minimum_required(VERSION 3.20)
project(NHF C)

set(CMAKE_C_STANDARD 99)

add_executable(NHF main.c readin.c readin.h datamgmt.c datamgmt.h menu.c menu.h information.c information.h delete_society.c delete_society.h filemgmt.c filemgmt.h misconceptions.c misconceptions.h spreading.c spreading.h)
