# Interactive helpers for Android kernel development
# Copyright (C) 2019 Danny Lin <danny@kdrag0n.dev>
# Copyright (C) 2019 kingbri <bdashore3@gmail.com>
# Copyright (C) 2019 celtare21 <celtare21@gmail.com>
#
# This script must be *sourced* from a Bourne-compatible shell in order to
# function. Nothing will happen if you execute it.
#
# Source a compiler-specific setup script for proper functionality. This is
# only a base script and does not suffice for kernel building without the
# flags that compiler-specific scripts append to kmake_flags.
#


#### CONFIGURATION ####

# Kernel name
kernel_name="Artemis"

# Defconfig name
defconfig="artemis_coral_defconfig"

# Target architecture
arch="arm64"

# Base kernel compile flags (extended by compiler setup script)
kmake_flags=(
	-j"$(nproc --all)"
	ARCH="$arch"
	O="out"
)

# Target device name to use in flashable package names
device_name="coral"

# Initialize kernel
function init_kernel() {
    git submodule update --init
}
# Reset the current config to the committed defconfig
function mc() {
	kmake "$defconfig"
}

# Open an interactive config editor
function cf() {
	kmake nconfig
}

# Edit the raw text config
function ec() {
	"${EDITOR:-vim}" "$kroot/out/.config"
}

# Get kernel repository root for later use
kroot="$PWD/$(dirname "$0")"

# Show an informational message
function msg() {
    echo -e "\e[1;32m$1\e[0m"
}

# Go to the root of the kernel repository repository
function croot() {
	cd "$kroot"
}

# Get the version of Clang in an user-friendly form
function get_clang_version() {
	"$1" --version | head -n 1 | perl -pe 's/\((?:http|git).*?\)//gs' | sed -e 's/  */ /g' -e 's/[[:space:]]*$//' -e 's/^.*clang/clang/'
}

# Get the version of GCC in an user-friendly form
function get_gcc_version() {
	"$1" --version | head -n 1 | cut -d'(' -f2 | tr -d ')' | sed -e 's/[[:space:]]*$//'
}


#### COMPILATION ####

# Make wrapper for kernel compilation
function kmake() {
	make "${kmake_flags[@]}" "$@"
}

# Create a zipfile
function mkzip() {
    echo "Removing old kernel files"
    echo " "
    rm -rf flasher/kernel
    rm -rf flasher/dtbs
    mkdir flasher/kernel
    mkdir flasher/dtbs
    echo "Copying new kernel files"
    echo " "
    cp out/arch/arm64/boot/Image.lz4 flasher/kernel/Image.lz4
    cp -r out/arch/arm64/boot/dts/google/qcom-base/* flasher/dtbs
    read -p 'Version number: ' version
    zipname="Artemis_coral_v$version.zip"
    echo " "
    cd flasher
    echo "Creating zipfile with name $zipname, please wait..."
    zip -r "$zipname" *
    cd ../
    mkdir -p out/flasher
    mv flasher/$zipname out/flasher/$zipname
    echo "Zip successfuly created"
    echo " "
    echo "Your zip is stored in out/flasher/$zipname"
}

