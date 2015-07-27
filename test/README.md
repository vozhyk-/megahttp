megahttp/test
=============

A simple parallel download test. Attempts to download the files in parallel and checks if their sha256sums match the recorded ones.

Usage
-----
```bash
$ cd test
## See "config.sh" for options, can be overridden with environment variables
## Start megahttp:
$ ../bin/megahttp& ## or in another terminal
$ ./test.sh
## Tells whether the test passed and returns 0 in that case.
```

License
-------

These files have been made by [these people](https://anapnea.net/music.php) and are released under the [Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported license](http://creativecommons.org/licenses/by-nc-sa/3.0/):
* `04 Greyhat.mp3`
* `06 Chase.mp3`
* `AlbumArtSmall.jpg`
