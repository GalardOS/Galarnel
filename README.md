# Galarnel
Galarnel is the kernel in which the GalardOS operating system runs on. The kernel is the component of the operating system in charge of making an abstraction of the hardware and managing system resources such as CPU and RAM usage. This kernel is meant to be as modular as posible so that not every thing depends on only one big software that could have bugs. 

## Philosophy
Having a giant monolothic kernel can be dangerous, as the bigger the codebase is the more difficult is to maintain and develop further, but having device and filesystem drivers in kernel-space has advantages such as having the complete control over hardware. A solution for this problem is available in the linux and FreeBSD's kernel in kernel modules. 

In Galarnel we decided to take this to the limit, having the kernel just have the most basic functionality such as the memory manager, interrupt handling, process management, some basic devices such as the UART. Making little functionality available by default in the kernel makes the codebase much smaller and maintainable. With this solution we have advantages from both microkernel and monolithic kernel designs.

One big problem monolithic kernels have is that if a device driver crashes, this can cause the whole system to break (BSODs on windows for example). To solve this, we decided to treat kernel modules or drivers as user processes running on EL1. With this, the kernel can handle driver crashes as simple user-space process crashes.
