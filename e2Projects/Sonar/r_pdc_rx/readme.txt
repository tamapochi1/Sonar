PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_pdc_rx
========

Document Number
---------------
R01AN3167EJ0201-rx (English version)
R01AN3167JJ0201-rx (Japanese version)

Version
-------
v2.01

Overview
--------
The PDC fit module provides a method to capture the parallel data output from the device including image sensors.
The source was tested on the board RSKRX64M and RSKRX71M, RSKRX65N, RSKRX65N_2MB, IDE e2studio with RX compiler
The driver includes API functions to initialize PDC, Control of PDC module, registrasion of the callback function etc..
All configuration options can be found in "r_config\r_pdc_rx_config.h".
An original copy of the configuration file is stored in "r_pdc_rx\ref\r_pdc_rx_config_reference.h".

Features
--------
* Capturing parallel data of any vertical, horizontal directions.

Supported MCUs
--------------
* RX64M Group
* RX71M Group
* RX651 Group
* RX65N Group

Boards Tested On
----------------
* RSKRX64M
* RSKRX71M
* RSKRX65N
* RSKRX65N_2MB

Limitations
-----------
* None

Peripherals Used Directly
-------------------------
* Parallel Data Capture Unit (PDC)

Required Packages
-----------------
* r_bsp

How to add to your project
--------------------------
* Add source foler r_pdc_rx to your project.
* Add an include path to the 'r_pdc_rx' directory.
* Copy the reference configuration file 'r_pdc_rx_config_reference.h' to your
  project and rename it r_pdc_rx_config.h.
* Configure middleware for your system through just copied r_pdc_rx_config.h.
* Add a #include for r_pdc_rx_if.h(It is also r_pdc_<mcu>.h)
  to any source files that need to use the API
  functions.

NOTE : <mcu> is RX famiry Group name.  (For example, rx64m)


Toolchain(s) Used
-----------------
* Renesas RX v2.07.00

File Structure
--------------
r_pdc_rx
|       readme.txt
|       r_pdc_rx_if.h
|
+---doc
|   |
|   +---en
|   |   r01an3167ej0201-rx.pdf
|   |
|   \---ja
|       r01an3167jj0201-rx.pdf
|
+---ref
|       r_pdc_rx_config_reference.h
|
\---src
        r_pdc_rx.c
        r_pdc_rx_private.h
