lmake_compatibility_version(1)

COMPILER = "/bin/aarch64-linux-gnu-gcc"
LINKER = "/bin/aarch64-linux-gnu-ld"
C_FLAGS = "-Wall -nostdlib -ffreestanding -Isrc -Isrc/klib -Isrc/kernel -mgeneral-regs-only"
ASM_FLAGS = "-Isrc"

function build()
    lmake_exec("mkdir -p bin/")

    local asm_files = lmake_find("src/**.S")
    local c_files = lmake_find("src/**.c")

    lmake_set_compiler(COMPILER)
    lmake_set_compiler_out("bin/%.o")
    lmake_set_compiler_flags(C_FLAGS)
    lmake_compile(c_files)
    lmake_set_compiler_flags(ASM_FLAGS)
    lmake_compile(asm_files)

    local obj = lmake_find("bin/*.o")
    lmake_set_linker(LINKER)
    lmake_set_linker_flags("-T linker/linker.ld")
    lmake_set_linker_out("bin/iquernel.elf")
    lmake_link(obj)
    lmake_exec("aarch64-linux-gnu-objcopy bin/iquernel.elf -O binary kernel8.img")
end

function run()
    lmake_exec("qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio -d int")
end

function clean()
    local obj = lmake_find("bin/*.o")
    lmake_exec("rm -f " .. obj)
end