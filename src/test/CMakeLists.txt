pkg_check_modules(LIBMICROHTTPD libmicrohttpd REQUIRED)

add_custom_target(tests DEPENDS cat-server mhd-chunked-test mega-test)

add_executable(cat-server EXCLUDE_FROM_ALL cat-server.cpp)
target_link_libraries(cat-server ${LIBHTTPSERVER_LIBRARIES})

add_executable(mhd-chunked-test EXCLUDE_FROM_ALL mhd-chunked-test.c)
target_link_libraries(mhd-chunked-test ${LIBMICROHTTPD_LIBRARIES})

add_executable(mega-test EXCLUDE_FROM_ALL mega-test.cpp)
target_link_libraries(mega-test ${LIBMEGA_LIBRARIES})
