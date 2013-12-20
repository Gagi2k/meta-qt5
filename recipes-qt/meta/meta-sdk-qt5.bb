DESCRIPTION = "Meta package for creating all tools and scripts needed in a qt5 sdk"
LICENSE = "MIT"

TOOLCHAIN_HOST_TASK = "nativesdk-packagegroup-qt5-toolchain-host packagegroup-cross-canadian-${MACHINE}"

inherit qmake5_paths

QT_TOOLS_PREFIX = "${SDKPATHNATIVE}${bindir_nativesdk}"

# we don't want conflicts with qt4
OE_QMAKE_PATH_HEADERS = "${OE_QMAKE_PATH_QT_HEADERS}"
OE_QMAKE_PATH_ARCHDATA = "${OE_QMAKE_PATH_QT_ARCHDATA}"
OE_QMAKE_PATH_DATA = "${OE_QMAKE_PATH_QT_DATA}"
OE_QMAKE_PATH_BINS = "${OE_QMAKE_PATH_QT_BINS}"
OE_QMAKE_PATH_TRANSLATIONS = "${OE_QMAKE_PATH_QT_TRANSLATIONS}"
OE_QMAKE_PATH_DOCS = "${OE_QMAKE_PATH_QT_DOCS}"
OE_QMAKE_PATH_SETTINGS = "${OE_QMAKE_PATH_QT_SETTINGS}"
OE_QMAKE_PATH_EXAMPLES = "${OE_QMAKE_PATH_QT_EXAMPLES}"
OE_QMAKE_PATH_TESTS = "${OE_QMAKE_PATH_QT_TESTS}"

SHELLSCRIPTPATH := "${FILE_DIRNAME}/${PN}"
QTCREATORSCRIPT = "qtCreatorConfig.sh"
QTCREATORSCRIPTPATH = "${SDK_OUTPUT}/${SDKPATH}/${QTCREATORSCRIPT}"

toolchain_create_sdk_env_script_append() {
    echo 'export OE_QMAKE_CFLAGS="$CFLAGS"' >> $script
    echo 'export OE_QMAKE_CXXFLAGS="$CXXFLAGS"' >> $script
    echo 'export OE_QMAKE_LDFLAGS="$LDFLAGS"' >> $script
    echo 'export OE_QMAKE_CC=$CC' >> $script
    echo 'export OE_QMAKE_CXX=$CXX' >> $script
    echo 'export OE_QMAKE_LINK=$CXX' >> $script
    echo 'export OE_QMAKE_AR=$AR' >> $script
    echo 'export OE_QMAKE_LIBDIR_QT=${SDKTARGETSYSROOT}/${libdir}' >> $script
    echo 'export OE_QMAKE_INCDIR_QT=${SDKTARGETSYSROOT}/${includedir}/${QT_DIR_NAME}' >> $script
    echo 'export OE_QMAKE_MOC=${QT_TOOLS_PREFIX}/moc4' >> $script
    echo 'export OE_QMAKE_UIC=${QT_TOOLS_PREFIX}/uic4' >> $script
    echo 'export OE_QMAKE_UIC3=${QT_TOOLS_PREFIX}/uic34' >> $script
    echo 'export OE_QMAKE_RCC=${QT_TOOLS_PREFIX}/rcc4' >> $script
    echo 'export OE_QMAKE_QMAKE=${SDKPATHNATIVE}/${OE_QMAKE_PATH_QT_BINS}/qmake' >> $script
    echo 'export OE_QMAKE_QDBUSCPP2XML=${QT_TOOLS_PREFIX}/qdbuscpp2xml4' >> $script
    echo 'export OE_QMAKE_QDBUSXML2CPP=${QT_TOOLS_PREFIX}/qdbusxml2cpp4' >> $script
    echo 'export OE_QMAKE_QT_CONFIG=${SDKTARGETSYSROOT}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs/qconfig.pri' >> $script
    echo 'export QMAKESPEC=linux-oe-g++' >> $script
    echo 'export QT_CONF_PATH=${SDKPATHNATIVE}/${OE_QMAKE_PATH_QT_BINS}/qt.conf' >> $script

    # make a symbolic link to mkspecs for compatibility with Nokia's SDK
    # and QTCreator
    mkdir -p ${SDK_OUTPUT}/${SDKPATHNATIVE}/${OE_QMAKE_PATH_ARCHDATA};
    (cd ${SDK_OUTPUT}/${SDKPATHNATIVE}/${OE_QMAKE_PATH_ARCHDATA}; ln -s ${SDKTARGETSYSROOT}/${OE_QMAKE_PATH_ARCHDATA}/mkspecs mkspecs;)

    cat > ${SDK_OUTPUT}/${SDKPATHNATIVE}/${OE_QMAKE_PATH_QT_BINS}/qt.conf <<EOF
[Paths]
Sysroot = ../../../../${REAL_MULTIMACH_TARGET_SYS}/
Prefix = ${OE_QMAKE_PATH_PREFIX}
Headers = ${OE_QMAKE_PATH_HEADERS}
Libraries = ${OE_QMAKE_PATH_LIBS}
ArchData = ${OE_QMAKE_PATH_ARCHDATA}
Data = ${OE_QMAKE_PATH_DATA}
Binaries = ${OE_QMAKE_PATH_BINS}
LibraryExecutables = ${OE_QMAKE_PATH_LIBEXECS}
Plugins = ${OE_QMAKE_PATH_PLUGINS}
Imports = ${OE_QMAKE_PATH_IMPORTS}
Qml2Imports = ${OE_QMAKE_PATH_QML}
Translations = ${OE_QMAKE_PATH_TRANSLATIONS}
Documentation = ${OE_QMAKE_PATH_DOCS}
Settings = ${OE_QMAKE_PATH_SETTINGS}
Examples = ${OE_QMAKE_PATH_EXAMPLES}
Tests = ${OE_QMAKE_PATH_TESTS}
HostPrefix = ../../..
HostBinaries = ${@'${OE_QMAKE_PATH_HOST_BINS}'.strip("/")}
HostData = ${@'${OE_QMAKE_PATH_ARCHDATA}'.strip("/")}
HostLibraries = ${@'${OE_QMAKE_PATH_LIBS}'.strip("/")}
HostSpec = linux-oe-sdk-g++
TargetSpec = linux-oe-sdk-g++
EOF

    cp ${SHELLSCRIPTPATH}/${QTCREATORSCRIPT} ${QTCREATORSCRIPTPATH}
}
