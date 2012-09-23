cmake_minimum_required ( VERSION 2.6 )
PROJECT( opencv-histlib )
FIND_PACKAGE( OpenCV REQUIRED )

ADD_LIBRARY( HistLib src/histLib.cpp )

ADD_EXECUTABLE( sample src/main.cpp )

include_directories( "${PROJECT_SOURCE_DIR}/include" )

TARGET_LINK_LIBRARIES( sample HistLib ${OpenCV_LIBS} )
