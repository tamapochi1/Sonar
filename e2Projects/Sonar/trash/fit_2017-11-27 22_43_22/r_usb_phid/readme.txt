PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_usb_phid
=======================

Document Number 
---------------
R01AN2663EJ
R01AN2663JJ

Version
-------
v1.22

Overview
--------
USB Peripheral Human Interface Device Class Driver (PHID)

Features
--------
USB peripheral HID class driver conforms to the USB HID class specification 
and implements communication with HID devices.


Supported MCUs
--------------
* RX64M Group
* RX71M Group
* RX63N Group
* RX65N Group

Boards Tested On
----------------
* RSKRX64M
* RSKRX71M
* RSKRX63N
* RSKRX65N
* RSKRX65N_2MB
 
Limitations
-----------

Peripherals Used Directly
-------------------------


Required Packages
-----------------
* r_bsp
* r_usb_basic

How to add to your project
--------------------------

Toolchain(s) Used
-----------------
* Renesas RX v.2.07.00

File Structure
--------------
r_usb_pcdc
|   readme.txt
|   r_usb_phid_if.h
|
+---doc
|     \en
|     |   r01an2663ej0122_usb.pdf
|     \jp
|         r01an2663jj0122_usb.pdf
|
+---ref
|       r_usb_phid_config_reference.h
|
\---src
     |  r_usb_phid_driver.c
     |
     \---inc
             r_usb_phid.h

