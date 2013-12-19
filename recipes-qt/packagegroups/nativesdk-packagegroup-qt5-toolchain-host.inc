require recipes-core/packagegroups/nativesdk-packagegroup-sdk-host.bb

DESCRIPTION = "Host packages for Qt5 SDK"
LICENSE = "MIT"

RDEPENDS_${PN} += "nativesdk-qtbase-tools nativesdk-qttools"
