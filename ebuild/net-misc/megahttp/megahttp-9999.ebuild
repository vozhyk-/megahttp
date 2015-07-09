# Copyright 2015 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI="4"

inherit cmake-utils git-r3

DESCRIPTION="HTTP server that streams files from mega.co.nz cloud storage"
HOMEPAGE="http://github.com/vozhyk-/megahttp"
EGIT_REPO_URI="git://github.com/vozhyk-/megahttp"

LICENSE="BSD-2"
SLOT="0"
KEYWORDS="~amd64"
IUSE="debug"

RDEPEND=">net-misc/mega-sdk-2.5.0
         net-libs/libhttpserver"
DEPEND="${RDEPEND}"

src_install() {
    cmake-utils_src_install

    dodoc doc/README.md
}
