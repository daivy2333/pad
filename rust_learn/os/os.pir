<pir>
<meta>
name: os
root: /home/daivy/projects/pad/rust_learn/os
profile: generic
lang: ASM,LD,Rust,S
</meta>
<units>
u0: src/linker.ld type=LD role=lib module=src
u1: src/lang_items.rs type=Rust role=lib module=src
u2: src/batch.rs type=Rust role=lib module=src
u3: src/link_app.S type=S role=lib module=src
u4: src/sbi.rs type=Rust role=lib module=src
u5: src/entry.asm type=ASM role=lib module=src
u6: src/console.rs type=Rust role=lib module=src
u7: src/main.rs type=Rust role=lib module=src
u8: src/syscall/process.rs type=Rust role=lib module=syscall
u9: src/syscall/mod.rs type=Rust role=lib module=syscall
u10: src/syscall/fs.rs type=Rust role=lib module=syscall
u11: src/log/timestamp.rs type=Rust role=lib module=log
u12: src/log/level.rs type=Rust role=lib module=log
u13: src/log/config.rs type=Rust role=lib module=log
u14: src/log/context.rs type=Rust role=lib module=log
u15: src/log/macros.rs type=Rust role=lib module=log
u16: src/log/mod.rs type=Rust role=lib module=log
u17: src/trap/context.rs type=Rust role=lib module=trap
u18: src/trap/mod.rs type=Rust role=lib module=trap
u19: src/trap/trap.S type=S role=lib module=trap
u20: src/sync/up.rs type=Rust role=lib module=sync
u21: src/sync/mod.rs type=Rust role=lib module=sync
</units>
<dependency-pool>
d0: call:u18#trap_handler
d1: call:u7#rust_main
d2: use:[$crate::log::_log]
d3: use:[$crate::log::_log_advanced]
d4: use:[core::arch::global_asm]
d5: use:[core::cell::{RefCell, RefMut}]
d6: use:[core::fmt::{self, Write}]
d7: use:[core::fmt::{self,Write}]
d8: use:[core::fmt]
d9: use:[core::panic::PanicInfo]
d10: use:[core::sync::atomic::{AtomicU32, Ordering}]
d11: use:[core::sync::atomic::{AtomicU64, Ordering}]
d12: use:[core::sync::atomic::{AtomicU8, Ordering}]
d13: use:[crate::batch::run_next_app]
d14: use:[crate::console::{write_str, putchar}]
d15: use:[crate::print]
d16: use:[crate::println]
d17: use:[crate::sbi::console_putchar]
d18: use:[crate::sync::UPSafeCell]
d19: use:[crate::syscall::syscall]
d20: use:[crate::trap::TrapContext]
d21: use:[crate::{sbi::shutdown}]
d22: use:[fs::sys_write]
d23: use:[lazy_static::lazy_static]
d24: use:[log::LogLevel]
d25: use:[log::init]
d26: use:[process::sys_exit]
d27: use:[riscv::register::scause::{Trap, Exception}]
d28: use:[riscv::register::sstatus::{self, Sstatus, SPP}]
d29: use:[riscv::register::stvec::TrapMode]
d30: use:[riscv::register::{stvec, stval, scause}]
d31: use:[sbi_rt::{system_reset, NoReason, Shutdown, SystemFailure}]
d32: use:[spin::Mutex]
d33: use:[spin::Once]
</dependency-pool>
<dependencies>
u1->refs:[d9 d21]
u2->refs:[d18 d20 d23]
u4->refs:[d31]
u5->refs:[d1]
u6->refs:[d7 d17]
u7->refs:[d25 d24 d4]
u8->refs:[d16 d13]
u9->refs:[d26 d22]
u10->refs:[d15]
u11->refs:[d11 d14]
u12->refs:[d8]
u13->refs:[d33]
u14->refs:[d10]
u15->refs:[d3 d2]
u16->refs:[d12 d6 d32 d14]
u17->refs:[d28]
u18->refs:[d29 d4 d27 d16 d13 d19 d30]
u19->refs:[d0]
u20->refs:[d5]
</dependencies>
<symbols>
_start:u0 ld_entry
skernel:u0 ld_symbol
stext:u0 ld_symbol
etext:u0 ld_symbol
srodata:u0 ld_symbol
erodata:u0 ld_symbol
sdata:u0 ld_symbol
edata:u0 ld_symbol
sbss:u0 ld_symbol
ebss:u0 ld_symbol
ekernel:u0 ld_symbol
panic:u1 func
get_current_app:u2 func
move_to_next_app:u2 func
get_sp:u2 func
push_context:u2 func
run_next_app:u2 func
AppManager:u2 struct
KernelStack:u2 struct
UserStack:u2 struct
_num_app:u3 label
console_putchar:u4 func
shutdown:u4 func
_start:u5 label
boot_stack_lower_bound:u5 label
boot_stack_top:u5 label
write_str:u6 func
putchar:u6 func
write_str:u6 func
print:u6 func
Stdout:u6 struct
rust_main:u7 func
clear_bss:u7 func
sys_exit:u8 func
sys_write:u10 func
update_nanos:u11 func
current_timestamp:u11 func
format_timestamp:u11 func
write_num:u11 func
as_str:u12 func
color:u12 func
reset_color:u12 func
fmt:u12 func
LogLevel:u12 enum
default:u13 func
init_config:u13 func
config:u13 func
LogConfig:u13 struct
current_cpu_id:u14 func
set_current_thread_id:u14 func
current_thread_id:u14 func
set_thread_name:u14 func
thread_name:u14 func
init:u16 func
set_max_level_silent:u16 func
set_max_level:u16 func
get_max_level:u16 func
should_log:u16 func
_log:u16 func
write_str:u16 func
_log_advanced:u16 func
write_str:u16 func
u8_slice_to_str:u16 func
LogWriter:u16 struct
LogWriter:u16 struct
set_sp:u17 func
app_init_context:u17 func
TrapContext:u17 struct
init:u18 func
trap_handler:u18 func
__alltraps:u19 label
__restore:u19 label
exclusive_access:u20 func
UPSafeCell:u20 struct
</symbols>
</pir>