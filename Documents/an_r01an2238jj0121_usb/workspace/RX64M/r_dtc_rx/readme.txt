PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_dtc_rx
=========

Document Number 
---------------
R01AN1819EJ0206
R01AN1819JJ0206

Version
-------
v2.06

Overview
--------
The DTC driver provides a method to transmit the data using Data Transfer Controller (DTC).
The driver includes API functions to initialize DTC, create Transfer data, Control and get status of DTC.
The driver can be reduced in size by removing code used for parameter checking. 
All configuration options can be found in "r_config\r_dtc_rx_config.h". 
An original copy of the configuration file is stored in "r_dtc_rx\ref\r_dtc_rx_config_reference.h".

Features
--------
* Support Normal trasnsfer mode, Repeat trasnsfer mode and Block trasnsfer mode.
* Support chain transfer

Supported MCUs
--------------
* RX110 MCU
* RX111 MCU
* RX113 MCU
* RX130 MCU
* RX230 MCU
* RX231 MCU
* RX64M MCU
* RX71M MCU
* RX23T MCU
* RX24T MCU
* RX65N MCU

Boards Tested On
----------------
* RSKRX110
* RSKRX111
* RSKRX113
* RSKRX130
* RSKRX230
* RSKRX231
* RSKRX64M
* RSKRX71M
* RSKRX23T
* RSKRX24T
* RSKRX65N

Limitations
-----------
* None

Peripherals Used Directly
-------------------------
* Data Transfer Controller (DTC)

Required Packages
-----------------
* r_bsp v3.40

How to add to your project
--------------------------
This module must be added to each project used in e2 studio.
There are two methods for adding to a project: using the FIT plug-in and adding manually.
When the FIT plug-in is used, FIT modules can be added to projects easily 
and the include file path will be updated automatically.
Therefore we recommend using the FIT plug-in when adding FIT modules to a project.

There are the following methods for adding FIT modules to the projects using FIT plug-in. 
1.  Use "FIT Configurator". 
This is the latest method that the plug-in function such as Lib file path automatic setting is enhanced, 
which we recommend the use. 
For the procedure, refer to "4.3.2 Install the FIT Modules with the FIT Plugin." 
in "RX64M/RX71M Group RX Driver Package Ver.1.02 (R01AN2606EJ)Åh application note. 

2.  Use the existing "FIT plug-in".
For the procedure, refer to "3. Adding FIT Modules to e2 studio Projects Using FIT Plug-In" 
in "Adding Firmware Integration Technology Modules to Projects (R01AN1723EU)" application note.

Toolchain(s) Used
-----------------
* Renesas RX v2.05

File Structure
--------------
r_dtc_rx
|   r_dtc_rx_if.h
|   readme.txt
|
+---doc
|   |
|   +---en
|   |       r01an1819ej0206-rx.pdf
|   +---ja
|           r01an1819jj0206-rx.pdf
|
+---ref
|       r_dtc_rx_config_reference.h
|
+---src
    |   r_dtc_rx.c
    |   r_dtc_rx_private.h
    |
    +---targets
        |
        +---rx23t
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx24t
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx64m
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx65n
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx71m
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx110
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx111
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx113
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx130
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx230
        |       r_dtc_rx_target.c
        |       r_dtc_rx_target.h
        |       r_dtc_rx_target_if.h
        |
        +---rx231
                r_dtc_rx_target.c
                r_dtc_rx_target.h
                r_dtc_rx_target_if.h

r_config
    r_dtc_rx_config.h


