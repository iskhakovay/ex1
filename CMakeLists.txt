cmake_minimum_required(VERSION 3.0.0)
project(HackEnrollment VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCES
        main.c
        IsraeliQueue.c
        HackEnrollment.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_executable(HackEnrollment ${SOURCES})
