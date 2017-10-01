PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_usb_pcdc
=======================

Document Number 
---------------
R01AN2030EJ
R01AN2030JJ

Version
-------
v1.20


Overview
--------
USB Peripheral Communications Device Class Driver (PCDC)

Features
--------
The PCDC conforms to the abstract control model of the communication
device class specification (CDC) and enables communication with a USB Host.


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
* Renesas RX v.2.05.00

File Structure
--------------
r_usb_pcdc
|   readme.txt
|   r_usb_pcdc_if.h
|
+---doc
|       r01an2030ej0120_usb.pdf
|       r01an2030jj0120_usb.pdf
|
+---ref
|       r_usb_pcdc_config_reference.h
|
+---utilities
|       CDC_Demo_Win7.inf
|
\---src
     |  r_usb_pcdc_api.c
     |  r_usb_pcdc_driver.c
     |
     \---inc
             r_usb_pcdc_api.h
             r_usb_pcdc_define.h
             r_usb_pcdc_extern.h

