cmake_minimum_required(VERSION 3.28)
project(ops_limiter C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ops_limiter
        example.c
        ops_limiter.c
        ops_limiter.h
        ops_limiter_timer.h)
