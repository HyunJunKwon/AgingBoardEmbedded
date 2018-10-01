/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V1.0
* Date               : 10/08/2007
* Description        : This sub-directory contains all the user-modifiable files 
*                      needed to create a new project linked with the STM32F10x  
*                      Firmware Library and working with IAR Embedded Workbench 
*                      for ARM (EWARM) software toolchain (version 4.42A)
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

Directory contents
===================
- project .ewd/.eww/.ewp: A pre-configured project file with the provided library 
                          structure that produces a debug\release executable image
                          with IAR Embedded Workbench.
                
- stm32f10x_vector.c: This file contains the vector table for STM32F10x.

- lnkarm_flash.xcl: This file is the IAR specific linking and loading file used 
                    to load in Flash and execute code and variables to target 
                    memories and regions. You can customize this file to your need.

- lnkarm_ram.xcl: This file is the IAR specific linking and loading file used to 
                  load in RAM and execute code and variables to target memories 
                  and regions. You can customize this file to your need.
                       
- cortexm3_macro.s: Instruction wrappers for special Cortex-M3 instructions. 

      
How to use it
=============
- Open the Project.eww workspace.
- In the workspace toolbar select the project config:
   - BOOT_FLASH: to load project image into FLASH
   - BOOT_RAM: to load project image into RAM
- Rebuild all files: Project->Rebuild all
- Load project image: Project->Debug
- Run program: Debug->Go(F5)   

Example description
===================
This is a simple demonstration, based on STM32 ("version 128k"), using the  Embeddeded  Library File System  “EFSL”  with an "SD" memory card in order to
explore the  contents of this SD card  and show, on an LCD color,  the Tree of directories/files within the SD card.

Hardware environment
====================
-  The demo was developed based on the STM3210B-EVAL board (revA).
-  The resources used on the board are the Joystick (up/sel buttons), the LCD color and the SD card connected to the SPI1 bus of STM32x.


 Development   Tools 
====================
 IAR Embedded Workbench for ARM (EWARM) software tool chain (version 4.42A)                     

Example Purpose
===================
The Purpose of this demo is to show that the STM32 can be used with the EFSL in order to browse a tree of directories on an SD card and read the content of files (examples: mp3 files, txt files, wave files...) which can be useful when using CODECs handling some files format like mp3....
We use the LCD available on the STM3210B-EVAL board to display the data structure and pointing, with Joystic buttons, the desired folder/file.
 Example Limitation
===================
This example is limited to browse "three levels” of access (with 2 subdirectories for each Level)
Directories naming are limited in term of size.
The example can read your own SD card content only if you respect directories naming size as delivered with the demo: Please find the SD data content tested with this demo under the directory SDcontent coming with this example.

, Otherwise you need to work on some "string handling”
Please note that the example can be improved in term of interrupt mechanism robustness when using Joystick.
The Joystick button "SEL” is used to enter directory and the “UP” button used to select it.
Before running the demo, you should format your SD card (FAT) using other applications :( example a PC with windows) and mount your data on the card…

About EFSL
===================

EFSL is available under GNU General Public License with an exception clause.
The EFSL project aims to create a library for filesystems, to be used on various embedded systems. EFSL supports the Microsoft FAT filesystems family.
 This library supports FAT12/16/32 reading and writing on SD-cards. 
For more info about EFSL please refer to: 

http://sourceforge.net/projects/efsl



      
******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE******

