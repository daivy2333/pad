<pir>
<meta>
name: os
root: /home/daivy/projects/pad/rust_learn/os
profile: generic
lang: ASM,LD,Rust
</meta>
<units>
u0: src/linker.ld type=LD role=lib module=src
u1: src/lang_items.rs type=Rust role=lib module=src
u2: src/sbi.rs type=Rust role=lib module=src
u3: src/entry.asm type=ASM role=lib module=src
u4: src/console.rs type=Rust role=lib module=src
u5: src/main.rs type=Rust role=lib module=src
u6: src/log/timestamp.rs type=Rust role=lib module=log
u7: src/log/level.rs type=Rust role=lib module=log
u8: src/log/config.rs type=Rust role=lib module=log
u9: src/log/context.rs type=Rust role=lib module=log
u10: src/log/macros.rs type=Rust role=lib module=log
u11: src/log/mod.rs type=Rust role=lib module=log
</units>
<dependency-pool>
d0: call:u5#rust_main
d1: use:[$crate::log::_log]
d2: use:[$crate::log::_log_advanced]
d3: use:[core::arch::global_asm]
d4: use:[core::fmt::{self,Write}]
d5: use:[core::fmt]
d6: use:[core::panic::PanicInfo]
d7: use:[core::sync::atomic::{AtomicU32, Ordering}]
d8: use:[core::sync::atomic::{AtomicU64, Ordering}]
d9: use:[core::sync::atomic::{AtomicU8, Ordering}]
d10: use:[crate::console::{write_str, putchar}]
d11: use:[crate::sbi::console_putchar]
d12: use:[crate::{sbi::shutdown}]
d13: use:[log::LogLevel]
d14: use:[log::init]
d15: use:[sbi_rt::{system_reset, NoReason, Shutdown, SystemFailure}]
d16: use:[spin::Mutex]
d17: use:[spin::Once]
</dependency-pool>
<dependencies>
u1->refs:[d6 d12]
u2->refs:[d15]
u3->refs:[d0]
u4->refs:[d4 d11]
u5->refs:[d13 d3 d14]
u6->refs:[d8 d10]
u7->refs:[d5]
u8->refs:[d17]
u9->refs:[d7]
u10->refs:[d1 d2]
u11->refs:[d10 d9 d5 d16]
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
console_putchar:u2 func
shutdown:u2 func
_start:u3 label
boot_stack_lower_bound:u3 label
boot_stack_top:u3 label
write_str:u4 func
putchar:u4 func
write_str:u4 func
print:u4 func
Stdout:u4 struct
rust_main:u5 func
clear_bss:u5 func
update_nanos:u6 func
current_timestamp:u6 func
format_timestamp:u6 func
write_num:u6 func
as_str:u7 func
color:u7 func
reset_color:u7 func
fmt:u7 func
LogLevel:u7 enum
default:u8 func
init_config:u8 func
config:u8 func
LogConfig:u8 struct
current_cpu_id:u9 func
set_current_thread_id:u9 func
current_thread_id:u9 func
set_thread_name:u9 func
thread_name:u9 func
init:u11 func
set_max_level_silent:u11 func
set_max_level:u11 func
get_max_level:u11 func
should_log:u11 func
_log:u11 func
_log_advanced:u11 func
u8_slice_to_str:u11 func
</symbols>
</pir>