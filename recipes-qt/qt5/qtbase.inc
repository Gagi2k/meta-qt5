require qt5.inc

SRC_URI += " \
    file://0001-Add-linux-oe-g-platform.patch \
    file://0002-qlibraryinfo-allow-to-set-qt.conf-from-the-outside-u.patch \
    file://0003-Add-external-hostbindir-option.patch \
    file://0004-qt_functions-temporary-remove-isEmpty-check.patch \
    file://0005-qmake-is-already-built-in-qtbase-native.patch \
    file://0006-Allow-building-a-separate-qmake-for-the-target.patch \
    file://0007-configureapp-Prefix-default-LIBDIRS-and-INCDIRS-with.patch \
    file://0008-qt_module-Fix-pkgconfig-replacement.patch \
    file://0009-qt_module-Fix-paths-in-.prl-files.patch \
    file://0010-wayland-scanner-disable-silent-rules.patch \
    file://0011-configure-don-t-export-SYSTEM_VARIABLES-to-.qmake.va.patch \
    file://0012-configure.prf-Allow-to-add-extra-arguments-to-make.patch \
    file://0013-Disable-mkv8snapshot.patch \
    file://0014-enables-tslib-device-to-be-read-from-env-variable.patch \
    file://0015-qtbase-allow-build-of-examples.patch \
    file://0018-QOpenGLPaintDevice-sub-area-support.patch \
    file://0020-Use-BGRA-extension-in-bindTexture.patch \
    file://0021-configure-make-pulseaudio-a-configurable-option.patch \
    file://0022-configure-make-alsa-a-configurable-option.patch \
    file://0023-configure-make-freetype-a-configurable-option.patch \
    file://0024-Use-OE_QMAKE_PATH_EXTERNAL_HOST_BINS-to-determine-pa.patch \
    file://0026-Ensure-lastPixel.y-is-also-initalized-to-1-when-nece.patch \
    file://0027-Fix-misaligned-selection-region-with-text-when-cente.patch \
"

DEPENDS += "qtbase-native"

# for syncqt
RDEPENDS_${PN}-tools += "perl"

# separate some parts of PACKAGECONFIG which are often changed
# be aware that you need to add icu to build qtwebkit, default
# PACKAGECONFIG is kept rather minimal for people who don't need
# stuff like webkit (and it's easier to add options than remove)

# gl or gles needs to be enabled in order to build qtdeclarative
# http://qt.gitorious.org/qt/qtdeclarative/commit/e988998a08b1420ed10bd02d9d4b3b8ed2289df9
PACKAGECONFIG_GL ?= "${@base_contains('DISTRO_FEATURES', 'opengl', 'gl', '', d)}"
PACKAGECONFIG_FB ?= "${@base_contains('DISTRO_FEATURES', 'directfb', 'directfb', '', d)}"
PACKAGECONFIG_X11 ?= "${@base_contains('DISTRO_FEATURES', 'x11', 'xcb xvideo xsync xshape xrender xrandr xfixes xinput2 xinput xinerama xcursor gtkstyle', '', d)}"
PACKAGECONFIG_FONTS ?= ""
PACKAGECONFIG_SYSTEM ?= "jpeg libpng zlib"
PACKAGECONFIG_MULTIMEDIA ?= "${@base_contains('DISTRO_FEATURES', 'pulseaudio', 'pulseaudio', '', d)}"
PACKAGECONFIG_DISTRO ?= ""

PACKAGECONFIG ??= " \
    release \
    dbus \
    udev \
    evdev \
    widgets \
    openssl \
    ${PACKAGECONFIG_GL} \
    ${PACKAGECONFIG_FB} \
    ${PACKAGECONFIG_X11} \
    ${PACKAGECONFIG_FONTS} \
    ${PACKAGECONFIG_SYSTEM} \
    ${PACKAGECONFIG_MULTIMEDIA} \
    ${PACKAGECONFIG_DISTRO} \
"

