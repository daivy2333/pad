#![feature(panic_info_message)]
#![no_std]
#![no_main]

mod lang_items;
mod sbi;

use core::arch::global_asm;

global_asm!(include_str!("entry.asm"));
#[macro_use]
mod console;

#[unsafe(no_mangle)]
pub fn rust_main() -> !
{
    clear_bss();
    println!("hello world!");
    panic!("manba out!")
}

fn clear_bss()
{
    // 1. 声明外部符号，这里需要 unsafe (新版 Rust 要求)
    unsafe extern "C" {
        fn sbss();
        fn ebss();
    }

    // 2. 使用这些符号，这里的作用域依然有效
    (sbss as usize..ebss as usize).for_each(|a|{
        unsafe {
            (a as *mut u8).write_volatile(0);
        }
    });
}

/*

cargo build --release
rust-objcopy --strip-all target/riscv64gc-unknown-none-elf/release/os -O binary target/riscv64gc-unknown-none-elf/release/os.bin
qemu-system-riscv64     -machine virt     -nographic     -bios ./bootloader/rustsbi-qemu.bin     -device loader,file=target/riscv64gc-unknown-none-elf/release/os.bin,addr=0x80200000 

*/