#!/bin/bash

TEST_DIR=${TEST_DIR:-"/tmp/megahttp-test"}
URL_PREFIX=${URL_PREFIX:-"http://localhost:8080/public?url=https%3A%2F%2Fmega.co.nz%2F%23!"}
CLEAN_TEST_DIR=${CLEAN_TEST_DIR:-no} # if "yes", removes $TEST_DIR's contents after testing

CHECKSUM=${CHECKSUM:-$(realpath "Anapnea-album-part.sha256sum")}
