PROJECT(DISearchOffline)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

find_package(OpenCV REQUIRED)

SET(SRC 
    main.cpp
    DIIndex.cpp
    utils.cpp
    )

SET(HDR
    DIIndex.h
    utils.h
    )

add_definitions(-std=c++11) # plz istic, update your cmake :(
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC} ${HDR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
