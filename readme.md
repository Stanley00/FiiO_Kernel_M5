'uboot-tools' package provides 'mkimage' utility. I use 2020.10 version.
Outdated prebuilded tools form Ingenic placed on 'tools/host'

0. Grab mips-gcc472-glibc216 toolchain
https://github.com/Ozzyminted/ingenic-toolchains
and place the content to 'tools/toolchains/mips-gcc472-glibc216'

1. Set PATH to MIPS GCC toolchain

  TOOLCHAINS="../tools/toolchains/mips-gcc472-glibc216/bin"
  
  export PATH=$TOOLCHAINS:$PATH

and if you need set path to image build utilities (mkimage, mkfs.ubifs, etc)

  export PATH="../tools/host":$PATH

2. To compile kernel and modules run commands from 'kenel_M5' directory

  make halley2_linux_sfcnand_mass_defconfig
  
  make xImage
  
  make modules

you'll find compiled 'xImage' image in 'arch/mips/boot/zcompressed' directory
and modules in 'sound/soc/ingenic' directory

3. To build 'recovery' image you need to place nand-root.cpio to 'linux-recovery/client-side/'
or change the path in 'arch/mips/configs/halley2_sfcnand_recovery_defconfig' 
CONFIG_INITRAMFS_SOURCE="linux-recovery/client-side/root-nand.cpio"
then  run commands from 'kenel_M5' directory

  make recovery

you'll find compiled 'recovery' image in 'arch/mips/boot/zcompressed' directory
 
4. To make ubi image

mkfs.ubifs -e 0x1f000 -c 2048 -m 0x800 -d $BUILD_ROOT_PATH/out/system -o $BUILD_ROOT_PATH/out/image/system.ubi
