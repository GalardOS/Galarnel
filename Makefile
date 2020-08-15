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

CC ?= clang --target=aarch64-elf
LD ?= aarch64-linux-gnu-ld
OBJCOPY ?= aarch64-linux-gnu-objcopy

SOURCE_DIR = src
INCLUDE_DIRS = -Isrc -Isrc/klib -Isrc/kernel

ALL_CC_FLAGS = -Wall -nostdlib -ffreestanding -mgeneral-regs-only -MMD $(INCLUDE_DIRS)
ALL_C_FLAGS = -Wall -nostdlib -ffreestanding -mgeneral-regs-only -MMD $(INCLUDE_DIRS)
ALL_ASM_FLAGS = $(INCLUDE_DIRS)

# Get all the source files (.c .cc and .S)
C_SOURCE_FILES = $(shell find $(SOURCE_DIR) -name '*.c')
CC_SOURCE_FILES = $(shell find $(SOURCE_DIR) -name '*.cc')
ASM_SOURCE_FILES = $(shell find $(SOURCE_DIR) -name '*.S')

OBJECT_FILES = $(addsuffix .o,$(basename $(C_SOURCE_FILES)))
OBJECT_FILES += $(addsuffix .o,$(basename $(CC_SOURCE_FILES))))
OBJECT_FILES += $(addsuffix .o,$(basename $(ASM_SOURCE_FILES)))

all: kernel8.img

build/%.o: src/%.c 
	$(CC) -c $< -o $@ $(ALL_C_FLAGS)

build/%.o: src/%.cc
	$(CC) -c $< -o $@ $(ALL_CC_FLAGS)

build/%.o: src/%.S 
	$(CC) -c $< -o $@ $(ALL_ASM_FLAGS)

clean:
	rm -rf build/*.o build/*.d build/*.elf kernel8.img

kernel8.img: LD/LD.ld $(OBJECT_FILES)
	$(LD) -T LD/LD.ld -o build/kernel8.elf $(OBJECT_FILES)
	$(OBJCOPY) build/kernel8.elf -O binary kernel8.img
