# ULib
This repository has some common business layer implementations, that implement in the form of a module usage.

You can use these modules via `#include`, there is a macro like `XXX_DEBUG` in all modules, and you can enable debugging logging via `#define XXX_DEBUG 1`.

+ Modules:
    + [uconfig](#uconfig)
    + [uprotocol](#uprotocol)

**WARNING**: That modules are not thread safe, and you should not use them in a multi-threaded environment or you must add mutexes.

## uconfig
This config manager for embedded system
### Usage
1. Implement your config interface file(uconfig_if.c and uconfig_if.h)

2. Your need include uconfig header`#include "uconfig.h"`

3. First you must call `uconfig_init()`, this function will load config

+ Main file:
    + Refer header: [./test/test_uconfig_if.h](./test/test_uconfig_if.h)
    + Refer source: [./test/test_uconfig_if.c](./test/test_uconfig_if.c)

## uprotocol
This easy protocol for point to point communication, look like RPC protocol, is application layer protocol

1. Each request must response
2. The next request can only be sent after the response is received
2. Each request is independent of the other

> Timeout feature need user implementation

### Usage

TODO: Secure feature, for macro switch, predefine cmd handler

