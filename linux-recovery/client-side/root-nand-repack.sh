mkdir root-nand
cd root-nand
sudo cpio -idm < ../root-nand.cpio
sudo cp -a ../recovery sbin/
sudo find ./ -print | cpio -H newc -ov > ../root-nand.cpio

