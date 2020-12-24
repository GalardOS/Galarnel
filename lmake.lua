lmake_compatibility_version(1)

CPP = "/bin/gcc"
AS = "/bin/as"
LINKER = "/bin/ld"
CXX_FLAGS = "-Isrc -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore"
ASM_FLAGS = "-Isrc --32"

CC_SOURCE = "src/kernel/kernel.cc src/pal/platform/pc99/debug.cc src/pal/platform/pc99/pre_configuration.cc src/pal/platform/pc99/cpu.cc"
ASM_SOURCE = "src/pal/platform/pc99/boot.S"

OBJECT_FILES = "build/kernel.cc.o build/debug.cc.o build/pre_configuration.cc.o build/cpu.cc.o build/boot.S.o"

function build()
    -- Compile C++ files
    lmake_set_compiler(CPP)
    lmake_set_compiler_flags(CXX_FLAGS)
    lmake_set_compiler_out("build/%.o")
    lmake_compile(CC_SOURCE)
   
    -- Compile assembly files
    lmake_set_compiler(AS)
    lmake_set_compiler_flags(ASM_FLAGS)
    lmake_compile(ASM_SOURCE)

    -- Build multiboot image
    OBJECT_FILES = lmake_find("build/*.o")
    lmake_set_linker(LINKER)
    lmake_set_linker_flags("-T linker/pc99.ld")
    lmake_set_linker_out("build/kernel.bin")
    lmake_link(OBJECT_FILES)
end

function run()
    build()
    lmake_exec("qemu-system-i386 -kernel build/kernel.bin")
end

function clean()
    lmake_exec("rm -f " .. OBJECT_FILES)
end