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
    c_cc_files = lmake_find("src/**.c") .. lmake_find("src/**.cc")
    asm_files = lmake_find("src/**.S")

    lmake_set_compiler(COMPILER)
    lmake_set_compiler_flags(CLANG_TARGET .. CXX_FLAGS)
    lmake_set_compiler_out("build/%.o")
    lmake_compile(c_cc_files)

    lmake_set_compiler_flags(CLANG_TARGET .. ASM_FLAGS)
    lmake_compile(asm_files)

    obj_files = lmake_find("build/*.o")

    lmake_set_linker(LINKER)
    lmake_set_linker_flags(LLD_TARGET .. "-T linker/linker.ld")
    lmake_set_linker_out("build/kernel.elf")
    lmake_link(obj_files)

    -- TODO: Create the .img bootable file
end

function clean()
    obj_files = lmake_find("build/*")
    lmake_exec("rm " .. obj_files)
end