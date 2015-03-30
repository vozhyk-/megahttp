megahttp
========
HTTP server that streams files from mega.co.nz cloud storage

Building
--------
```bash
cmake .
make
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

Dependencies
------------

* [CMake](http://www.cmake.org/) - build system
* [libhttpserver](https://github.com/etr/libhttpserver) - HTTP server library
* [MEGA SDK](https://github.com/meganz/sdk) - MEGA client library
