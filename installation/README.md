# ROS2 Installation

Currently, we provide a few methods to install ROS2 and the `epuck_ros2` package.
The following table compares the installation methods:

|   | [Using Pi-puck Image](#using-pi-puck-image) | [Compilation on the Raspberry Pi](./compile) | [Cross-compilation on your PC](./cross_compile) |
|-------------------|:---:|:---:|:---:|
| Compilation speed |  ++ |  -  |  +  |
| Easy to use       |  ++ |  -  |  -- |
| Flexibility       |  -  |  ++ |  +  |

---

## Using Pi-puck Image
This is the recommended way of installing ROS2 on pi-puck as all ROS2 compilation issues are resolved by us.
Moreover, this is very fast as you don't have to wait for the compilation process to finish.
It is enough to download our image and burn it to a SD card that has to be at least 8GB.
To burn the image on the SD card you can use the following command on Linux:
```bash
dd bs=4M if=path_to_pi_puck_image.img of=/dev/sdX conv=fsync
```
It is very important to provide a correct output device name, it is usually `/dev/sdb` (not `/dev/sdb1`).
To check whether the block device is the one associated with the SD card you can run before inserting the SD card `ls /dev/sd*`, then insert the SD card and run the same command again and compare the output.
For more detailed instructions on how to burn an image to the SD card for different operating systems you can check the following links:

> Detailed instructions for burning SD card on:
[Windows](https://www.raspberrypi.org/documentation/installation/installing-images/windows.md),
[Mac](https://www.raspberrypi.org/documentation/installation/installing-images/mac.md) and 
[Linux](https://www.raspberrypi.org/documentation/installation/installing-images/linux.md)

### Wifi and SSH
Once the image is burned on SD card you may want to configure the Wi-Fi connection.
By default, the pi-puck with the provided image will try to connect to a Wi-Fi network with the SSID `E-PUCK`.
If you want to change the default behavior or to add more networks you can add networks to `/etc/wpa_supplicant/wpa_supplicant.conf` (file located on the SD card).
For example:
```conf
network={
    ssid="my_network_ssid"
    psk="my_network_password"
    key_mgmt=WPA-PSK
}
```
> Detailed instructions on Wi-Fi configuration can be found [here](https://www.raspberrypi.org/documentation/configuration/wireless/wireless-cli.md).

At this point, you probably want to start the nodes from `epuck_ros2`.
First, make sure that your pi-puck and computer are connected to the same local network.
You can ping the pi-puck using:
```
ping raspberrypi.local
```
Or, if your device doesn't support `mDNS` you will need to use `nmap` to [discover pi-puck's IP address](https://www.raspberrypi.org/documentation/remote-access/ip-address.md).

Then, connect to the pi-puck via SSH:
```
ssh pi@raspberrypi.local
```
with `raspberry` as a default password.

> More about SSH and Raspberry Pi can be found [here](https://www.raspberrypi.org/documentation/remote-access/ssh/).

ROS2 installation is located in `/home/pi/ros2_ws`, so you can navigate inside and start `epuck_ros2` driver with:
```bash
source install/local_setup.bash
ros2 launch webots_ros2_epuck2 robot_launch.py
```

### Creating Custom Image

Once the installation is complete, or you developed a custom node, you may want to save the configuration and quickly distribute it to the other robots by creating your own image.
To achieve that, you can simply put the SD card in your computer and copy its content to a `.img` file:
```bash
dd if=/dev/sdX of=path_to_pi_puck_image.img
```
The image size will be equal (if expanded before) to your SD card size even though the content of the image is much smaller.
To shrink the image, use the following command:
```bash
curl https://raw.githubusercontent.com/Drewsif/PiShrink/master/pishrink.sh | sudo bash -s -- path_to_pi_puck_image.img
```

Now, burn the `path_to_pi_puck_image.img` to other SD cards that will be used in other pi-pucks.

## Starting `epuck_ros2` on Boot
In most of the cases, ROS2 development will take place on your computer and ROS2 will take handle the communication between the local nodes and nodes on the pi-puck.
In that scenario, you may want to execute `epuck_ros2` as soon as pi-puck boots without manual intervention.
To achieve this, it is enough to populate `/etc/rc.local` with the following commands:
```bash
source /home/pi/ros2_ws/install/local_setup.bash
ros2 launch webots_ros2_epuck2 robot_launch.py
```
> More about `/etc/rc.local` and Raspberry Pi OS can be found [here](https://www.raspberrypi.org/documentation/linux/usage/rc-local.md)
