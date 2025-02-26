// STM32.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "STM32.h"
/*
System calls are the fundamental interface between an application and the kernel, allowing programs to request services from the operating system.
 The file defines various system calls, such as open, read, write, and close. Each system call is implemented as a function that 
 performs specific tasks requested by user-space applications.
 System Call Definitions:
 This file defines various system calls that user-space programs can invoke to request services from the kernel. 
 Examples include file operations (open, read, write), process control (fork, exec, exit), and memory management (mmap, munmap).
Function Implementations: Each system call is implemented as a function in this file.
These functions handle the necessary operations in kernel space, such as interacting with hardware, managing resources, and enforcing security policies.
System Call Table: The file often includes a table that maps system call numbers to their corresponding handler functions. 
This table is used by the kernel to dispatch system calls to the correct function based on the system call number provided by the user-space program.
Error Handling: The implementations include error checking and handling to ensure that invalid requests or
operations are properly managed and that appropriate error codes are returned to the user-space program.


If so then what is Kernal:
A kernel is the core component of an operating system. It acts as a bridge between software applications and the hardware of
a computer. Here are some key points about the kernel:
Core Functions: The kernel manages system resources, such as the CPU, memory, and input/output devices.
It ensures that different applications and processes can run smoothly without interfering with each other1.
Memory Management: It controls how memory is allocated and ensures that each process has the necessary memory to function properly2.
Process Management: The kernel handles the creation, scheduling, and termination of processes. 
It decides which processes get to use the CPU and for how long2.
Device Management: It manages communication between the system and hardware devices through device drivers1.
System Calls: The kernel provides a set of system calls that applications can use to request services from the operating system, 
such as file operations, process control, and network communication3.
There are different types of kernels, including monolithic kernels, which run all operating system services in a single address space for efficiency,
and microkernels, which run most services in user space for modularity and resilience

ITM Module:

The Instrumentation Trace Macrocell (ITM) is a debugging module found in ARM Cortex-M microcontrollers, 
including STM32 devices. It provides a way to output debug information, such as trace data and printf-style messages,
to a debugger or a console. Here are some key features and uses of the ITM module:

Debugging and Tracing: ITM allows developers to send trace data and debug messages from the microcontroller 
to an external debugger. This is useful for monitoring the execution of code and diagnosing issues in real-time.

Printf Redirection: One common use of ITM is to redirect printf statements to the ITM console. 
This enables developers to view debug messages without needing a serial port or other communication peripherals.

Performance Monitoring: ITM can be used in conjunction with other debugging tools, such as the Data Watchpoint 
and Trace (DWT) unit, to monitor performance metrics like CPU cycles and instruction counts.

Low Overhead: ITM is designed to have minimal impact on the performance of the microcontroller, making 
it suitable for use in real-time applications.

The _write function is overridden to send characters to the ITM.
The printf function is used to send a message to the ITM console.
To view the ITM output, you need to configure your debugger(using STM32CubeIDE) to enable the
ITM console and set up the necessary debug configurations
*/

#include <stdio.h>
#include "stm32f4xx.h"

/*
Setting a bit in a control register in Embedded C is a common task. Here’s how you can do it:
For below code, ITM_SendChar() function, we need to enable TRCENA pins.

Enabling TRCENA
DEMCR |= (1 << 24);
This line enables the Trace Control Register (TRCENA) by setting the 24th bit of the Debug Exception and
Monitor Control Register (DEMCR). This is necessary for ITM to function.

Enabling Stimulus Port 0
ITM_TRACE_EN |= (1 << 0);
This line enables stimulus port 0 by setting the 0th bit of the ITM Trace Enable Register (ITM_TRACE_EN).
This allows data to be sent to this port.

Checking FIFO Status
while (!(ITM_STIMULUS_PORT0 & 1));
This loop waits until the FIFO (First In, First Out) buffer of stimulus port 0 is ready to accept new data. 
It checks the 0th bit of the ITM Stimulus Port 0 Register (ITM_STIMULUS_PORT0) to see if it’s set, indicating the port is ready.

*/
//Debug Exception and Monitor Control Register base address
#define DEMCR        			*((volatile uint32_t*) 0xE000EDFCU )

/* ITM register addresses */
#define ITM_STIMULUS_PORT0   	*((volatile uint32_t*) 0xE0000000 )
#define ITM_TRACE_EN          	*((volatile uint32_t*) 0xE0000E00 )
#define CONTROL_REG   	        *((volatile uint32_t*) 0xE0000B00 )

void ITM_SendChar(uint8_t ch)
{

    //Enable TRCENA
    DEMCR |= (1 << 24);

    //enable stimulus port 0
    ITM_TRACE_EN |= (1 << 0);

    // read FIFO status in bit [0]:
    while (!(ITM_STIMULUS_PORT0 & 1));

    //Write to ITM stimulus port0
    ITM_STIMULUS_PORT0 = ch;
}

int _write(int file, char* ptr, int len) {
    for (int i = 0; i < len; i++) {
        ITM_SendChar(*ptr++);
    }
    return len;
}

/*
Setting a Bit
To set a specific bit, you use the bitwise OR operator ( |= ) with a bitmask.The bitmask has a 1 at the position of the bit you want to set and 0s elsewhere.
*/
int setting_bit(int n) {
  // Set the nth bit of a register
    CONTROL_REG |= (1 << n);
  // For example If you want to set the 3rd bit of a register named CONTROL_REG, you would do:
  // CONTROL_REG |= (1 << 3);

    return 0;
}

/*
Clearing a Bit:
To clear a specific bit, you use the bitwise AND operator (&=) with the bitwise NOT operator (~) to create a
bitmask that has 0 at the position of the bit you want to clear and 1s elsewhere.
*/
int clearing_bit(int n) {
    // Clear the nth bit of a register
    CONTROL_REG &= ~(1 << n);
    // For example if n is 3 then.
    // CONTROL_REG &= ~(1 << 3);
    return 0;
}
/*
Toggling a bit
To toggle a specific bit, you use the bitwise XOR operator (^=) with a bitmask.
*/

int toggling_bit(int n) {
    // Toggle the nth bit of a register
    CONTROL_REG ^= (1 << n);
    // For example, toggle the 3rd bit of CONTROL_REG
    // CONTROL_REG ^= (1 << 3);
    return 0;
}
/*
Waiting for Availability: 
Sometime, we need to wait until a bit is available for a particular port, in this case, normally we use the below code:
For example, below code, the while loop ensures that the FIFO buffer of the ITM stimulus port 0 is ready to accept new data 
before proceeding. It checks the 0th bit of the ITM_STIMULUS_PORT0 register.
Operation:
Bitwise AND Operation: The expression (ITM_STIMULUS_PORT0 & 1) checks the 0th bit of the ITM_STIMULUS_PORT0 register.
Condition Check: The while loop continues to run as long as the 0th bit is 0, indicating that the FIFO buffer is not ready.
Exit Condition: The loop exits when the 0th bit becomes 1, meaning the FIFO buffer is ready to accept new data.
This is a common practice in embedded systems to ensure that the hardware is ready before sending data, preventing data loss or corruption.

*/
int wait_for_availability() {
    // read FIFO status in bit [0]:
    while (!(ITM_STIMULUS_PORT0 & 1));
    return 0;
}
int main(void) {
   //  SystemInit();
    printf("Hello world!\n");
    for (;;);
}
