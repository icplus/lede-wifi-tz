#!/bin/sh
if [ -f /bin/art-partition.bin ]
then 
	rm /bin/art-partition.bin
fi

dd if=/dev/mtd5 of=/bin/art-partition.bin
chmod +x /bin/mac_set
mac_set $1
sleep 5
mtd write /bin/art-partition.bin /dev/mtd5
sleep 3
echo y | firstboot 

reboot
