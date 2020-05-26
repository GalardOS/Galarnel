ARMGNU ?= aarch64-linux-gnu

COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Isrc -Isrc/klib -Isrc/kernel -mgeneral-regs-only
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
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_c.o: $(KERNEL_SRC)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_cc.o: $(KERNEL_SRC)/%.cc
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# Klib
$(BUILD_DIR)/%_cc.o: $(KLIB_SRC)/%.cc
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@


$(BUILD_DIR)/%_s.o: $(KLIB_SRC)/%.S
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

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
	$(ARMGNU)-ld -T $(LINKER_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
