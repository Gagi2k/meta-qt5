LICENSE = "MIT"

# Qt4 could NOT be built on MIPS64 with 64 bits userspace
COMPATIBLE_HOST_mips64 = "mips64.*-linux-gnun32"

inherit packagegroup

PACKAGEGROUP_DISABLE_COMPLEMENTARY = "1"

RDEPENDS_${PN} += " \
        packagegroup-core-standalone-sdk-target \
        qtdeclarative-dev \
        qtgraphicaleffects-dev \
        qtmultimedia-dev \
        qtwebkit-dev \
        qtlocation-dev \
        qtquick1-dev \
        qtquickcontrols-dev \
        qt3d-dev \
        qtxmlpatterns-dev \
        qtsensons-dev \
        qtscript-dev \
        qtjsbackend-dev \
        "
