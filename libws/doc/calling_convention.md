Calling conventions/ASM interfacing {#calling_convention}
===================================

Wonderful currently uses the `20180813` version of the `regparmcall` calling convention, as defined by gcc-ia16.

## Function parameter passing

For typical functions, the first three arguments or words, whichever comes first, are passed via the registers
`AX`, `DX` and `CX`, in this order. Bytes are passed via `AL`, `DL` and `CL`. The remaining arguments are pushed
onto the stack.

Arguments are not split between registers and stack. A far pointer, or 32-bit integer, will be passed via `DX:AX`, `CX:DX`, or entirely on the stack.
  
For functions with *variable arguments*, all arguments are pushed onto the stack. It is the callee's responsibility to remove arguments off the stack.

For example, the following function signature:

    void outportw(uint8_t port, uint16_t value);

results in the following calling convention:

 * `AL` = `port`,
 * `DX` = `value`.

The following function signature:

    void __far* memcpy(void __far* s1, const void __far* s2, size_t n);

results in the following calling convention:

 * `DX:AX` = `s1`,
 * stack (4 bytes allocated) = `s2`,
 * stack (2 bytes allocated) = `n`,
 * return in `DX:AX`.

 The following function signature:

    void __far* memcpy(void __far* s1, const void __far* s2, size_t n);

results in the following calling convention:

 * `DX:AX` = `s1`,
 * stack (4 bytes allocated) = `s2`,
 * stack (2 bytes allocated) = `n`,
 * return in `DX:AX`.

## Function call register allocation

* `AX`, `BX`, `CX`, `DX` can be modified by the callee,
* `SI`, `DI`, `BP`, `DS`, `ES` must be saved by the callee - the value must not be changed after function return relative to the state at function entry.
