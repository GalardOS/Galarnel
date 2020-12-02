lmake_compatibility_version(1)

lmake_include("build/config.lua")

function build()
    -- Compiler C and C++ files
    lmake_set_compiler(CONFIGURATION_COMPILER)
    lmake_set_compiler_flags(CXX_COMPILER_FLAGS)
    lmake_set_compiler_out("build/obj/%.o")
    lmake_compile(C_SOURCE_FILES .. " " .. CC_SOURCE_FILES)

    -- Compile assembly files
    lmake_set_compiler_flags(ASM_COMPILER_FLAGS)
    lmake_compile(ASM_SOURCE_FILES)

    -- Link all the files 
    obj_files = lmake_find("build/obj/*.o")
    lmake_set_linker(CONFIGURATION_LINKER)
    lmake_set_linker_flag(LINKER_FLAGS)
    lmake_set_linker_out("build/galarnel.elf")
    lmake_link(obj_files)
end

function clean()
    obj_files = lmake_find("build/obj/*.o")
    lmake_exec("rm " .. obj_files)
end