<pir>
<meta>
name: rcore_re
root: /home/daivy/projects/pad/rust_learn/rcore_re
profile: generic
lang: ASM,LD,PY,Rust,S
</meta>
<units>
u0: user/build.py type=PY role=lib module=user
u1: user/src/linker.ld type=LD role=lib module=src
u2: user/src/syscall.rs type=Rust role=lib module=src
u3: user/src/lang_items.rs type=Rust role=lib module=src
u4: user/src/lib.rs type=Rust role=lib module=src
u5: user/src/console.rs type=Rust role=lib module=src
u6: user/src/bin/03.rs type=Rust role=lib module=bin
u7: user/src/bin/02.rs type=Rust role=lib module=bin
u8: user/src/bin/01.rs type=Rust role=lib module=bin
u9: user/src/bin/04.rs type=Rust role=lib module=bin
u10: os/build.rs type=Rust role=lib module=os
u11: os/src/linker-qemu.ld type=LD role=lib module=src
u12: os/src/timer.rs type=Rust role=lib module=src
u13: os/src/lang_items.rs type=Rust role=lib module=src
u14: os/src/config.rs type=Rust role=lib module=src
u15: os/src/loader.rs type=Rust role=lib module=src
u16: os/src/logging.rs type=Rust role=lib module=src
u17: os/src/link_app.S type=S role=lib module=src
u18: os/src/sbi.rs type=Rust role=lib module=src
u19: os/src/entry.asm type=ASM role=lib module=src
u20: os/src/console.rs type=Rust role=lib module=src
u21: os/src/main.rs type=Rust role=lib module=src
u22: os/src/syscall/process.rs type=Rust role=lib module=syscall
u23: os/src/syscall/mod.rs type=Rust role=lib module=syscall
u24: os/src/syscall/fs.rs type=Rust role=lib module=syscall
u25: os/src/trap/context.rs type=Rust role=lib module=trap
u26: os/src/trap/mod.rs type=Rust role=lib module=trap
u27: os/src/trap/trap.S type=S role=lib module=trap
u28: os/src/boards/qemu.rs type=Rust role=lib module=boards
u29: os/src/sync/up.rs type=Rust role=lib module=sync
u30: os/src/sync/mod.rs type=Rust role=lib module=sync
u31: os/src/task/switch.S type=S role=lib module=task
u32: os/src/task/context.rs type=Rust role=lib module=task
u33: os/src/task/task.rs type=Rust role=lib module=task
u34: os/src/task/switch.rs type=Rust role=lib module=task
u35: os/src/task/mod.rs type=Rust role=lib module=task
</units>
<dependency-pool>
d0: call:u21#rust_main
d1: call:u26#trap_handler
d2: import:[stdlib:py]
d3: use:[core::arch::asm]
d4: use:[core::arch::global_asm]
d5: use:[core::cell::{RefCell, RefMut}]
d6: use:[core::fmt::{self, Write}]
d7: use:[core::panic::PanicInfo]
d8: use:[crate::config::*]
d9: use:[crate::config::CLOCK_FREQ]
d10: use:[crate::config::MAX_APP_NUM]
d11: use:[crate::loader::{get_num_app, init_app_cx}]
d12: use:[crate::sbi::console_putchar]
d13: use:[crate::sbi::set_timer]
d14: use:[crate::sbi::shutdown]
d15: use:[crate::sync::UPSafeCell]
d16: use:[crate::syscall::syscall]
d17: use:[crate::task::{exit_current_and_run_next, suspend_current_and_run_next}]
d18: use:[crate::timer::get_time_ms]
d19: use:[crate::timer::set_next_trigger]
d20: use:[crate::trap::TrapContext]
d21: use:[fs::*]
d22: use:[lazy_static::*]
d23: use:[log::*]
d24: use:[log::{self, Level, LevelFilter, Log, Metadata, Record}]
d25: use:[process::*]
d26: use:[riscv::register::sstatus::{self, SPP, Sstatus}]
d27: use:[riscv::register::time]
d28: use:[riscv::register::{
    mtvec::TrapMode,
    scause::{self, Exception, Interrupt, Trap},
    sie, stval, stvec,
}]
d29: use:[sbi_rt::{NoReason, Shutdown, SystemFailure, system_reset}]
d30: use:[stdlib:rust]
d31: use:[super::TaskContext]
d32: use:[super::write]
d33: use:[switch::__switch]
d34: use:[syscall::*]
d35: use:[task::{TaskControlBlock, TaskStatus}]
d36: use:[user_lib::{get_time, yield_}]
</dependency-pool>
<dependencies>
u0->refs:[d2]
u2->refs:[d3]
u4->refs:[d34]
u5->refs:[d6 d32]
u9->refs:[d36]
u10->refs:[d30]
u12->refs:[d13 d27 d9]
u13->refs:[d7 d23 d14]
u15->refs:[d8 d20 d3]
u16->refs:[d24]
u18->refs:[d29]
u19->refs:[d0]
u20->refs:[d6 d12]
u21->refs:[d4 d23]
u22->refs:[d18 d17]
u23->refs:[d25 d21]
u25->refs:[d26]
u26->refs:[d28 d4 d19 d16 d17]
u27->refs:[d1]
u29->refs:[d5]
u33->refs:[d31]
u34->refs:[d4 d31]
u35->refs:[d10 d11 d15 d14 d35 d33 d22]
</dependencies>
<symbols>
_start:u1 ld_entry
start_bss:u1 ld_symbol
end_bss:u1 ld_symbol
sys_write:u2 func
sys_exit:u2 func
sys_yield:u2 func
sys_get_time:u2 func
panic_handler:u3 func
main:u4 func entry=true
clear_bss:u4 func
write:u4 func
exit:u4 func
yield_:u4 func
get_time:u4 func
write_str:u5 func
print:u5 func
Stdout:u5 struct
main:u6 func entry=true
main:u7 func entry=true
main:u8 func entry=true
main:u9 func entry=true
main:u10 func entry=true
insert_app_data:u10 func
_start:u11 ld_entry
skernel:u11 ld_symbol
stext:u11 ld_symbol
etext:u11 ld_symbol
srodata:u11 ld_symbol
erodata:u11 ld_symbol
sdata:u11 ld_symbol
edata:u11 ld_symbol
sbss:u11 ld_symbol
ebss:u11 ld_symbol
ekernel:u11 ld_symbol
get_time:u12 func
get_time_ms:u12 func
set_next_trigger:u12 func
panic:u13 func
get_sp:u15 func
push_context:u15 func
get_sp:u15 func
get_base_i:u15 func
get_num_app:u15 func
load_apps:u15 func
init_app_cx:u15 func
KernelStack:u15 struct
UserStack:u15 struct
enabled:u16 func
log:u16 func
flush:u16 func
init:u16 func
SimpleLogger:u16 struct
_num_app:u17 label
app_0_start:u17 label
app_0_end:u17 label
app_1_start:u17 label
app_1_end:u17 label
app_2_start:u17 label
app_2_end:u17 label
app_3_start:u17 label
app_3_end:u17 label
console_putchar:u18 func
set_timer:u18 func
shutdown:u18 func
_start:u19 label
boot_stack_lower_bound:u19 label
boot_stack_top:u19 label
write_str:u20 func
print:u20 func
Stdout:u20 struct
clear_bss:u21 func
rust_main:u21 func
sys_exit:u22 func
sys_yield:u22 func
sys_get_time:u22 func
sys_write:u24 func
set_sp:u25 func
app_init_context:u25 func
TrapContext:u25 struct
init:u26 func
enable_timer_interrupt:u26 func
trap_handler:u26 func
__alltraps:u27 label
__restore:u27 label
exclusive_access:u29 func
UPSafeCell:u29 struct
__switch:u31 label
zero_init:u32 func
goto_restore:u32 func
TaskContext:u32 struct
TaskControlBlock:u33 struct
TaskStatus:u33 enum
run_first_task:u35 func
mark_current_suspended:u35 func
mark_current_exited:u35 func
find_next_task:u35 func
run_next_task:u35 func
run_first_task:u35 func
run_next_task:u35 func
mark_current_suspended:u35 func
mark_current_exited:u35 func
suspend_current_and_run_next:u35 func
exit_current_and_run_next:u35 func
TaskManager:u35 struct
TaskManagerInner:u35 struct
</symbols>
<layout>
ENTRY=_start
SECTIONS=.bss,.data,.rodata,.text
SECTIONS_FROM=u1
ENTRY=_start
SECTIONS=.bss,.data,.rodata,.text
SECTIONS_FROM=u11
</layout>
</pir>