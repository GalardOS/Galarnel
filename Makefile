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

COMPILER ?= clang --target=aarch64-elf
LINKER ?= aarch64-linux-gnu-ld
OBJCOPY ?= aarch64-linux-gnu-objcopy

COPS = -Wall -nostdlib -ffreestanding -Isrc -Isrc/klib -Isrc/kernel -mgeneral-regs-only
ASMOPS = -Isrc 

BUILD_DIR = build
KLIB_SRC = src/klib
KERNEL_SRC = src/kernel
LINKER_DIR = linker

all : kernel8.img

clean :
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(BUILD_DIR)/*.elf kernel8.img

# Kernel files
$(BUILD_DIR)/%_s.o: $(KERNEL_SRC)/%.S
	$(COMPILER) $(ASMOPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_c.o: $(KERNEL_SRC)/%.c
	mkdir -p $(@D)
	$(COMPILER) $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_cc.o: $(KERNEL_SRC)/%.cc
	mkdir -p $(@D)
	$(COMPILER) $(COPS) -MMD -c $< -o $@

# Klib
$(BUILD_DIR)/%_cc.o: $(KLIB_SRC)/%.cc
	$(COMPILER) $(COPS) -MMD -c $< -o $@


$(BUILD_DIR)/%_s.o: $(KLIB_SRC)/%.S
	$(COMPILER) $(ASMOPS) -MMD -c $< -o $@

KERNEL_ASM_FILES = $(wildcard $(KERNEL_SRC)/*.S)
KERNEL_C_FILES = $(wildcard $(KERNEL_SRC)/*.c)
KERNEL_CC_FILES = $(wildcard $(KERNEL_SRC)/*.cc)

KLIB_ASM_FILES = $(wildcard $(KLIB_DIR)/*.S)
KLIB_CC_FILES = $(wildcard src/klib/*.cc)

OBJ_FILES = $(KERNEL_ASM_FILES:$(KERNEL_SRC)/%.S=$(BUILD_DIR)/%_s.o)
OBJ_FILES += $(KERNEL_C_FILES:$(KERNEL_SRC)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(KERNEL_CC_FILES:$(KERNEL_SRC)/%.cc=$(BUILD_DIR)/%_cc.o)
OBJ_FILES += $(KLIB_CC_FILES:$(KLIB_SRC)/%.cc=$(BUILD_DIR)/%_cc.o)
OBJ_FILES += $(KLIB_ASM_FILES:$(KLIB_SRC)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(LINKER_DIR)/linker.ld $(OBJ_FILES)
	$(LINKER) -T $(LINKER_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(OBJCOPY) $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
