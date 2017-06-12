set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${megahttp_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(LibHttpServer REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMEGA libmega REQUIRED)

subdirs(test)


add_executable(megahttp
  main.cpp
  config.cpp
  logging.cpp
  logging_utils.cpp
  text.cpp
  http_server.cpp
  http_utils.cpp
  public_files_resource.cpp
  account_files_resource.cpp
  login_resource.cpp
  status_resource.cpp
  mega_client.cpp
  mega_account.cpp
  mega_logger.cpp
  get_public_node_listener.cpp
  file_cache.cpp
  file_cache_item.cpp
  file_buffer.cpp
  download_listener.cpp
  streaming_response.cpp
  )
set_property(TARGET megahttp PROPERTY CXX_STANDARD 11)
set_property(TARGET megahttp PROPERTY CXX_STANDARD_REQIRED ON)
target_link_libraries(megahttp
  ${LIBHTTPSERVER_LIBRARIES}
  ${LIBMEGA_LIBRARIES}
  )


install(TARGETS megahttp
  RUNTIME DESTINATION bin)
