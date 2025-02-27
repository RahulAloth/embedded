# ARM Cortex-M0, M3, and M4 Processors

## Operational Modes

### Thread Mode
This is the default mode where user application code runs. The processor enters Thread mode after a reset and returns to it after handling an exception. In Thread mode, the code can run with either privileged or unprivileged access.

### Handler Mode
This mode is used for exception handling. When an exception occurs, the processor switches to Handler mode to execute the exception handler. All code running in Handler mode has privileged access.

## Privilege Levels

### Privileged
Full access to all system resources.

### Unprivileged
Limited access to system resources, typically used for application code to enhance security.

The CONTROL register is used to switch between privileged and unprivileged levels in Thread mode. However, in Handler mode, the code always runs with privileged access.

These modes and privilege levels help in managing system resources efficiently and securely, especially in embedded systems where reliability and security are crucial.