PACKAGECONFIG[release] = "-release,-debug"
PACKAGECONFIG[sm] = "-sm,-no-sm"
PACKAGECONFIG[tests] = ",-nomake tests"
PACKAGECONFIG[examples] = ",-nomake examples"
# accessibility is required to compile qtquickcontrols
PACKAGECONFIG[accessibility] = "-accessibility,-no-accessibility"
PACKAGECONFIG[glib] = "-glib,-no-glib,glib-2.0"
# use either system freetype or bundled freetype, if you disable freetype completely
# fontdatabases/basic/qbasicfontdatabase.cpp will fail to build and system freetype
# works only together with fontconfig
PACKAGECONFIG[freetype] = "-system-freetype,-freetype,freetype"
PACKAGECONFIG[jpeg] = "-system-libjpeg,-no-libjpeg,jpeg"
PACKAGECONFIG[libpng] = "-system-libpng,-no-libpng,libpng"
PACKAGECONFIG[zlib] = "-system-zlib,-qt-zlib,zlib"
PACKAGECONFIG[pcre] = "-system-pcre,-qt-pcre,pcre"
# gl or gles2 is needed in order to build qtdeclarative (qtdeclarative.do_configure fails to find quick module without)
PACKAGECONFIG[gl] = "-opengl desktop -no-eglfs,,virtual/libgl"
PACKAGECONFIG[gles2] = "-opengl es2 -eglfs,,virtual/libgles2 virtual/egl"
PACKAGECONFIG[tslib] = "-tslib,-no-tslib,tslib"
PACKAGECONFIG[dbus] = "-dbus,-no-dbus,dbus"
PACKAGECONFIG[xcb] = "-xcb,-no-xcb,xcb-util-wm xcb-util-image xcb-util-keysyms"
PACKAGECONFIG[sql-ibase] = "-sql-ibase,-no-sql-ibase"
PACKAGECONFIG[sql-mysql] = "-sql-mysql,-no-sql-mysql,mysql"
PACKAGECONFIG[sql-psql] = "-sql-psql,-no-sql-psql,postgresql"
PACKAGECONFIG[sql-odbc] = "-sql-odbc,-no-sql-odbc"
PACKAGECONFIG[sql-oci] = "-sql-oci,-no-sql-oci"
PACKAGECONFIG[sql-tds] = "-sql-tds,-no-sql-tds"
PACKAGECONFIG[sql-db2] = "-sql-db2,-no-sql-db2"
PACKAGECONFIG[sql-sqlite2] = "-sql-sqlite2,-no-sql-sqlite2,sqlite"
PACKAGECONFIG[sql-sqlite] = "-sql-sqlite,-no-sql-sqlite,sqlite3"
PACKAGECONFIG[xcursor] = "-xcursor,-no-xcursor,libxcursor"
PACKAGECONFIG[xinerama] = "-xinerama,-no-xinerama,libxinerama"
PACKAGECONFIG[xinput] = "-xinput,-no-xinput"
PACKAGECONFIG[xinput2] = "-xinput2,-no-xinput2"
PACKAGECONFIG[xfixes] = "-xfixes,-no-xfixes,libxfixes"
PACKAGECONFIG[xrandr] = "-xrandr,-no-xrandr,libxrandr"
PACKAGECONFIG[xrender] = "-xrender,-no-xrender,libxrender"
PACKAGECONFIG[xshape] = "-xshape,-no-xshape"
PACKAGECONFIG[xsync] = "-xsync,-no-xsync"
PACKAGECONFIG[xvideo] = "-xvideo,-no-xvideo"
PACKAGECONFIG[openvg] = "-openvg,-no-openvg"
PACKAGECONFIG[iconv] = "-iconv,-no-iconv,virtual/libiconv"
PACKAGECONFIG[xkb] = "-xkb,-no-xkb,libxkbcommon"
PACKAGECONFIG[evdev] = "-evdev,-no-evdev"
# depends on glib
PACKAGECONFIG[gstreamer] = "-gstreamer,-no-gstreamer,gstreamer"
PACKAGECONFIG[fontconfig] = "-fontconfig,-no-fontconfig,fontconfig"
PACKAGECONFIG[gtkstyle] = "-gtkstyle,-no-gtkstyle,gtk+"
PACKAGECONFIG[directfb] = "-directfb,-no-directfb,directfb"
PACKAGECONFIG[linuxfb] = "-linuxfb,-no-linuxfb"
PACKAGECONFIG[mitshm] = "-mitshm,-no-mitshm,mitshm"
PACKAGECONFIG[kms] = "-kms,-no-kms,kms"
# needed for qtdeclarative (qtdeclarative.do_configure fails to find quick module without)
PACKAGECONFIG[icu] = "-icu,-no-icu,${ICU}"
PACKAGECONFIG[udev] = "-libudev,-no-libudev,udev"
PACKAGECONFIG[openssl] = "-openssl,-no-openssl,openssl"
PACKAGECONFIG[alsa] = "-alsa,-no-alsa,alsa-lib"
PACKAGECONFIG[pulseaudio] = "-pulseaudio,-no-pulseaudio,pulseaudio"
PACKAGECONFIG[nis] = "-nis,-no-nis"
PACKAGECONFIG[widgets] = "-widgets,-no-widgets"

