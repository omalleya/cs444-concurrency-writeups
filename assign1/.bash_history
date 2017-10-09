cd /scratch/fall2017
ls
mkdir 19
ls
cd 19
git init
git clone git://git.yoctoproject.org/linux-yocto-3.19
git checkout v3.19.2
git checkout 'v3.19.2'
cd ..
ls
chmod 755 19
ls
cd 19
ls
git
git status
git add .
git commit -m "initial commit"
git status
cd ..
ls ..
cd fall2017
ls
ls ..
cd ..
cd bin
ls
./acl_open -g ./fall2017/19 group
./acl_open -g ../fall2017/19 19
./acl_open -g ../fall2017/ 19
./acl_open -g ../fall2017/19
./acl_open -g ../fall2017/19 omalleya simsw
./acl_open -g ../fall2017/19 omalleya
./acl_open -g ../fall2017/19 19
./acl_open -g ../fall2017/19 '19'
./acl_open -g ../fall2017/19 19
./acl_open -g ../fall2017/19 simsw
./acl_open ../fall2017/19 simsw
ls
cd ..
cd fall2017
ls
ls -ld .
cd 19
ls -ld .
ls
git checkout v3.19.2
git status
git branch
git fetch
cd linux-yocto-3.19/
ls
git status
git checkout v3.19.2
ls
cd kernel
ls
cd configs
ls
cd ../..
ls
cd ..
ls
cd ..
ls
cd opt
ls
cd poky
ls
cd 1.8 && ls
ls
./environment-setup-i586-poky-linux
source ./environment-setup-i586-poky-linux
cd ..
ls
cd ../..
ls
cd fall2017
ls
cd 19
ls
cd linux-yocto-3.19/
ls
cd ../..
ls
cd files
cd ..
ls
cd files
ls
cd ..
ls
cd fall2017
ls
cd 19
ls
cd linux-yocto-3.19/
ls
pwd
source ../../../scratch/opt/environment-setup-i586-poky-linux
source ../../../../scratch/opt/environment-setup-i586-poky-linux
source ../../scratch/opt/environment-setup-i586-poky-linux
source ../../..//opt/environment-setup-i586-poky-linux
source ../../../opt/environment-setup-i586-poky-linux
source ../../../opt/poky/1.8/environment-setup-i586-poky-linux 
git status
cp ../../../files/bzImage-qemux86.bin .
cp ../../../files/core-image-lsb-sdk-qemux86.ext4 .
ls
git status
git add .
git status
git add .
git status
git commit -m "copies kernel and drive files to working directory"
git push
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel bzImage-qemux86.bin -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
cd scratch/fall2017/19
cd /scratch/fall2017/19
la
ls
cd linux-yocto-3.19/
ls
cp bzImage-qemux86.bin bzImage-qemux86-1.bin 
ls
cp ../../../files/bzImage-qemux86.bin .
ls
git status
gdb
gdb help
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel bzImage-qemux86.bin -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
source ../../../files/environment-setup-i586-poky-linux
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel bzImage-qemux86.bin -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
cd /scratch/fall2017/19
ls
cd linux-yocto-3.19/
ls
gdb
$GDB
$GDB remote target :5519
gdb
ls
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel bzImage-qemux86.bin -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
source ../../../files/environment-setup-i586-poky-linux
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel bzImage-qemux86.bin -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
cd /scratch/fall2017/19
cd linux-yocto-3.19/
ls
gdb
ls
cd arch
ls
cd ..
ls
cp ../../../fall2017/files/config-3.19.2-yocto-qemu ./.config
cp ../../../files/config-3.19.2-yocto-qemu ./.config
cp ../../../files/config-3.19.2-yocto-standard ./.config
ls
ls -a
cat .config
make -j4 all
ls
./vmlinux
target
$GBD
$GDB
ls
file vmlinux
make menuconfig
ls -a
emacs .bashrc
source .bashrc
os2
ls
cd linux-yocto-3.19/
ls
$GDB target remote :5519
$GDB
cd tools && ls
cd ..
$GDB target remote :5519
$GBD target remote :5519
target remote :5519 $GDB
target remote :5519 $GBD
ls
cd kernel
ls
$GDB
echo $GDB
echo $GBD
cd ..
ls
source ../../../files/environment-setup-i586-poky-linux
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel bzImage-qemux86.bin -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
os2
cd linux-yocto-3.19/
ls
$GDB target remote :5519
$gdb target remote :5519
$gbd target remote :5519
source ../../../files/environment-setup-i586-poky-linux
$GDB
os2
cd linux-yocto-3.19/
make -j4 all
ls
./vmlinux
make menuconfig
ls
source ../../../files/environment-setup-i586-poky-linux
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel group19hw1 -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel group19hw1.bin -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel vmlinux -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
rm vmlinux*
ls
$GDB
os2
cd linux-yocto-3.19/
source ../../../files/environment-setup-i586-poky-linux
$GDB
cd ../../../files
ls
cd ..
cd opt
ls
cd ..
cd bin && ls
cd ..
ls
cd fall2017
cd 19
ls
cd linux-yocto-3.19/
ls
make menuconfig
make -j4 all
ls
source ../../../files/environment-setup-i586-poky-linux
make -j4 all
ls
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel group19-hw1 -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel vmlinux -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
vmlinux
cat Makefile
vim Makefile
ls
git status
ls -a
make menuconfig
cd kernel
ls
cd ..
ls
make vmlinux
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel vmlinux -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
ls
cd arch
ls
ls -a
cd ..
ls
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel group19-hw1 -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
ls -a
cd virt
ls
cd kvm
ls
cd ../../
ls
cd kernel
ls
cd ..
ls
source ../../../files/environment-setup-i586-poky-linux
source ../../../files/environment-setup-i586-poky-linux.csh
source ../../../files/environment-setup-i586-poky-linux
cp ../../../files/core-image-lsb-sdk-qemux86.ext4 .
make -j4 all
ls
cd arch/x86/boot
ls
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel arch/x86/boot/bzImage -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
ls
cd ../../../
ls
qemu-system-i386 -gdb tcp::5519 -S -nographic -kernel arch/x86/boot/bzImage -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
