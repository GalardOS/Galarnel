lmake_compatibility_version(1)

COMPILER = "/bin/clang"
LINKER = "/bin/ld.lld"
CXX_FLAGS = "-Wall -nostdlib -ffreestanding -Isrc -Isrc/klib -Isrc/kernel -mgeneral-regs-only"
ASM_FLAGS = "-Isrc"

ARCH = "aarch64"
CLANG_TARGET = ""
LLD_TARGET = ""

if ARCH == "aarch64" then
    CLANG_TARGET = "--target=aarch64 "
    LLD_TARGET = "-m aarch64elf "
end

function build()
    lmake_set_compiler(COMPILER)
    compile_kernel()
    compile_klib()
    compile_hal()

    lmake_set_linker(LINKER)
    lmake_set_linker_flags(LLD_TARGET .. "-T linker/linker.ld")
    lmake_set_linker_out("build/kernel8.elf")
    lmake_link("build/boot.S.o build/kernel.cc.o build/mini_uart.cc.o build/pre_kernel.S.o build/utils.S.o build/cstring.cc.o build/klib.cc.o build/printf.cc.o")
end

function compile_kernel()
    lmake_set_compiler_flags(CLANG_TARGET ..  CXX_FLAGS)
    lmake_set_compiler_out("build/%.o")
    lmake_compile("src/kernel/kernel.cc src/kernel/mini_uart.cc")

    lmake_set_compiler_flags(CLANG_TARGET .. ASM_FLAGS)
    lmake_compile("src/kernel/boot.S src/kernel/pre_kernel.S src/kernel/utils.S")
end

function compile_klib()
    lmake_set_compiler_flags(CLANG_TARGET .. CXX_FLAGS)
    lmake_set_compiler_out("build/%.o")
    lmake_compile("src/klib/cstring.cc src/klib/klib.cc src/klib/printf.cc")
end

function compile_hal()
    lmake_set_compiler_flags(CLANG_TARGET .. CXX_FLAGS)
    lmake_set_compiler_out("build/%.o")
    lmake_compile("src/hal/cpu.cc src/hal/excpt.cc")

    if ARCH == "aarch64" then
        lmake_compile("src/hal/aarch64/aarch64_excpt.c")
        lmake_set_compiler_flags(CLANG_TARGET .. ASM_FLAGS)
        lmake_compile("src/hal/aarch64/aarch64_cpu.S src/hal/aarch64/aarch64_excpt.S src/hal/aarch64/aarch64_sysregs.S")
    end
end