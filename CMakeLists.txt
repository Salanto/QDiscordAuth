cmake_minimum_required(VERSION 3.19)
project(AOOAuth LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Network NetworkAuth)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Network NetworkAuth)

qt_standard_project_setup()

qt_add_executable(AOOAuth
    main.cpp
    aooauth.h aooauth.cpp
)

target_link_libraries(AOOAuth
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Network
        Qt::NetworkAuth
)
target_link_libraries(AOOAuth PRIVATE Qt6::Core)