ALTERNATIVE_qtbase-tools = "moc qdbuscpp2xml qdbusxml2cpp qdoc rcc uic"
ALTERNATIVE_TARGET[moc] = "${OE_QMAKE_PATH_BINS}/moc"
ALTERNATIVE_TARGET[qdbuscpp2xml] = "${OE_QMAKE_PATH_BINS}/qdbuscpp2xml"
ALTERNATIVE_TARGET[qdbusxml2cpp] = "${OE_QMAKE_PATH_BINS}/qdbusxml2cpp"
ALTERNATIVE_TARGET[qdoc] = "${OE_QMAKE_PATH_BINS}/qdoc"
ALTERNATIVE_TARGET[rcc] = "${OE_QMAKE_PATH_BINS}/rcc"
ALTERNATIVE_TARGET[uic] = "${OE_QMAKE_PATH_BINS}/uic"

QT_CONFIG_FLAGS += " \
    -reduce-relocations \
    -shared \
    -silent \
    -no-pch \
    -no-rpath \
    -pkg-config \
    ${EXTRA_OECONF} \
"

# Qt uses atomic instructions not supported in thumb mode
ARM_INSTRUCTION_SET = "arm"

do_generate_qt_config_file_append() {
    cat >> ${QT_CONF_PATH} <<EOF

[EffectivePaths]
Prefix=..
EOF
}

# qtbase is exception, we need to use mkspecs from ${S}
QMAKE_MKSPEC_PATH = "${B}"

# another exception is that we need to run bin/qmake, because EffectivePaths are relative to qmake location
OE_QMAKE_QMAKE_ORIG = "${STAGING_BINDIR_NATIVE}/${QT_DIR_NAME}/qmake"
OE_QMAKE_QMAKE = "bin/qmake"

# qtbase is exception, configure script is using our get(X)QEvalMakeConf and setBootstrapEvalVariable functions to read it from shell
export OE_QMAKE_COMPILER
export OE_QMAKE_CC
export OE_QMAKE_CFLAGS
export OE_QMAKE_CXX
export OE_QMAKE_CXXFLAGS
export OE_QMAKE_LINK
export OE_QMAKE_LDFLAGS
export OE_QMAKE_AR
export OE_QMAKE_STRIP

