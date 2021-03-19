lmake_compatibility_version(1)

-- Settings for compiling
COMPILER = "/bin/clang"
LINKER = "/bin/aarch64-linux-gnu-ld"
CXX_FLAGS = "--target=aarch64 -Wall -nostdlib -ffreestanding -Ilib -Isrc/klib -Isrc/kernel -mgeneral-regs-only"
ASM_FLAGS = "--target=aarch64 -Ilib -nostdlib"

LIBSTEEL_LINKER_FILE = "libraries/libsteel/linker/linker.ld"

INCLUDE_DIRECTORIES = "-I./src/ -I./libraries/"

function build_librariesraries()
    local cc_source_files = lmake_find("libraries/libsteel/**.cc")
    local asm_source_files = lmake_find("libraries/libsteel/**.S")
    compile_files(cc_source_files, asm_source_files, "-Ilibraries/libsteel")
end

function compile_files(cpp_files, asm_files, include_dirs)
    lmake_set_compiler(COMPILER)
    lmake_set_compiler_flags(CXX_FLAGS .. " " .. include_dirs)
    lmake_set_compiler_out("bin/%.o")
    lmake_compile(cpp_files)

    lmake_set_compiler_flags(ASM_FLAGS .. " " .. include_dirs)
    lmake_compile(asm_files)
end

function link_executable(obj_files, linker_path)
    lmake_set_linker(LINKER)
    lmake_set_linker_flags("-T linker/linker.ld")
    lmake_set_linker_out("bin/kernel.elf")
    lmake_link(obj_files)
end

function build()
    -- Build librariesraries
    build_librariesraries()

    -- Build the kernel
    local additional_compilation_flags = INCLUDE_DIRECTORIES
    local source_files = lmake_find("src/**.cc")
    local asm_files = lmake_find("src/**.S")
    compile_files(source_files, asm_files, additional_compilation_flags)

    local obj_files = lmake_find("bin/**.o")
    link_executable(obj_files, LIBSTEEL_LINKER_FILE)
    lmake_exec("aarch64-linux-gnu-objcopy bin/kernel.elf -O binary kernel8.img")
end

function clean()
    local to_remove = lmake_find("bin/**.o")
    lmake_exec("rm -f " .. to_remove)
end

function run()
    lmake_exec("qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio -d int")
end