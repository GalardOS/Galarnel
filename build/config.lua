-- These are the available configuration platforms
--      * bcm2711
CONFIGURATION_PLATFORM = "bcm2711"

-- Include the platform configuration
lmake_include("build/configs/" .. CONFIGURATION_PLATFORM .. ".lua")

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