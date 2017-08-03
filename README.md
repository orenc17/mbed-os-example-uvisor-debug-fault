# Debug box with uVisor example

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
Tried to access address 0xFFFFFFFF which is not allowed
Bye Bye Now!!!!!!
```

### Debug

When a debugger is connected, you can observe debug output from uVisor. Please note that these messages are sent through semihosting, which halts the program execution if a debugger is not connected. For more information please read the [Debugging uVisor on mbed OS](https://github.com/ARMmbed/uvisor/blob/master/docs/api/DEBUGGING.md) guide. To build a debug version of this example, please enter:

```bash
$ mbed compile -m K64F -t GCC_ARM --profile mbed-os/tools/profiles/debug.json -c
```

## Known issues

- Use of exporters for multiple IDEs is not supported at the moment.

