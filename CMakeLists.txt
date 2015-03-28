cmake_minimum_required (VERSION 2.6)
project (megahttp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost 1.40 COMPONENTS system thread REQUIRED)
find_package(OpenSSL)

add_executable(pion-test src/pion-test.cpp)
target_link_libraries(pion-test pion ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