do_configure() {
    # we need symlink in path relative to source, because
    # EffectivePaths:Prefix is relative to qmake location
    if [ ! -e ${B}/bin/qmake ]; then
        mkdir ${B}/bin
        ln -sf ${OE_QMAKE_QMAKE_ORIG} ${B}/bin/qmake
    fi

    ${S}/configure -v \
        -dont-process \
        -opensource -confirm-license \
        -sysroot ${STAGING_DIR_TARGET} \
        -no-gcc-sysroot \
        -prefix ${OE_QMAKE_PATH_PREFIX} \
        -bindir ${OE_QMAKE_PATH_BINS} \
        -libdir ${OE_QMAKE_PATH_LIBS} \
        -datadir ${OE_QMAKE_PATH_DATA} \
        -sysconfdir ${OE_QMAKE_PATH_SETTINGS} \
        -docdir ${OE_QMAKE_PATH_DOCS} \
        -headerdir ${OE_QMAKE_PATH_HEADERS} \
        -archdatadir ${OE_QMAKE_PATH_ARCHDATA} \
        -libexecdir ${OE_QMAKE_PATH_LIBEXECS} \
        -plugindir ${OE_QMAKE_PATH_PLUGINS} \
        -importdir ${OE_QMAKE_PATH_IMPORTS} \
        -qmldir ${OE_QMAKE_PATH_QML} \
        -translationdir ${OE_QMAKE_PATH_TRANSLATIONS} \
        -testsdir ${OE_QMAKE_PATH_TESTS} \
        -examplesdir ${OE_QMAKE_PATH_EXAMPLES} \
        -hostbindir ${OE_QMAKE_PATH_HOST_BINS} \
        -hostdatadir ${OE_QMAKE_PATH_HOST_DATA} \
        -external-hostbindir ${OE_QMAKE_PATH_EXTERNAL_HOST_BINS} \
        -platform ${OE_QMAKESPEC} \
        -xplatform linux-oe-g++ \
        ${QT_CONFIG_FLAGS}

    qmake5_base_do_configure
}

do_compile_append() {
    # Build qmake for the target arch
    # Disable for now, because doesn't work well with separate ${B}
    # cp -ra ${S}/qmake ${B}
    # cd ${B}/qmake
    # ${OE_QMAKE_QMAKE}
    # Fix to use headers in ${B}
    # sed '/INCPATH/s#${S}#${B}#g' -i Makefile
    # oe_runmake CC="${CC}" CXX="${CXX}"
    # cd ${B}
}

