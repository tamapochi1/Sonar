PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_dmaca_rx
=========

Document Number 
---------------
R01AN2063EJ0104
R01AN2063JJ0104

Version
-------
v1.04

Overview
--------
The DMACA driver provides a method to transmit the data using the Direct Memory Access Controller (DMAC).
The driver includes API functions to initialize DMAC, create Transfer data, Control and get status of DMAC.
The driver can be reduced in size by removing code used for parameter checking. 
All configuration options can be found in "r_config\r_dmaca_rx_config.h". 
An original copy of the configuration file is stored in "r_dmaca_rx\ref\r_dmaca_rx_config_reference.h".

Features
--------
* Support Normal mode, Repeat mode and Block mode
* Support chain transfer

Supported MCUs
--------------
* RX230 Group
* RX231 Group
* RX64M Group
* RX65N Group
* RX71M Group

Boards Tested On
----------------
* RSKRX230
* RSKRX231
* RSKRX64M
* RSKRX65N
* RSKRX71M

Limitations
-----------
* None

Peripherals Used Directly
-------------------------
* Direct Memory Access Controller (DMAC)

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
* Renesas RX v2.05 release 00

File Structure
--------------
r_dmaca_rx
|   r_dmaca_rx_if.h
|   readme.txt
|
+---doc
|   |
|   +---en
|   |       r01an2063ej0104_rx.pdf
|   +---ja
|           r01an2063jj0104_rx.pdf
|
+---ref
|       r_dmaca_rx_config_reference.h
|
+---src
    |   r_dmaca_rx.c
    |   r_dmaca_rx_private.h
    |
    +---targets
        |
        +---rx64m
        |       r_dmaca_rx_target.c
        |       r_dmaca_rx_target.h
        |
        +---rx65n
        |       r_dmaca_rx_target.c
        |       r_dmaca_rx_target.h
        |
        +---rx71m
        |       r_dmaca_rx_target.c
        |       r_dmaca_rx_target.h
        |
        +---rx230
        |       r_dmaca_rx_target.c
        |       r_dmaca_rx_target.h
        |
        +---rx231
                r_dmaca_rx_target.c
                r_dmaca_rx_target.h

r_config
    r_dmaca_rx_config.h
