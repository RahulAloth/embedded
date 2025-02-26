# Printf using SWV

## Overview of the STMicroelectronics Evaluation Board
The STMicroelectronics evaluation board is equipped with an ARM Cortex processor. On the front of the board, there is an ST-Link onboard debug circuitry. This circuitry allows communication with a PC over USB.

## ARM Cortex-M4 Processor and ITM Unit
The ARM Cortex-M4 processor includes an ITM (Instrumentation Trace Macrocell) unit, which is a peripheral. The ITM unit serves two main purposes:
- **Supporting `printf`**: It allows the use of `printf` statements for debugging.
- **Reporting Diagnostics**: It is used to report diagnostic information.

## Debugging with SWD (Serial Wire Debug)
To read registers, memory locations, and perform other debugging tasks, the SWD interface is used. Here are the key points about SWD:
- **Two-Wire Protocol**: SWD is a two-wire protocol that is part of the ARM debug interface.
- **Alternative to JTAG**: It serves as an alternative to the JTAG interface.
- **Physical Layer**: The physical layer of SWD consists of two lines:
  - **SWDIO**: Serial Wire Debug Input/Output
  - **SWCLK**: Serial Wire Clock

## Using Serial Wire Viewer (SWV) for `printf` Statements
The Serial Wire Viewer (SWV) can be used for `printf` statements, which is useful for debugging. Here’s how it works:
- **ARM Cortex-M3 and Onwards**: The `printf`/trace functionality is available from ARM Cortex-M3 processors onwards.
- **Setup**: The setup for using `printf` with SWV involves the following components:
  - **STM32F**: The microcontroller.
  - **SWO Pin**: The Serial Wire Output pin on the microcontroller.
  - **ST-Link V2 Debug Circuit**: The onboard debug circuitry.
  - **USB**: The connection to the PC.
  - **PC Output**: The output displayed on the PC.

## Summary
- **STMicroelectronics Evaluation Board**: Communicates with PC via USB using ST-Link onboard debug circuitry.
- **ARM Cortex-M4 Processor**: Features ITM unit for `printf` and diagnostics.
- **SWD Interface**: Two-wire protocol for debugging, alternative to JTAG.
- **SWV for `printf`**: Enables debugging with `printf` statements, supported from ARM Cortex-M3 onwards.


Implimentation of this feature can be found in syscalls.c file.
