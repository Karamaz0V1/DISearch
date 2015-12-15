PROJECT(DISearchOnline)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

find_package(OpenCV REQUIRED)

SET(SRC
	lire_fichier.cpp
)

SET(HDR
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC} ${HDR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