do_install_append() {
    ### Fix up the binaries to the right location
    ### TODO: FIX
    # qemu built on host breaks do_package, remove it here (will be replaces with right qemu when do_compile is fixed
    # ERROR: objcopy failed with exit code 1 (cmd was 'arm-oe-linux-gnueabi-objcopy' --only-keep-debug '/OE/oe-core/tmp-eglibc/work/armv5te-oe-linux-gnueabi/qtbase/5.0.1-r0.0/package/usr/bin/qmake' '/OE/oe-core/tmp-eglibc/work/armv5te-oe-linux-gnueabi/qtbase/5.0.1-r0.0/package/usr/bin/.debug/qmake')
    rm -f ${D}/${bindir}/${QT_DIR_NAME}/qmake
    # install fonts manually if they are missing
    if [ ! -d ${D}/${OE_QMAKE_PATH_LIBS}/fonts ]; then
        cp -a ${S}/lib/fonts ${D}/${OE_QMAKE_PATH_LIBS}
    fi

# TODO: Don't hardcode the relative paths, caluculate it somehow from OE_QMAKE_PATH_ARCHDATA
sed -i "s,${STAGING_DIR_TARGET},\$\$PWD/../../../../,g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/qconfig.pri
sed -i "s,${STAGING_DIR_NATIVE},\$\$PWD/../../../../../${SDK_SYS},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/qconfig.pri
sed -i "s,QT_HOST_ARCH = ${TARGET_ARCH},QT_HOST_ARCH = ${SDK_ARCH},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/qconfig.pri

sed -i "s,${STAGING_DIR_TARGET},\$\$PWD/../../../../,g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/qmodule.pri
sed -i "s,${STAGING_DIR_NATIVE},\$\$PWD/../../../../../${SDK_SYS},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/qconfig.pri

cat >> ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/qconfig.pri << EOF
QMAKE_CFLAGS += --sysroot=\$\$[QT_SYSROOT]
QMAKE_CXXFLAGS += --sysroot=\$\$[QT_SYSROOT]
QMAKE_LFLAGS += --sysroot=\$\$[QT_SYSROOT]
EOF

cat > ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/qdevice.pri << EOF
CROSS_COMPILE = \$\$PWD/../../../../../${SDK_SYS}/usr/bin/${TARGET_SYS}/${TARGET_SYS}-
GCC_MACHINE_DUMP = ${TARGET_SYS}
EOF


cp -rf ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-g++ ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/

# Fix the linux-oe-sdk-g++ mkspec to use the real values and not the environment variables
# We don't want to have the --sysroot in the mkspec itself, it should be set in the qconfig.pri to be able to change it via qt.conf and also make it possible to use other mkspecs
sed -i "s,\$(OE_QMAKE_AR),\$\$PWD/../../../../../../${SDK_SYS}/usr/bin/${TARGET_SYS}/${OE_QMAKE_AR},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s,\$(OE_QMAKE_STRIP),\$\$PWD/../../../../../../${SDK_SYS}/usr/bin/${TARGET_SYS}/${STRIP},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s,\$(OE_QMAKE_WAYLAND_SCANNER),\$\$PWD/../../../../../${@'${OE_QMAKE_WAYLAND_SCANNER}'.replace('${STAGING_DIR_NATIVE}','')},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s#\$(OE_QMAKE_CFLAGS)#${OE_QMAKE_CFLAGS}#g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s#\$(OE_QMAKE_CXXFLAGS)#${OE_QMAKE_CXXFLAGS}#g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s#\$(OE_QMAKE_LDFLAGS)#${OE_QMAKE_LDFLAGS}#g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s,\$(OE_QMAKE_COMPILER),\$\$PWD/../../../../../../${SDK_SYS}/usr/bin/${TARGET_SYS}/${@'${OE_QMAKE_COMPILER}'.replace('--sysroot=${STAGING_DIR_TARGET}','')},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s,\$(OE_QMAKE_CC),\$\$PWD/../../../../../../${SDK_SYS}/usr/bin/${TARGET_SYS}/${@'${OE_QMAKE_CC}'.replace('--sysroot=${STAGING_DIR_TARGET}','')},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s,\$(OE_QMAKE_CXX),\$\$PWD/../../../../../../${SDK_SYS}/usr/bin/${TARGET_SYS}/${@'${OE_QMAKE_CXX}'.replace('--sysroot=${STAGING_DIR_TARGET}','')},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s,\$(OE_QMAKE_LINK),\$\$PWD/../../../../../../${SDK_SYS}/usr/bin/${TARGET_SYS}/${@'${OE_QMAKE_LINK}'.replace('--sysroot=${STAGING_DIR_TARGET}','')},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf
sed -i "s,\$(OE_QMAKE_QT_CONFIG),${OE_QMAKE_QT_CONFIG},g" ${D}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/linux-oe-sdk-g++/qmake.conf

}

PACKAGES =. " \
    ${PN}-fonts \
    ${PN}-fonts-ttf-vera \
    ${PN}-fonts-ttf-dejavu \
    ${PN}-fonts-pfa \
    ${PN}-fonts-pfb \
    ${PN}-fonts-qpf \
"

RRECOMMENDS_${PN}-fonts = " \
    ${PN}-fonts-ttf-vera \
    ${PN}-fonts-ttf-dejavu \
    ${PN}-fonts-pfa \
    ${PN}-fonts-pfb \
    ${PN}-fonts-qpf \
"

ALLOW_EMPTY_${PN}-fonts = "1"

FILES_${PN}-fonts-ttf-vera       = "${OE_QMAKE_PATH_LIBS}/fonts/Vera*.ttf"
FILES_${PN}-fonts-ttf-dejavu     = "${OE_QMAKE_PATH_LIBS}/fonts/DejaVu*.ttf"
FILES_${PN}-fonts-pfa            = "${OE_QMAKE_PATH_LIBS}/fonts/*.pfa"
FILES_${PN}-fonts-pfb            = "${OE_QMAKE_PATH_LIBS}/fonts/*.pfb"
FILES_${PN}-fonts-qpf            = "${OE_QMAKE_PATH_LIBS}/fonts/*.qpf*"
FILES_${PN}-fonts                = "${OE_QMAKE_PATH_LIBS}/fonts/README \
                                    ${OE_QMAKE_PATH_LIBS}/fonts/fontdir"
