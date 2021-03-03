lmake_compatibility_version(1)

LIBSTEEL_LINKER_FILE = "lib/libsteel/linker/linker.ld"
LIBSTEEL_OBJECT_FILES = ""

function prepare_libraries()
    lmake_chdir("lib/libsteel")

    lmake_exec("lmake build")
    LIBSTEEL_OBJECT_FILES = lmake_find("lib/libsteel/bin/*.o")
   
    lmake_chdir("../../")
end

function build()
    lmake_error("Not implemented yet")

    source_files = lmake_find("src/**.cc")
    asm_files = lmake_find("src/**.S")
end