#!/bin/bash

USAGE="Usage: `basename $0` [-r] <qt-creator-binary-path> <name> \n Options: \n   -r: Remove the SDK from QtCreator"
removeMode=0;

# Parse command line options.
while getopts rh OPT; do
    case "$OPT" in
        r)
            removeMode=1
            ;;
        h)
            # getopts issues an error message
            echo -e $USAGE >&2
            exit 1
            ;;
    esac
done

# Remove the switches we parsed above.
shift `expr $OPTIND - 1`

# We want at least one non-option argument. 
# Remove this block if you don't need it.
if [ $# -eq 0 ]; then
    echo -e $USAGE >&2
    exit 1
fi

qtCreatorBinPath=$1
name=$2

toolchainId="ProjectExplorer.ToolChain.Gcc:$name";
qtId=$name"_qt";
kitId=$name"_kit";

CUR_DIR=`dirname $0`
source $CUR_DIR/environment-setup-cortexa9-vfp-neon-bistro-linux-gnueabi

abi="arm-linux-generic-elf-32bit"
compiler=`which arm-bistro-linux-gnueabi-g++`
qmake=$OE_QMAKE_QMAKE
gdb=`which arm-bistro-linux-gnueabi-gdb`
sysroot=$SDKTARGETSYSROOT

if [ -z "$sysroot" ]; then
    sysroot=$OECORE_TARGET_SYSROOT
fi

if [ $removeMode -eq 0 ]; then

    $qtCreatorBinPath/sdktool addTC --id "$toolchainId" --name "$name" --abi $abi --path $compiler
    if [ $? -ne 0 ]; then
        echo adding Toolchain failed
        exit 1
    fi
    $qtCreatorBinPath/sdktool addQt --id "$qtId" --name "$name" --type "RemoteLinux.EmbeddedLinuxQt" --qmake $qmake
    if [ $? -ne 0 ]; then
        echo adding Qt failed
        $qtCreatorBinPath/sdktool rmTC --id "$toolchainId"
        exit 1
    fi
    $qtCreatorBinPath/sdktool addKit --id "$kitId" --name "$name" --debuggerengine 1 --debugger $gdb --devicetype GenericLinuxOsType --sysroot $sysroot --toolchain "$toolchainId" --qt "$qtId" --mkspec "linux-oe-sdk-g++"
    if [ $? -ne 0 ]; then
        echo adding Kit failed
        $qtCreatorBinPath/sdktool rmTC --id "$toolchainId"
        $qtCreatorBinPath/sdktool rmQt --id "$qtId"
        exit 1
    fi

else
        $qtCreatorBinPath/sdktool rmTC --id "$toolchainId"
        $qtCreatorBinPath/sdktool rmQt --id "$qtId"
        $qtCreatorBinPath/sdktool rmKit --id "$kitId"
fi
