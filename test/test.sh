#!/bin/bash

. config.sh

clean_only() {
    rm -rf "$TEST_DIR"/*
}

clean() {
    if [[ "$CLEAN_TEST_DIR" == "yes" ]]; then
	clean_only
    fi
}

mkdir -p "$TEST_DIR"

clean_only

curl "${URL_PREFIX}atMDkbBa!VdDbNEvLtfNBSdd4cBF3sRzg1bGXGMmkKIZx7nyPWc8" > "$TEST_DIR/04 Greyhat.mp3" & pid_1=$!
curl "${URL_PREFIX}6tNTmABa!OtCn0vNcTRT70b9rGZuVnj6QIDKZwspjWZh2W3gIq3I" > "$TEST_DIR/06 Chase.mp3" & pid_2=$!
curl "${URL_PREFIX}G180jAaL!ocIn4YQYB9oxIRvSPKPAByFmgSQfZgzTcGBqJ5jakRk" > "$TEST_DIR/AlbumArtSmall.jpg" & pid_3=$!

if wait $pid_1 && wait $pid_2 && wait $pid_3 && 
   cd "$TEST_DIR" && sha256sum -c "$CHECKSUM"; then
    echo "++++++++++++++++   pass.   ++++++++++++++++"
    clean
    exit 0
else
    echo "- - - - - - - -    FAIL!    - - - - - - - -"
    clean
    exit 1
fi
