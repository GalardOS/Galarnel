-- These are the available configuration platforms
--      * bcm2711
CONFIGURATION_PLATFORM = "bcm2711"

lmake_include("build/configs/" .. CONFIGURATION_PLATFORM .. ".lua")