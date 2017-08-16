# Debug box with uVisor example

[![Build Status](https://travis-ci.org/ARMmbed/mbed-os-example-uvisor-debug-fault.svg?branch=master)](https://travis-ci.org/ARMmbed/mbed-os-example-uvisor-debug-fault)

This is a simple example to show how to use uVisor APIs to build a box that implements debug box functionality.

* Create and run secure boxes.
* Try accessing a not allowed address and enter debug box

Supported devices:

| Target            | Toolchain | Baud rate |
|-------------------|-----------|-----------|
| `K64F`            | `GCC_ARM` | 9600      |
| `DISCO_F429ZI`    | `GCC_ARM` | 9600      |
| `EFM32GG_STK3700` | `GCC_ARM` | 9600      |

Latest release: [mbed-os-5.5.x](https://github.com/ARMmbed/mbed-os/releases/tag/latest). Tested with [mbed-cli v1.2.0](https://github.com/ARMmbed/mbed-cli/releases/tag/1.2.0).

## Quickstart

For a release build, please enter:

```bash
$ mbed compile -m K64F -t GCC_ARM -c
```

You will find the resulting binary in `BUILD/K64F/GCC_ARM/mbed-os-example-uvisor-debug-fault.bin`. You can drag and drop it onto your board USB drive.

```bash
$ screen /dev/tty.usbmodem1422 9600
```

You will see an output similar to the following one:

```
***** uVisor debug box example *****
Failed with an error code: 0x00000001

Exception stack frame:
SP[07]: 0x21000000 | xPSR
SP[06]: 0x00008f70 | PC
SP[05]: 0x00008f6b | LR
SP[04]: 0x0000672d | R12
SP[03]: 0xffffffff | R3
SP[02]: 0x0000000d | R2
SP[01]: 0x00000000 | R1
SP[00]: 0x1fff06c2 | R0

Registers after fault:
LR:      0xfffffffd
IPSR:    0x00000005
CONTROL: 0x00000001

Fault registers:
CFSR:  0x00000400
HFSR:  0x00000000
DFSR:  0x00000008
AFSR:  0x00000000
MMFAR: Invalid
BFAR:  Invalid
```

### Debug

When a debugger is connected, you can observe debug output from uVisor. Please note that these messages are sent through semihosting, which halts the program execution if a debugger is not connected. For more information please read the [Debugging uVisor on mbed OS](https://github.com/ARMmbed/uvisor/blob/master/docs/api/DEBUGGING.md) guide. To build a debug version of this example, please enter:

```bash
$ mbed compile -m K64F -t GCC_ARM --profile mbed-os/tools/profiles/debug.json -c
```

## Known issues

- Use of exporters for multiple IDEs is not supported at the moment.

