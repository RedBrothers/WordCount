cmake_minimum_required(VERSION 3.10)

SET(PROJECT_NAME wordcount)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED
        COMPONENTS
        locale thread
        filesystem)

find_package(ICU REQUIRED
        COMPONENTS
        data i18n test
        io tu uc)

add_executable(${PROJECT_NAME}
        main.cpp
        config.cpp
        counter.cpp
        base_manager.cpp
        simple_manager.cpp queue_manager.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${Boost_LIBRARIES}
        ${ICU_LIBRARIES}
        )