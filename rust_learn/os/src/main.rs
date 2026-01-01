#![no_std]
#![no_main]

mod lang_items;
mod sbi;
mod log;

use core::arch::global_asm;

global_asm!(include_str!("entry.asm"));
#[macro_use]
mod console;

use log::LogLevel;
use log::init;

#[unsafe(no_mangle)]
pub fn rust_main() -> !
{
    clear_bss();
    
    // 初始化日志系统
    init(LogLevel::Debug);
    
    crate::log::_log(LogLevel::Info, format_args!("avt"));

    // 测试不同级别的日志
    crate::log::_log(LogLevel::Error, format_args!("ero"));
    crate::log::_log(LogLevel::Warn, format_args!("warn"));
    crate::log::_log(LogLevel::Info, format_args!("note"));
    crate::log::_log(LogLevel::Debug, format_args!("debug"));
    crate::log::_log(LogLevel::Trace, format_args!("trace"));

    // 显示内存布局
    let s_text = 0x8020_0000usize;
    let e_text = 0x8021_0000usize;
    let s_rodata = 0x8021_0000usize;
    let e_rodata = 0x8022_0000usize;
    let s_data = 0x8022_0000usize;
    let e_data = 0x8023_0000usize;

    crate::log::_log(LogLevel::Info, format_args!(".text [{:#x}, {:#x})", s_text, e_text));
    crate::log::_log(LogLevel::Info, format_args!(".rodata [{:#x}, {:#x})", s_rodata, e_rodata));
    crate::log::_log(LogLevel::Info, format_args!(".data [{:#x}, {:#x})", s_data, e_data));

    // 切换日志级别
    crate::log::_log(LogLevel::Info, format_args!("turn INFO"));
    log::set_max_level(LogLevel::Info);

    // 这些不会输出
    crate::log::_log(LogLevel::Debug, format_args!("no put"));
    crate::log::_log(LogLevel::Trace, format_args!("above too"));

    // 这些会输出
    crate::log::_log(LogLevel::Error, format_args!("err stiil"));
    crate::log::_log(LogLevel::Warn, format_args!("warn stiil"));
    crate::log::_log(LogLevel::Info, format_args!("info level"));


    
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
    (sbss as *const () as usize..ebss as *const () as usize).for_each(|a|{
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