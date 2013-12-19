TOOLCHAIN_TARGET_TASK = "packagegroup-qt5-toolchain-target"
TOOLCHAIN_OUTPUTNAME = "${SDK_NAME}-toolchain-qt5-${DISTRO_VERSION}"

require meta-sdk-qt5.bb
require recipes-core/meta/meta-toolchain.bb
