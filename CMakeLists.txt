#
# This project is provided under the GNU GPL v2 license, more information can 
# found on https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
# 
# Authors:
#    - Iker Galardi
# 

cmake_minimum_required(VERSION 3.1)
enable_language(C ASM CXX)

project(Galarnel)

# Set the compiler
set(COMPILER "/usr/bin/clang")
set(CMAKE_C_COMPILER ${COMPILER})
set(CMAKE_CXX_COMPILER ${COMPILER})
set(CMAKE_ASM_COMPILER ${COMPILER})

# Set the linker
set(LINKER "/usr/bin/aarch64-linux-gnu-ld")
set(CMAKE_LINKER ${LINKER})

# Setup compiler and linker flags
set(CMAKE_CXX_FLAGS "--target=aarch64 -Wall -nostdlib -ffreestanding -mgeneral-regs-only")
set(CMAKE_C_FLAGS "--target=aarch64 -Wall -nostdlib -ffreestanding -mgeneral-regs-only")
set(CMAKE_ASM_FLAGS "--target=aarch64")
set(LINKER_SCRIPT "../linker/linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKER_SCRIPT} -v")

# Set the sources directory
set(CMAKE_SOURCE_DIR "src")


# kernel source files
file(GLOB kernel_asm src/kernel/*.S)
file(GLOB kernel_c src/kernel/*.c)
file(GLOB kernel_cc src/kernel/*.cc)

# klib source files
file(GLOB klib_asm src/klib/*.S)
file(GLOB klib_c src/klib/*.c)
file(GLOB klib_cc src/klib/*.cc)

# Set the project include directories
include_directories("src/klib" "src/kernel")

# Add source files to the executable image
add_executable(kernel8.elf
               ${kernel_asm} 
               ${kernel_c} 
               ${kernel_cc}
               ${klib_asm} 
               ${klib_c} 
               ${klib_cc})

# Post install scripts
add_custom_command(OUTPUT kernel8.elf
                   POST_BUILD
                   COMMAND /bin/sh "post_compile.sh")