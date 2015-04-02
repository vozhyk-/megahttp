set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${megahttp_BINARY_DIR}/bin)

find_package(LibHttpServer)
find_package(PkgConfig)
pkg_check_modules(LIBMEGA libmega REQUIRED)

add_executable(cat-server cat-server.cpp)
target_link_libraries(cat-server ${LIBHTTPSERVER_LIBRARIES})

add_executable(mega-test mega-test.cpp)
target_link_libraries(mega-test ${LIBMEGA_LIBRARIES})

add_executable(megahttp
  main.cpp
  http_server.cpp
  megahttp_resource.cpp
  chunked_test_resource.cpp
  mega_client.cpp
  get_public_node_listener.cpp
  transfer_listener.cpp
  )
set_property(TARGET megahttp PROPERTY CXX_STANDARD 11)
set_property(TARGET megahttp PROPERTY CXX_STANDARD_REQIRED ON)
target_link_libraries(megahttp
  ${LIBHTTPSERVER_LIBRARIES}
  ${LIBMEGA_LIBRARIES}
  )
