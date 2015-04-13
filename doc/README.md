megahttp
========
HTTP server that streams files from mega.co.nz cloud storage

Building
--------
```bash
cmake .
make
make doc # If you want to generate documentation for the source with doxygen
make tests # If you want to build some tests of the libraries used
```

Usage
-----
Start the server with
```bash
bin/megahttp
```
Then point a browser or any other HTTP client to
```
http://localhost:8080/?url=MEGA_URL
```
where MEGA_URL is a public link to a file in MEGA (with the key built-in).

Logs are written to `megahttp.log` in the current directory by default.

Configuration
-------------
See `src/config.cpp`

Dependencies
------------

* [CMake](http://www.cmake.org/) - build system
* [libhttpserver](https://github.com/etr/libhttpserver) - HTTP server library
* [MEGA SDK](https://github.com/meganz/sdk) - MEGA client library
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) (optional) - tool for
generating documentation
