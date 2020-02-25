cmake_minimum_required(VERSION 3.10)

SET(PROJECT_NAME wordcount)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED
        COMPONENTS
        locale
        system
        thread
        filesystem)
find_package(Threads REQUIRED)
find_package(LibArchive REQUIRED)
find_package(ICU REQUIRED
        COMPONENTS
        data i18n test
        io tu uc)
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/utils.cpp
        src/config.cpp
        src/simple_manager.cpp
        src/queue_manager.cpp
        src/indexer.cpp
        src/counter.cpp
        src/merger.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include src)
target_link_libraries(${PROJECT_NAME} PUBLIC
        ${Boost_LIBRARIES}
        ${ICU_LIBRARIES}
        Threads::Threads
        )