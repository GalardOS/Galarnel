lmake_compatibility_version(1)

LIBSTEEL_LINKER_FILE = "lib/libsteel/linker/linker.ld"
LIBSTEEL_OBJECT_FILES = ""

INCLUDE_DIRECTORIES = "Isrc/ "

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
    source_files = lmake_find("src/**.cc")
    asm_files = lmake_find("src/**.S")
end
