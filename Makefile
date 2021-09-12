kernel_source_files := $(shell find src/ -name *.cpp)
kernel_object_files := $(patsubst src/%.cpp, build/src/%.o, $(kernel_source_files))

x86_64_asm_source_files := $(shell find asm/ -name *.asm)
x86_64_asm_object_files := $(patsubst asm/%.asm, build/asm/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_asm_object_files)

$(kernel_object_files): build/src/%.o : src/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -c -I src/ -fpermissive -ffreestanding $(patsubst build/src/%.o, src/%.cpp, $@) -o $@

$(x86_64_asm_object_files): build/asm/%.o : asm/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/asm/%.o, asm/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso
