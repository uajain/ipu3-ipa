# Copyright 2019 The Chromium OS Authors. All rights reserved.
# Distributed under the terms of the GNU General Public License v2

EAPI=6

CROS_WORKON_PROJECT="chromiumos/third_party/ipu3-ipa"
CROS_WORKON_INCREMENTAL_BUILD=0

inherit cros-workon meson

DESCRIPTION="Intel IPU3 IPA for CrOS"
HOMEPAGE="https://www.libcamera.org"

LICENSE="LGPL-2.1+"
SLOT="0"
KEYWORDS="~*"
IUSE=""

RDEPEND="
	media-libs/intel-3a-libs-bin
"

DEPEND="
"

src_configure() {
	BUILD_DIR="$(cros-workon_get_build_dir)"

	local emesonargs=(
	)
	meson_src_configure
}

src_compile() {
	meson_src_compile
}

src_install() {
	meson_src_install
}
