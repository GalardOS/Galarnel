lmake_compatibility_version(1)

lmake_include("lib/libsteel/lmake.lua")

LIBSTEEL_LINKER_FILE = "lib/libsteel/linker/linker.ld"

INCLUDE_DIRECTORIES = "-Isrc/ -Ilib/libsteel/lib"

function prepare_libraries()
    -- Build the library
    lmake_chdir("lib/libsteel")
    lmake_exec("lmake lib")
    lmake_chdir("../../")

    -- Copy the binary
    lmake_exec("mv lib/libsteel/bin/libsteel.a lib/bin/libsteel.a")

    -- Setup include directory
    INCLUDE_DIRECTORIES = INCLUDE_DIRECTORIES .. "Ilib/libsteel/lib "
end

function build()
    local additional_compilation_flags = INCLUDE_DIRECTORIES

    local source_files = lmake_find("src/**.cc")
    local asm_files = lmake_find("src/**.S")

    compile_files(source_files, asm_files, additional_compilation_flags)

    local obj_files = lmake_find("bin/**.o")
    link_executable(obj_files, LIBSTEEL_LINKER_FILE)
end
