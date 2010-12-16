Author: andrew dot nagi at gmail dot com
========================================

This is a hardware hack. It turns the trackball on the Compaq mx11800 into a "scroll ball". It should work with other trackballs and dissembled PS/2 mouse parts. The microcontroller needs to be clocked at 12Mhz at least to stand any chance of working. It works fine at 16Mhz, which allows sufficient time to Read PS/2 data from the mouse between USB Polls. If you want to use this code in a commercial product don't forget to get a unique USB device ID.

Once you have built the adapter and plugged it in, use dmesg in Linux to check if the device has connected:
[] input: Nagi-Sys Scrolly Ball as /devices/pci0000:00/0000:00:16.0/usb7/7-2/7-2:1.0/input/input8
[] generic-usb 0003:FEED:BEEF.0006: input,hidraw2: USB HID v1.01 Mouse [Nagi-Sys Scrolly Ball] on usb-0000:00:16.0-2/input0

Possible modifications could inlude:
  Make a scroll ball / track ball out of a upside down P2/2 mouse.
  Add extra buttons to or generate key sequences from a Model M.
  Make a HID custom controller for AV editing etc
  Log key pressess and display words per minute on 7-Segment Display / LCD
  Make a novel game controller to keep fit (I'm working on that next).

Thanks to: Christian Starkjohann at Objective Development Software GmbH.
http://www.obdev.at/
Thanks to: Akshay Srinivasan<akshaysrinivasan@nitk.ac.in>
-------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
