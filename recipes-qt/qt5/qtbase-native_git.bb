require qt5-git.inc
require ${PN}.inc

# common with target version
SRC_URI = "\
    git://qt.gitorious.org/qt/${QT_MODULE}.git;branch=${QT_MODULE_BRANCH} \
    file://0001-Add-linux-oe-g-platform.patch \
    file://0002-qlibraryinfo-allow-to-set-qt.conf-from-the-outside-u.patch \
    file://0003-Add-external-hostbindir-option.patch \
    file://0004-qt_functions-temporary-remove-isEmpty-check.patch \
    file://0005-configureapp-Prefix-default-LIBDIRS-and-INCDIRS-with.patch \
    file://0006-qt_module-Fix-pkgconfig-replacement.patch \
    file://0007-qt_module-Fix-paths-in-.prl-files.patch \
    file://0008-wayland-scanner-disable-silent-rules.patch \
    file://0009-configure-don-t-export-SYSTEM_VARIABLES-to-.qmake.va.patch \
    file://0010-configure.prf-Allow-to-add-extra-arguments-to-make.patch \
    file://0011-configure-make-pulseaudio-a-configurable-option.patch \
    file://0012-configure-make-alsa-a-configurable-option.patch \
    file://0013-configure-make-freetype-a-configurable-option.patch \
    file://0014-Use-OE_QMAKE_PATH_EXTERNAL_HOST_BINS-to-determine-pa.patch \
"

do_install_append() {
    # for modules which are still using syncqt and call qtPrepareTool(QMAKE_SYNCQT, syncqt)
    # e.g. qt3d, qtwayland
    ln -sf syncqt.pl ${D}${OE_QMAKE_PATH_QT_BINS}/syncqt
}

SRCREV = "690cf426f3a8c18d903e61228f65fa3b9e2a69d3"
