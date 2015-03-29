cmake_minimum_required (VERSION 2.6)
project (megahttp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#find_package(Boost 1.40 COMPONENTS system filesystem thread REQUIRED)
#find_package(OpenSSL)
find_package(LibHttpServer)
find_package(PkgConfig)
pkg_check_modules(LIBMEGA libmega REQUIRED)

add_executable(cat-server src/cat-server.cpp)
target_link_libraries(cat-server ${LIBHTTPSERVER_LIBRARIES})
add_executable(mega-test src/mega-test.cpp)
target_link_libraries(mega-test ${LIBMEGA_LIBRARIES})
