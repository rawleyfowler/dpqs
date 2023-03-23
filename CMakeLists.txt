cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

project(dpqs VERSION 1.0.0 DESCRIPTION "A Dual Pivot Quicksort Implementation")
add_library(dpqs SHARED dpqs.c)
find_library(MATH m REQUIRED)
target_link_libraries(dpqs INTERFACE ${MATH})
set_target_properties(dpqs PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(dpqs PROPERTIES PUBLIC_HEADER dpqs.h)
set_target_properties(dpqs PROPERTIES SOVERSION 1)
target_include_directories(dpqs PRIVATE .)
install(TARGETS dpqs
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
