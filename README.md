# pi-dongle (WIP)

Transform your pi into a  keyboard.

## Rationale
I own a surface pro 7. Recently its keyboard stopped working and due to lack of availability and high price, I opted for a similar keyboard from a third party vendor. That works great but the only problem is, its a Bluetooth Keyboard, which means I cant use it before the OS starts (GRUB, Firmware Settings etc) :-| 

Therefore as a workaround, I wrote this program. So now your pi zero acts as a bridge between bluetooth keyboard and system using USB port.

## Installation (Pi Zero)

- Enable Necessary kernel modules
```
pi-dongle@pi-dongle:~ $ echo "dtoverlay=dwc2" | sudo tee -a /boot/firmware/config.txt
pi-dongle@pi-dongle:~ $ echo "dwc2" | sudo tee -a /etc/modules
pi-dongle@pi-dongle:~ $ sudo echo "libcomposite" | sudo tee -a /etc/modules
```
- Download required libraries
```
pi-dongle@pi-dongle:~ $ sudo apt install libinput-dev
```

- Cloning and building pi-dongle

``` bash
git clone 
mkdir build
cd build
cmake ..
make

```
- To configure your pi as a USB keyboard, copy the `enable_pikeyboard` script into `/usr/bin` and invoke the program at the end of `/etc/rc.local`
 

## Usage

- After installation, connect your Pi to the host and reboot your Pi Zero.
- Now connect your bluetooth keyboard to the Pi zero using bluetoothctl or similar program.
- Navigate into the project-root/build/executable and run `pi_dongle`
```bash
sudo ./pi_dongle
```
- Now typing anything on your keyboard should be visible on the screen.

## References
- [https://wayland.freedesktop.org/libinput/doc/latest/api/index.html](https://wayland.freedesktop.org/libinput/doc/latest/api/index.html)
- [https://randomnerdtutorials.com/raspberry-pi-zero-usb-keyboard-hid/](https://randomnerdtutorials.com/raspberry-pi-zero-usb-keyboard-hid/)
- [https://mtlynch.io/key-mime-pi/](https://mtlynch.io/key-mime-pi/)
- [https://github.com/htrefil/rkvm](https://github.com/htrefil/rkvm)

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[GPL-3.0](https://choosealicense.com/licenses/gpl-3.0/)
