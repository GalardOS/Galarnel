lmake_compatibility_version(1)

COMPILER = "/bin/clang"
LINKER = "/bin/ld.lld"
CXX_FLAGS = "-Wall -nostdlib -ffreestanding -Isrc -Isrc/klib -Isrc/kernel -mgeneral-regs-only"
ASM_FLAGS = "-Isrc"


function build()
    lmake_set_compiler(COMPILER)
    compile_kernel()
    compile_klib()

    lmake_set_linker(LINKER)
    lmake_set_linker_flags("-m aarch64elf -T linker/linker.ld")
    lmake_set_linker_out("build/kernel8.elf")
    lmake_link("build/boot.S.o build/cpu.S.o build/kernel.cc.o build/mini_uart.cc.o build/pre_kernel.S.o build/utils.S.o build/cstring.cc.o build/klib.cc.o build/printf.cc.o")
end

function compile_kernel()
    lmake_set_compiler_flags("--target=aarch64 " ..  CXX_FLAGS)
    lmake_set_compiler_out("build/%.o")
    lmake_compile("src/kernel/kernel.cc src/kernel/mini_uart.cc")

    lmake_set_compiler_flags("--target=aarch64 " .. ASM_FLAGS)
    lmake_compile("src/kernel/boot.S src/kernel/cpu.S src/kernel/pre_kernel.S src/kernel/utils.S")
end

function compile_klib()
    lmake_set_compiler_flags("--target=aarch64 " .. CXX_FLAGS)
    lmake_set_compiler_out("build/%.o")
    lmake_compile("src/klib/cstring.cc src/klib/klib.cc src/klib/printf.cc")
end
