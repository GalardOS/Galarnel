-- These are the available configuration platforms
--      * bcm2711
CONFIGURATION_PLATFORM = "bcm2711"

CONFIGURATION_COMPILER = "clang"
CONFIGURATION_LINKER = "ld.lld" 

-- Include the platform configuration
lmake_include("build/configs/" .. CONFIGURATION_PLATFORM .. ".lua")

-- Set the target for the compiler and linker
if CONFIGURATION_ISA == "aarch64" then
    COMPILER_TARGET = "--target=aarch64"
    LINKER_TARGET = "-m aarch64elf"
else
    lmake_error("Unkown ISA")
end

-- Construct the compiler flags
CXX_COMPILER_FLAGS = COMPILER_TARGET .. " -Wall -nostdlib -ffreestanding -Isrc -Isrc/klib -Isrc/kernel -mgeneral-regs-only"
ASM_COMPILER_FLAGS = COMPILER_TARGET .. " -Isrc"

-- Construct the linker flags
LINKER_FLAGS = LINKER_TARGET .. " -T linker/linker.ld"

-- Variables to be used in lmake.lua for compiling and linking
C_SOURCE_FILES = ""
CC_SOURCE_FILES = ""
ASM_SOURCE_FILES = ""

-- Add configured driver source files
for i in 1, #CONFIGURATION_BAKED_DRIVERS do
    local driver = CONFIGURATION_BAKED_DRIVERS[i]
    C_SOURCE_FILES = C_SOURCE_FILES .. lmake_find("drivers/" .. driver .. "/**.c")
    CC_SOURCE_FILES = CC_SOURCE_FILES .. lmake_find("drivers/" .. driver .. "/**.cc")
end

-- Add ISA source files
C_SOURCE_FILES = C_SOURCE_FILES .. lmake_find("arch/" .. CONFIGURATION_ISA .. "/**.c")
CC_SOURCE_FILES = C_SOURCE_FILES .. lmake_find("arch/" .. CONFIGURATION_ISA .. "/**.cc")
ASM_SOURCE_FILES = C_SOURCE_FILES .. lmake_find("arch/" .. CONFIGURATION_ISA .. "/**.S")