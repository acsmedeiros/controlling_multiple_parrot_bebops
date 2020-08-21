# Controlling Multiple Parrot Bebops2

How to connect multiple Parrot Bebop 2 to a router and control them using ROS kinetic on Ubuntu 16.04LTS

## Connecting Bebop 2 to a Router 

### Setting up the 3.3 version firmware

To connect your bebop to a router, you first need to install [wpa_supplicant](https://wiki.archlinux.org/index.php/WPA_supplicant) software to your bebop 2. 

Unfortunately, some firmware versions won't allow it. If that's the case for your firmware version, I recommend downgrading your "Bebop 2" firmware to the 3.3v. Do it at your own risk.

To install the firmware 3.3 for bebop2, you will need the firmware file, which you can download from [here](https://github.com/uavpal/beboptwo4g/wiki/Manual-firmware-upgrade-and-downgrade-of-Parrot-Bebop-2)

After downloading the "bebop2_update.plf" for the "3.3.0" firmware version, you can then follow the instructions given there, or if you preferer, follow the instructions here.

To move the "bebop2_update.plf" inside your drone:

1. fully charge the drone
2. connect it via USB to the PC 
3. press the drone button 4 times
4. open a terminal:
```bash
sudo apt-get install android-tools-adb
adb connect 192.168.43.1:9050
```

It should state something like "connected to 192.168.43.1:9050" if the connection was not established, try pushing bebop2's power button 4 times again, sometimes that's tricky.
Once your connection was stabilished you can copy the "bebop2_update.plf" to the drone's update/ folder:

```bash
adb shell mount -o remount,rw /
adb push path/to/bebop2_update.plf /update/  
```


Okay, now lets use telnet to connect to the drone and make the change in the firmware version. **Make sure the drone has a full battery**

```bash
telnet 192.168.43.1
mount -o remount,rw /
mv /update/bebop2_update.plf /update/bebopdrone_update.plf
/usr/bin/pinst_trigger 1
/bin/reboot.sh
```


I should take around 3-4 minutes (Bebop 2 will reboot twice).

Congrats, now you have firmware 3.3.0 installed! 

### Installing wpa_supplicant files to bebop 2 (so it can connect to the router)

Credits to [this](https://github.com/tnaegeli/multiple_bebops.git) repository. Just go [there](https://github.com/tnaegeli/multiple_bebops.git) and download the files and follow their instructions, should work fine.
Just make sure to edit the shortpress_3.sh file to contain the **desired IP for your drone**, **SSID**, and **Password** of your router wifi network.
Also, make sure to set up the desired IP on shortpress_5.sh.

If you have some troubles here, a good way to troubleshoot is to:
```bash
telnet 192.168.43.1
mount -o remount,rm /
cd /bin/onoffbutton
vi shortpress_3.sh
```
You can then edit the shortpress_3.sh file directly, a suggestion is to drop the -B flag from "wpa_supplicant -B -D wext -i eth0 -c /etc/wpa_supplicant.conf" therefore you can see the output from this command.

Still connected to the drone's telnet, you can ./shortpress_3.sh and check the output for any errors.

Dont know how to edit files with "vi" ? check [here](https://staff.washington.edu/rells/R110/).

## Using ROS to connect to multiple drones

Now you should have one or more drones connect to your local network. Make sure each drone has a **unique IP** address.
Now download [bebop_autonomy](https://bebop-autonomy.readthedocs.io/en/latest/) from [this](https://github.com/AutonomyLab/bebop_autonomy.git) repository.

In order to launch the drones we are going to need to modify the original */bebop_autonomy/bebop_driver/launch/bebop_node.launch* file.

You can have a separate launch file for each bebop. Modify this launch file with the correct ip address for each drone.

This repository provides, as an example, [two](https://github.com/acsmedeiros/controlling_multiple_parrot_bebops/tree/master/launch_for%20bebop_autonomy) separate launch files for drones A and B, and a simple [routine](https://github.com/acsmedeiros/controlling_multiple_parrot_bebops/blob/master/src/move_two_bebop2.cpp) that can make those drones go up, down, left, right and roundabout, simultaneously.

If you are going to use the launch files here, remember to change the IP address accordingly.

To run the code here just:
```bash
rosrun controlling_multiple_parrot_bebops multiple_bebop move_two_bebop2
```

A video showcasing the code in use can be found [here](https://youtu.be/slre7MKHVYc).

