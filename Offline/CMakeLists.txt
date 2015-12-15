PROJECT(DISearchOffline)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

find_package(OpenCV REQUIRED)

SET(SRC 
    main.cpp
    DIIndex.cpp
    )

SET(HDR
    DIIndex.h
    )

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC} ${HDR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
