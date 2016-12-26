cmake_minimum_required ( VERSION 3.0 )
PROJECT( opencv-histlib )

FIND_PACKAGE( OpenCV REQUIRED )

INCLUDE_DIRECTORIES( "${PROJECT_SOURCE_DIR}/include" )

ADD_LIBRARY( HistLib src/histLib.cpp )

ADD_EXECUTABLE( sample src/main.cpp )

TARGET_LINK_LIBRARIES( sample HistLib ${OpenCV_LIBS} )
