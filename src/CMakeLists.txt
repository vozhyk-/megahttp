set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${megahttp_BINARY_DIR}/bin)

find_package(LibHttpServer)
find_package(PkgConfig)
pkg_check_modules(LIBMEGA libmega REQUIRED)

subdirs(test)


add_executable(megahttp
  main.cpp
  config.cpp
  logging.cpp
  text.cpp
  http_server.cpp
  megahttp_resource.cpp
  login_resource.cpp
  basic_resource.cpp
  mega_client.cpp
  mega_account.cpp
  mega_logger.cpp
  get_public_node_listener.cpp
  file_cache.cpp
  file_cache_item.cpp
  streaming_listener.cpp
  )
set_property(TARGET megahttp PROPERTY CXX_STANDARD 11)
set_property(TARGET megahttp PROPERTY CXX_STANDARD_REQIRED ON)
target_link_libraries(megahttp
  ${LIBHTTPSERVER_LIBRARIES}
  ${LIBMEGA_LIBRARIES}
  )
