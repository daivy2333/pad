```rust
//! Uniprocessor interior mutability primitives

use core::cell::{RefCell, RefMut};
```

该模块提供单处理器（uniprocessor）环境下的内部可变性（interior mutability）原语。由于仅在单核系统中使用，无需考虑多核并发访问问题，因此可以安全地绕过 Rust 的借用检查器限制，同时避免使用 `unsafe` 代码来修改静态数据。

---

```rust
/// Wrap a static data structure inside it so that we are
/// able to access it without any `unsafe`.
///
/// We should only use it in uniprocessor.
///
/// In order to get mutable reference of inner data, call
/// `exclusive_access`.
pub struct UPSafeCell<T> {
    /// inner data
    inner: RefCell<T>,
}
```

`UPSafeCell<T>` 是一个封装了 `RefCell<T>` 的结构体，其设计目的是允许对静态存储的可变数据进行安全访问，而无需在每次访问时使用 `unsafe`。  
- **为什么用 `RefCell<T>`**：`RefCell` 提供运行时借用检查，支持在不可变上下文中获取可变引用，这在初始化为静态变量但需要后续修改的场景中非常有用。
- **为何限定于单处理器**：`RefCell` 本身不是线程安全的（不实现 `Sync`），但在单处理器系统中不存在多线程并发访问的问题，因此可以安全使用。
- **命名含义**：“UP” 表示 Uniprocessor，“SafeCell” 暗示其提供了一种在特定条件下（单核）的安全内部可变性机制。

---

```rust
unsafe impl<T> Sync for UPSafeCell<T> {}
```

此行通过 `unsafe impl Sync` 声明 `UPSafeCell<T>` 是 `Sync` 的，即可以在多个线程间安全共享。  
- **为何需要这个 impl**：默认情况下，由于 `RefCell<T>` 不是 `Sync`，包含它的结构体也不会自动实现 `Sync`。然而，在单处理器系统中，即使结构体被跨“逻辑任务”共享（如协作式调度或中断处理），也不存在真正的并行执行，因此不会违反 `RefCell` 的借用规则。
- **为何标记为 unsafe**：编译器无法验证“仅用于单处理器”的前提条件是否成立，因此该 `Sync` 实现必须由程序员手动保证其安全性，故需 `unsafe`。
- **作用**：使得 `UPSafeCell<T>` 可以被放置在全局静态变量中（如 `static` 变量），因为全局静态变量要求其类型必须是 `Sync`。

---

```rust
impl<T> UPSafeCell<T> {
    /// User is responsible to guarantee that inner struct is only used in
    /// uniprocessor.
    pub unsafe fn new(value: T) -> Self {
        Self {
            inner: RefCell::new(value),
        }
    }
```

`new` 函数用于构造一个新的 `UPSafeCell<T>` 实例。  
- **为何标记为 unsafe**：虽然函数体本身不包含 `unsafe` 代码，但其正确性依赖于调用者确保该实例仅在单处理器环境中使用。若在多核系统中使用，可能导致数据竞争，因此将责任转移给调用者，标记为 `unsafe` 以强调这一契约。
- **实现方式**：直接将传入的 `value` 包装进 `RefCell`，这是标准的内部可变性模式。

---

```rust
    /// Exclusive access inner data in UPSafeCell. Panic if the data has been borrowed.
    pub fn exclusive_access(&self) -> RefMut<'_, T> {
        self.inner.borrow_mut()
    }
}
```

`exclusive_access` 方法提供对内部数据的独占可变访问。  
- **行为说明**：调用 `RefCell::borrow_mut()`，若当前已有活跃的不可变或可变借用，则 panic。这符合 `RefCell` 的运行时借用规则。
- **为何命名为 “exclusive_access”**：强调该方法提供的是排他性访问，与多核环境中的“互斥锁”语义类似，但在单核下通过运行时检查而非原子操作实现。
- **作用**：允许在不可变引用（`&self`）的基础上获取可变引用，从而支持对全局静态可变状态的安全修改，前提是遵守单处理器约束。

```rust
//! File and filesystem-related syscalls

const FD_STDOUT: usize = 1;
```

该模块定义了与文件及文件系统相关的系统调用。  
- **`FD_STDOUT`** 被硬编码为 `1`，这是 POSIX 标准中标准输出（stdout）的标准文件描述符值。此处直接使用常量而非从用户空间继承，是因为在简单的内核实现中，通常只支持有限的、预定义的文件描述符。

---

```rust
/// write buf of length `len`  to a file with `fd`
pub fn sys_write(fd: usize, buf: *const u8, len: usize) -> isize {
    match fd {
        FD_STDOUT => {
            let slice = unsafe { core::slice::from_raw_parts(buf, len) };
            let str = core::str::from_utf8(slice).unwrap();
            print!("{}", str);
            len as isize
        }
        _ => {
            panic!("Unsupported fd in sys_write!");
```

`sys_write` 是 `write` 系统调用的内核实现，用于将用户空间缓冲区的数据写入指定文件描述符。  
- **参数说明**：
  - `fd`：目标文件描述符。
  - `buf`：指向用户空间内存的原始指针，内核需将其解释为字节序列。
  - `len`：要写入的字节数。
- **为何使用 `unsafe`**：`core::slice::from_raw_parts` 需要假设 `buf` 指向有效且长度至少为 `len` 的内存区域，这在系统调用上下文中由用户程序保证，但 Rust 编译器无法验证，故需 `unsafe`。
- **仅支持 `FD_STDOUT`**：当前实现仅处理标准输出，其余文件描述符直接 panic。这是因为简易操作系统（如教学 OS）通常尚未实现完整的 VFS 或文件抽象，仅需将输出重定向到控制台。
- **UTF-8 解码**：通过 `core::str::from_utf8` 将字节切片转换为字符串，便于使用 `print!` 宏输出。若输入非 UTF-8，会 panic——这在调试或受限环境中可接受，但在生产系统中应更健壮。
- **返回值**：成功时返回实际写入的字节数（此处恒为 `len`），符合 POSIX `write` 语义。

---

```rust
//! Implementation of syscalls
//!
//! The single entry point to all system calls, [`syscall()`], is called
//! whenever userspace wishes to perform a system call using the `ecall`
//! instruction. In this case, the processor raises an 'Environment call from
//! U-mode' exception, which is handled as one of the cases in
//! [`crate::trap::trap_handler`].
//!
//! For clarity, each single syscall is implemented as its own function, named
//! `sys_` then the name of the syscall. You can find functions like this in
//! submodules, and you should also implement syscalls this way.

const SYSCALL_WRITE: usize = 64;
const SYSCALL_EXIT: usize = 93;

mod fs;
mod process;

use fs::*;
use process::*;
```

此部分为系统调用的总入口和组织结构说明。  
- **`SYSCALL_WRITE` 和 `SYSCALL_EXIT`**：分别对应 RISC-V Linux ABI 中的系统调用号 64（`SYS_write`）和 93（`SYS_exit`）。这些编号是约定俗成的，确保用户程序使用标准 libc 或汇编调用时能正确映射。
- **模块化设计**：将不同类别的系统调用（如文件系统 `fs`、进程管理 `process`）拆分到子模块中，提升代码可维护性。
- **命名规范**：每个系统调用以 `sys_` 前缀命名，便于识别和统一管理。

---

```rust
/// handle syscall exception with `syscall_id` and other arguments
pub fn syscall(syscall_id: usize, args: [usize; 3]) -> isize {
    match syscall_id {
        SYSCALL_WRITE => sys_write(args[0], args[1] as *const u8, args[2]),
        SYSCALL_EXIT => sys_exit(args[0] as i32),
        _ => panic!("Unsupported syscall_id: {}", syscall_id),
    }
}
```

`syscall` 是所有系统调用的统一入口函数。  
- **调用机制**：当用户程序执行 `ecall` 指令时，CPU 触发异常，进入内核态，`trap_handler` 提取系统调用号和参数后调用此函数。
- **参数传递**：采用 `[usize; 3]` 数组接收最多三个参数，符合 RISC-V 用户态 ABI 中前几个参数通过寄存器（如 `a0`–`a2`）传递的惯例。
- **分发逻辑**：通过 `match` 将 `syscall_id` 路由到对应的处理函数。当前仅支持 `write` 和 `exit`。
- **类型转换**：`args[1] as *const u8` 将寄存器中的整数值重新解释为用户空间指针，这是系统调用处理中的常见模式，但隐含了对用户传参合法性的信任。

---

```rust
//! App management syscalls
use crate::batch::run_next_app;

/// task exits and submit an exit code
pub fn sys_exit(exit_code: i32) -> ! {
    println!("[kernel] Application exited with code {}", exit_code);
    run_next_app()
}
```

`sys_exit` 实现进程退出系统调用。  
- **永不返回（`-> !`）**：该函数终止当前应用，并切换到下一个应用，因此不会返回调用者。
- **功能**：打印退出码用于调试，然后调用 `run_next_app()` 切换上下文。这表明系统采用批处理（batch）或多任务调度模型，而非 Unix 风格的进程树。
- **简化设计**：未释放资源或清理进程状态，适用于教学 OS 或简单运行时环境，其中应用生命周期由内核严格控制。

```rust
use riscv::register::sstatus::{self, SPP, Sstatus};
```

该行导入 RISC-V 架构中与 `sstatus` 控制状态寄存器（CSR）相关的类型和函数。  
- **`Sstatus`**：表示 `sstatus` CSR 的结构化视图，允许安全地读写其字段。
- **`SPP`**：表示 Supervisor Previous Privilege 位的枚举类型，用于记录进入陷阱前的特权级（User 或 Supervisor）。
- **作用**：在构建用户态应用的初始陷阱上下文时，需设置 `sstatus.SPP = User`，以确保从内核态返回用户态时能正确恢复到用户模式。

---

```rust
/// Trap Context
#[repr(C)]
pub struct TrapContext {
    /// general regs[0..31]
    pub x: [usize; 32],
    /// CSR sstatus      
    pub sstatus: Sstatus,
    /// CSR sepc
    pub sepc: usize,
}
```

`TrapContext` 结构体用于保存和恢复陷阱（trap）发生时的处理器上下文。  
- **`#[repr(C)]`**：强制使用 C 语言的内存布局，确保该结构体在汇编代码（如 `trap.S`）和 Rust 代码之间具有确定且一致的字段偏移，便于直接通过地址访问字段。
- **`x: [usize; 32]`**：保存 32 个通用寄存器（x0–x31）。其中 x0 恒为 0，但为简化上下文切换逻辑仍一并保存。
- **`sstatus: Sstatus`**：保存 `sstatus` CSR 的值，包含中断使能位、特权级状态等关键信息。
- **`sepc: usize`**：保存 `sepc`（Supervisor Exception Program Counter）CSR 的值，即陷阱发生时的下一条指令地址，用于异常处理完成后返回。

---

```rust
impl TrapContext {
    /// set stack pointer to x_2 reg (sp)
    pub fn set_sp(&mut self, sp: usize) {
        self.x[2] = sp;
    }
```

`set_sp` 方法将栈指针（SP）设置到 `x[2]`，因为 RISC-V ABI 规定 `x2` 为栈指针寄存器（`sp`）。  
- **为何需要此方法**：在初始化用户程序上下文或切换任务时，需显式设置用户栈顶地址。
- **实现简单性**：直接赋值，依赖调用者传入合法的栈地址。

---

```rust
    /// init app context
    pub fn app_init_context(entry: usize, sp: usize) -> Self {
        let mut sstatus = sstatus::read(); // CSR sstatus
        sstatus.set_spp(SPP::User); //previous privilege mode: user mode
        let mut cx = Self {
            x: [0; 32],
            sstatus,
            sepc: entry, // entry point of app
        };
        cx.set_sp(sp); // app's user stack pointer
        cx // return initial Trap Context of app
    }
}
```

`app_init_context` 用于构造用户应用程序的初始陷阱上下文。  
- **`sstatus.set_spp(SPP::User)`**：设置 `SPP` 位为 User，确保当内核通过 `sret` 指令返回时，CPU 切换到用户模式执行。
- **`sepc = entry`**：将程序入口地址写入 `sepc`，这样首次从内核跳转到用户程序时，会从 `entry` 开始执行。
- **寄存器清零**：所有通用寄存器初始化为 0，符合新进程启动时的干净状态假设。
- **设置栈指针**：通过 `set_sp(sp)` 将用户栈顶地址写入 `x2`，为用户程序提供运行时栈。

---

```rust
global_asm!(include_str!("trap.S"));
```

该宏将 `trap.S` 汇编文件的内容内联到当前模块中。  
- **作用**：定义 `__alltraps` 入口点，这是所有陷阱（包括系统调用、异常、中断）的统一汇编处理入口。
- **必要性**：Rust 无法直接处理 trap 帧的保存/恢复，必须由汇编代码完成寄存器压栈、切换到内核栈、调用 Rust 处理函数等底层操作。

---

```rust
/// initialize CSR `stvec` as the entry of `__alltraps`
pub fn init() {
    unsafe extern "C" {
        safe fn __alltraps();
    }
    unsafe {
        stvec::write(__alltraps as usize, TrapMode::Direct);
    }
}
```

`init` 函数在内核初始化阶段设置 `stvec` CSR，指定陷阱向量基地址。  
- **`__alltraps` 声明**：通过 `extern "C"` 声明汇编符号，`safe fn` 表示该函数可被安全调用（尽管实际由硬件触发）。
- **`stvec::write(..., TrapMode::Direct)`**：将 `stvec` 设置为直接模式，即所有同步/异步陷阱均跳转到 `__alltraps` 地址，而非使用向量表。
- **`unsafe` 原因**：修改 CSR 可能影响系统稳定性，且 `__alltraps` 地址的正确性依赖于链接器和汇编实现。

---

```rust
#[no_mangle]
/// handle an interrupt, exception, or system call from user space
pub fn trap_handler(cx: &mut TrapContext) -> &mut TrapContext {
```

`trap_handler` 是 Rust 层的陷阱处理主函数，由 `__alltraps` 汇编代码调用。  
- **`#[no_mangle]`**：防止 Rust 编译器对函数名进行修饰，确保汇编代码能通过原始符号名 `trap_handler` 调用它。
- **参数与返回值**：接收一个可变引用 `&mut TrapContext`，处理完毕后返回同一引用，供汇编代码用于恢复上下文。

---

```rust
    let scause = scause::read(); // get trap cause
    let stval = stval::read(); // get extra value
```

读取 `scause` 和 `stval` CSR 以获取陷阱原因和附加信息。  
- **`scause`**：指示陷阱类型（如系统调用、页错误、非法指令等）。
- **`stval`**：在某些异常（如缺页、非法地址访问）中包含出错的虚拟地址或指令信息，用于诊断。

---

```rust
    match scause.cause() {
        Trap::Exception(Exception::UserEnvCall) => {
            cx.sepc += 4;
            cx.x[10] = syscall(cx.x[17], [cx.x[10], cx.x[11], cx.x[12]]) as usize;
        }
```

处理来自用户态的环境调用（即系统调用）。  
- **`UserEnvCall`**：RISC-V 中用户态执行 `ecall` 指令触发的异常。
- **`cx.sepc += 4`**：将 `sepc` 指向下一条指令（RISC-V 指令长度为 4 字节），避免返回后重复执行 `ecall`。
- **参数传递约定**：
  - 系统调用号在 `a7`（即 `x[17]`）。
  - 参数依次在 `a0–a2`（即 `x[10]–x[12]`）。
  - 返回值写回 `a0`（即 `x[10]`）。
- **调用 `syscall`**：分发到具体的系统调用实现，并将返回值存入 `x[10]`。

---

```rust
        Trap::Exception(Exception::StoreFault) | Trap::Exception(Exception::StorePageFault) => {
            println!("[kernel] PageFault in application, kernel killed it.");
            run_next_app();
        }
        Trap::Exception(Exception::IllegalInstruction) => {
            println!("[kernel] IllegalInstruction in application, kernel killed it.");
            run_next_app();
        }
```

处理致命异常，终止当前应用并切换到下一个。  
- **存储相关异常**：`StoreFault`（地址对齐错误等）和 `StorePageFault`（页表项无效或权限不足）表明用户程序存在严重错误。
- **非法指令**：执行了未定义或特权指令，通常由程序崩溃或恶意代码引起。
- **`run_next_app()`**：在批处理系统中，内核直接切换到下一个应用，不尝试恢复当前应用。

---

```rust
        _ => {
            panic!(
                "Unsupported trap {:?}, stval = {:#x}!",
                scause.cause(),
                stval
            );
        }
```

对未处理的陷阱类型触发 panic。  
- **设计哲学**：在教学或简化 OS 中，仅支持有限的陷阱类型，其余视为内核 bug 或不可恢复错误。
- **调试信息**：打印 `scause` 和 `stval` 有助于定位问题。

---

```rust
    cx
}

pub use context::TrapContext;
```

- **返回 `cx`**：确保汇编代码能使用修改后的上下文执行 `sret` 返回用户态。
- **`pub use`**：将 `TrapContext` 重新导出，使其他模块（如任务切换、系统调用）可访问该类型。


```asm
.altmacro
.macro SAVE_GP n
    sd x\n, \n*8(sp)
.endm
.macro LOAD_GP n
    ld x\n, \n*8(sp)
.endm
```

定义两个汇编宏以简化通用寄存器的保存与恢复。  
- **`.altmacro`**：启用 GNU as 的高级宏语法，允许在宏参数中使用 `\n` 等表达式。
- **`SAVE_GP n`**：将寄存器 `x<n>` 存储到栈偏移 `n*8` 处（RISC-V 64 位系统中每个寄存器占 8 字节）。
- **`LOAD_GP n`**：从栈偏移 `n*8` 处加载值回 `x<n>`。
- **作用**：避免重复书写 `sd/ld` 指令，提高代码可读性和维护性。

---

```asm
    .section .text
    .globl __alltraps
    .globl __restore
    .align 2
```

声明代码段和全局符号。  
- **`.section .text`**：指示后续代码放入可执行的 `.text` 段。
- **`.globl __alltraps, __restore`**：将这两个标签导出为全局符号，供 Rust 代码（如 `stvec::write` 和 `trap_handler` 调用）引用。
- **`.align 2`**：确保指令地址按 4 字节（2^2）对齐，符合 RISC-V 指令对齐要求。

---

```asm
__alltraps:
    csrrw sp, sscratch, sp
```

交换 `sp`（栈指针）与 `sscratch` CSR 的值。  
- **初始状态**：进入陷阱时，`sp` 指向用户栈顶，`sscratch` 在任务切换时被预设为当前任务的内核栈顶。
- **执行后**：
  - `sp` 指向内核栈（可用于安全压栈），
  - `sscratch` 保存了用户栈指针（稍后存入 `TrapContext`）。
- **目的**：快速切换到内核栈，避免在用户栈上操作导致安全问题或崩溃。

---

```asm
    # allocate a TrapContext on kernel stack
    addi sp, sp, -34*8
```

在内核栈上为 `TrapContext` 分配空间。  
- **大小计算**：`TrapContext` 包含 32 个通用寄存器（32×8）、`sstatus`（8）、`sepc`（8），共 34×8 字节。
- **栈增长方向**：RISC-V 栈向下增长，故减去空间大小。
- **对齐**：34×8 = 272 字节，满足 16 字节栈对齐要求（RISC-V ABI 推荐）。

---

```asm
    # save general-purpose registers
    sd x1, 1*8(sp)
    # skip sp(x2), we will save it later
    sd x3, 3*8(sp)
    # skip tp(x4), application does not use it
```

手动保存部分通用寄存器。  
- **`x1`（ra）**：返回地址寄存器，必须保存以支持函数调用和异常返回。
- **跳过 `x2`（sp）**：其值已通过 `sscratch` 获取，将在后续显式保存。
- **跳过 `x4`（tp）**：线程指针，在单地址空间、无 TLS 的简易 OS 中未使用，故省略以节省开销。

---

```asm
    # save x5~x31
    .set n, 5
    .rept 27
        SAVE_GP %n
        .set n, n+1
    .endr
```

使用宏循环保存 `x5` 到 `x31` 共 27 个寄存器。  
- **`.set n, 5`**：初始化计数器。
- **`.rept 27`**：重复展开 27 次。
- **效率**：展开而非运行时循环，避免额外分支开销，符合 trap handler 的性能敏感性。

---

```asm
    # we can use t0/t1/t2 freely, because they were saved on kernel stack
    csrr t0, sstatus
    csrr t1, sepc
    sd t0, 32*8(sp)
    sd t1, 33*8(sp)
```

保存关键 CSR 到 `TrapContext` 的最后两个槽位。  
- **`t0–t2` 可安全使用**：它们属于调用者保存寄存器，且已在前面保存到栈中。
- **`sstatus` → offset 32*8**：对应 `TrapContext.sstatus`。
- **`sepc` → offset 33*8**：对应 `TrapContext.sepc`。
- **顺序无关**：因 `t0/t1` 已保存，读取 CSR 不会破坏上下文。

---

```asm
    # read user stack from sscratch and save it on the kernel stack
    csrr t2, sscratch
    sd t2, 2*8(sp)
```

将用户栈指针（原 `sp`）存入 `TrapContext.x[2]`。  
- **来源**：`sscratch` 在 `csrrw` 后保存了用户态的 `sp`。
- **位置**：`2*8(sp)` 对应 `TrapContext.x[2]`，即 `sp` 寄存器在结构体中的位置。
- **意义**：完整恢复用户上下文时需还原 `sp`。

---

```asm
    # set input argument of trap_handler(cx: &mut TrapContext)
    mv a0, sp
    call trap_handler
```

调用 Rust 层的 `trap_handler` 函数。  
- **参数传递**：RISC-V ABI 规定第一个参数通过 `a0` 传递，此处传入 `TrapContext` 的地址（即当前 `sp`）。
- **控制流**：`call` 指令跳转到 Rust 函数，处理具体 trap 类型（如系统调用、页错误等）。

---

```asm
__restore:
    # case1: start running app by __restore
    # case2: back to U after handling trap
    mv sp, a0
```

`__restore` 是上下文恢复入口，用于首次启动应用或从 trap 返回用户态。  
- **`a0` 输入**：指向要恢复的 `TrapContext`（通常由调度器或 `trap_handler` 准备）。
- **`mv sp, a0`**：将栈指针设为该上下文地址，以便从中加载寄存器。

---

```asm
    # restore sstatus/sepc
    ld t0, 32*8(sp)
    ld t1, 33*8(sp)
    ld t2, 2*8(sp)
    csrw sstatus, t0
    csrw sepc, t1
    csrw sscratch, t2
```

恢复关键 CSR。  
- **`sstatus`**：恢复中断使能、特权级状态（特别是 `SPP` 位决定返回用户/内核态）。
- **`sepc`**：设置返回地址（如系统调用后的下一条指令）。
- **`sscratch`**：写回用户栈指针，为下次 trap 的 `csrrw sp, sscratch, sp` 做准备。

---

```asm
    # restore general-purpuse registers except sp/tp
    ld x1, 1*8(sp)
    ld x3, 3*8(sp)
    .set n, 5
    .rept 27
        LOAD_GP %n
        .set n, n+1
    .endr
```

恢复通用寄存器（除 `x2/sp` 和 `x4/tp`）。  
- **与保存对称**：使用相同偏移和宏展开方式。
- **`sp` 不在此恢复**：因其值已通过 `sscratch` 机制在最后一步恢复。

---

```asm
    # release TrapContext on kernel stack
    addi sp, sp, 34*8
```

释放 `TrapContext` 占用的内核栈空间。  
- **栈指针回退**：加回之前分配的 34×8 字节，恢复到 trap 前的内核栈状态。

---

```asm
    # now sp->kernel stack, sscratch->user stack
    csrrw sp, sscratch, sp
    sret
```

最终切换回用户栈并执行返回。  
- **`csrrw sp, sscratch, sp`**：
  - 将 `sp` 设为 `sscratch`（即用户栈指针），
  - 同时将原 `sp`（内核栈）写回 `sscratch`，完成状态交换。
- **`sret`**：
  - 根据 `sstatus.SPP` 决定返回用户态（U-mode）或内核态（S-mode），
  - 跳转到 `sepc` 所指地址继续执行。


  ```rust
//! batch subsystem

use crate::sbi::shutdown;
use crate::sync::UPSafeCell;
use crate::trap::TrapContext;
use core::arch::asm;
use lazy_static::*;
```

该模块实现了一个批处理（batch）子系统，用于顺序加载和运行多个用户应用程序。  
- **`sbi::shutdown`**：通过 SBI（Supervisor Binary Interface）通知宿主机关闭系统。
- **`UPSafeCell`**：利用单处理器安全的内部可变性容器管理全局应用状态。
- **`TrapContext`**：用于初始化和切换到用户程序的执行上下文。
- **`lazy_static!`**：延迟初始化全局静态变量 `APP_MANAGER`，避免在编译期构造复杂结构。

---

```rust
const USER_STACK_SIZE: usize = 4096 * 2;
const KERNEL_STACK_SIZE: usize = 4096 * 2;
const MAX_APP_NUM: usize = 16;
const APP_BASE_ADDRESS: usize = 0x80400000;
const APP_SIZE_LIMIT: usize = 0x20000;
```

定义系统关键常量：  
- **栈大小**：用户栈和内核栈均为 8KB（2×4096），满足一般应用需求且节省内存。
- **`MAX_APP_NUM`**：最多支持 16 个应用，限制来自链接脚本或内存布局。
- **`APP_BASE_ADDRESS`**：用户程序统一加载到物理/虚拟地址 `0x80400000`，这是 RISC-V 教学 OS 常见的用户空间起始地址。
- **`APP_SIZE_LIMIT`**：每个应用最大 128KB（0x20000 字节），防止恶意或错误程序占用过多内存。

---

```rust
#[repr(align(4096))]
struct KernelStack {
    data: [u8; KERNEL_STACK_SIZE],
}

#[repr(align(4096))]
struct UserStack {
    data: [u8; USER_STACK_SIZE],
}
```

定义对齐到 4KB 边界的栈结构体。  
- **`#[repr(align(4096))]`**：强制结构体按页对齐，便于后续内存管理（如设置页表权限）或满足硬件要求。
- **`data` 字段**：以字节数组形式预留栈空间，避免动态分配。

---

```rust
static KERNEL_STACK: KernelStack = KernelStack {
    data: [0; KERNEL_STACK_SIZE],
};
static USER_STACK: UserStack = UserStack {
    data: [0; USER_STACK_SIZE],
};
```

声明全局静态栈实例。  
- **生命周期**：整个内核运行期间有效，地址固定。
- **初始化为零**：确保栈初始内容干净，避免信息泄露。

---

```rust
impl KernelStack {
    fn get_sp(&self) -> usize {
        self.data.as_ptr() as usize + KERNEL_STACK_SIZE
    }
```

`get_sp` 返回内核栈顶地址。  
- **栈向下增长**：RISC-V 栈从高地址向低地址增长，故栈顶为数组起始地址加总大小。
- **用途**：作为内核态执行时的栈指针，或用于放置 `TrapContext`。

---

```rust
    pub fn push_context(&self, cx: TrapContext) -> &'static mut TrapContext {
        let cx_ptr = (self.get_sp() - core::mem::size_of::<TrapContext>()) as *mut TrapContext;
        unsafe {
            *cx_ptr = cx;
        }
        unsafe { cx_ptr.as_mut().unwrap() }
    }
}
```

`push_context` 将 `TrapContext` 压入内核栈顶部，并返回其可变引用。  
- **位置计算**：从栈顶向下预留 `TrapContext` 大小的空间。
- **`unsafe` 原因**：
  - 指针运算和写入需假设地址有效且未越界；
  - 返回 `'static` 生命周期引用，依赖调用者保证该上下文在使用期间不被覆盖。
- **用途**：为 `__restore` 提供初始上下文地址，启动用户程序。

---

```rust
impl UserStack {
    fn get_sp(&self) -> usize {
        self.data.as_ptr() as usize + USER_STACK_SIZE
    }
}
```

`UserStack::get_sp` 返回用户栈顶地址，逻辑同内核栈，用于初始化用户程序的 `sp` 寄存器。

---

```rust
struct AppManager {
    num_app: usize,
    current_app: usize,
    app_start: [usize; MAX_APP_NUM + 1],
}
```

`AppManager` 管理所有用户应用的元数据。  
- **`num_app`**：实际应用数量。
- **`current_app`**：当前待运行的应用索引。
- **`app_start`**：长度为 `MAX_APP_NUM + 1` 的数组，存储每个应用在内核镜像中的起始地址，`app_start[i+1] - app_start[i]` 即为第 `i` 个应用的大小。末尾多一项用于简化长度计算。

---

```rust
impl AppManager {
    pub fn print_app_info(&self) {
        println!("[kernel] num_app = {}", self.num_app);
        for i in 0..self.num_app {
            println!(
                "[kernel] app_{} [{:#x}, {:#x})",
                i,
                self.app_start[i],
                self.app_start[i + 1]
            );
        }
    }
```

`print_app_info` 打印所有应用的加载地址范围，用于调试和验证链接脚本是否正确嵌入应用数据。

---

```rust
    fn load_app(&self, app_id: usize) {
        if app_id >= self.num_app {
            println!("All applications completed!");
            shutdown(false);
        }
        println!("[kernel] Loading app_{}", app_id);
        unsafe {
            // clear app area
            core::slice::from_raw_parts_mut(APP_BASE_ADDRESS as *mut u8, APP_SIZE_LIMIT).fill(0);
```

`load_app` 将指定应用从内核镜像复制到用户空间。  
- **边界检查**：若 `app_id` 超出范围，关闭系统。
- **清零目标区域**：先将 `APP_BASE_ADDRESS` 开始的 `APP_SIZE_LIMIT` 字节清零，避免残留数据干扰新应用。
- **`unsafe` 原因**：直接操作任意物理/虚拟地址，假设 `APP_BASE_ADDRESS` 可写且足够大。

---

```rust
            let app_src = core::slice::from_raw_parts(
                self.app_start[app_id] as *const u8,
                self.app_start[app_id + 1] - self.app_start[app_id],
            );
            let app_dst =
                core::slice::from_raw_parts_mut(APP_BASE_ADDRESS as *mut u8, app_src.len());
            app_dst.copy_from_slice(app_src);
```

- **`app_src`**：从内核镜像中提取第 `app_id` 个应用的原始字节（只读）。
- **`app_dst`**：指向用户空间目标区域（可写）。
- **`copy_from_slice`**：高效复制应用代码和数据到用户空间。

---

```rust
            // Memory fence about fetching the instruction memory
            // It is guaranteed that a subsequent instruction fetch must
            // observes all previous writes to the instruction memory.
            // Therefore, fence.i must be executed after we have loaded
            // the code of the next app into the instruction memory.
            // See also: riscv non-priv spec chapter 3, 'Zifencei' extension.
            asm!("fence.i");
```

插入 `fence.i` 指令确保指令缓存一致性。  
- **必要性**：RISC-V 允许指令和数据缓存不一致。若刚写入的代码未同步到 I-Cache，CPU 可能执行旧指令或无效指令。
- **`fence.i` 作用**：使后续取指操作能观察到之前对指令内存的所有写入，符合 `Zifencei` 扩展规范。

---

```rust
    pub fn get_current_app(&self) -> usize {
        self.current_app
    }

    pub fn move_to_next_app(&mut self) {
        self.current_app += 1;
    }
}
```

提供对当前应用索引的访问和递增操作，用于控制批处理流程。

---

```rust
lazy_static! {
    static ref APP_MANAGER: UPSafeCell<AppManager> = unsafe {
        UPSafeCell::new({
            unsafe extern "C" {
                safe fn _num_app();
            }
            let num_app_ptr = _num_app as usize as *const usize;
            let num_app = num_app_ptr.read_volatile();
```

通过 `lazy_static!` 初始化 `APP_MANAGER`。  
- **`_num_app` 符号**：由链接脚本生成，指向一个包含应用数量和起始地址的只读数据结构（通常位于 `.data` 或自定义段）。
- **`read_volatile()`**：防止编译器优化掉对该内存位置的读取，确保从实际地址加载值。
- **`unsafe` 原因**：直接解释函数地址为数据指针，依赖链接器布局正确性。

---

```rust
            let mut app_start: [usize; MAX_APP_NUM + 1] = [0; MAX_APP_NUM + 1];
            let app_start_raw: &[usize] =
                core::slice::from_raw_parts(num_app_ptr.add(1), num_app + 1);
            app_start[..=num_app].copy_from_slice(app_start_raw);
            AppManager {
                num_app,
                current_app: 0,
                app_start,
            }
        })
    };
}
```

- **`app_start_raw`**：从 `_num_app + 1` 开始读取 `num_app + 1` 个 `usize`，即所有应用的起始地址（含结束哨兵）。
- **复制到本地数组**：避免后续依赖内核镜像中的原始布局，提高鲁棒性。
- **封装进 `UPSafeCell`**：允许在单处理器环境下通过 `exclusive_access` 安全地获取可变引用。

---

```rust
/// init batch subsystem
pub fn init() {
    print_app_info();
}
```

`init` 函数在内核启动时调用，打印应用信息用于调试。

---

```rust
/// print apps info
pub fn print_app_info() {
    APP_MANAGER.exclusive_access().print_app_info();
}
```

对外暴露的打印接口，通过 `UPSafeCell::exclusive_access` 获取 `AppManager` 的独占访问权。

---

```rust
/// run next app
pub fn run_next_app() -> ! {
    let mut app_manager = APP_MANAGER.exclusive_access();
    let current_app = app_manager.get_current_app();
    app_manager.load_app(current_app);
    app_manager.move_to_next_app();
    drop(app_manager);
```

`run_next_app` 加载并启动下一个应用，永不返回（`-> !`）。  
- **获取独占访问**：确保在单处理器下对 `AppManager` 的修改是原子的。
- **加载与递增**：先加载当前应用，再移动到下一个，避免重复执行。
- **显式 `drop`**：释放 `UPSafeCell` 的借用，防止在后续汇编调用中因 RefCell 借用冲突而 panic。

---

```rust
    // before this we have to drop local variables related to resources manually
    // and release the resources
    unsafe extern "C" {
        unsafe fn __restore(cx_addr: usize);
    }
    unsafe {
        __restore(KERNEL_STACK.push_context(TrapContext::app_init_context(
            APP_BASE_ADDRESS,
            USER_STACK.get_sp(),
        )) as *const _ as usize);
    }
    panic!("Unreachable in batch::run_current_app!");
}
```

- **调用 `__restore`**：传入新构建的 `TrapContext` 地址，该上下文设置：
  - `sepc = APP_BASE_ADDRESS`：用户程序入口点；
  - `sp = USER_STACK.get_sp()`：用户栈顶；
  - `sstatus.SPP = User`：确保返回用户态。
- **`__restore` 行为**：由汇编实现，恢复寄存器和 CSR 后执行 `sret`，跳转到用户程序。
- **`panic!` 不可达**：因 `__restore` 通过 `sret` 切换到用户态，不会返回 Rust 代码。


```rust
use std::fs::{File, read_dir};
use std::io::{Result, Write};

fn main() {
    println!("cargo:rerun-if-changed=../user/src/");
    println!("cargo:rerun-if-changed={}", TARGET_PATH);
    insert_app_data().unwrap();
}
```

该构建脚本（通常作为 `build.rs`）在编译内核前自动生成汇编文件 `src/link_app.S`，用于将用户程序二进制嵌入内核镜像。  
- **`cargo:rerun-if-changed`**：通知 Cargo 当 `../user/src/` 目录或目标二进制目录内容变化时重新运行此构建脚本，确保用户程序更新后内核能重新链接。
- **`insert_app_data().unwrap()`**：执行核心逻辑，若失败则 panic，中断构建。

---

```rust
static TARGET_PATH: &str = "../user/target/riscv64gc-unknown-none-elf/release/";
```

定义用户程序编译输出路径。  
- **目标三元组 `riscv64gc-unknown-none-elf`**：表示为 RISC-V 64 位通用 CPU（含原子、浮点等扩展）、无操作系统（bare-metal）、ELF 格式的可执行文件。
- **`release/`**：使用优化后的发布版本二进制，减小体积并提升性能。

---

```rust
fn insert_app_data() -> Result<()> {
    let mut f = File::create("src/link_app.S").unwrap();
```

创建或覆盖 `src/link_app.S` 文件，该文件将被内核链接脚本包含，用于静态嵌入用户程序。

---

```rust
    let mut apps: Vec<_> = read_dir("../user/src/bin")
        .unwrap()
        .into_iter()
        .map(|dir_entry| {
            let mut name_with_ext = dir_entry.unwrap().file_name().into_string().unwrap();
            name_with_ext.drain(name_with_ext.find('.').unwrap()..name_with_ext.len());
            name_with_ext
        })
        .collect();
    apps.sort();
```

扫描 `../user/src/bin/` 目录下的所有用户程序源文件（如 `app1.rs`, `hello.rs`），提取不带扩展名的文件名，并排序。  
- **`read_dir`**：列出目录项。
- **`drain(...)`**：移除从第一个 `.` 开始的后缀（如 `.rs`），得到纯应用名。
- **`sort()`**：确保应用按字典序加载，使行为可预测。

---

```rust
    writeln!(
        f,
        r#"
    .align 3
    .section .data
    .global _num_app
_num_app:
    .quad {}"#,
        apps.len()
    )?;
```

在 `.data` 段中定义全局符号 `_num_app`，其值为用户程序数量。  
- **`.align 3`**：按 8 字节（2^3）对齐，满足 RISC-V 64 位 `quad`（8 字节）对齐要求。
- **`.quad`**：定义一个 64 位整数，在链接后地址处存储应用数量。
- **用途**：内核通过读取 `_num_app` 地址处的值获取应用总数（见 `AppManager` 初始化）。

---

```rust
    for i in 0..apps.len() {
        writeln!(f, r#"    .quad app_{}_start"#, i)?;
    }
    writeln!(f, r#"    .quad app_{}_end"#, apps.len() - 1)?;
```

生成 `_num_app` 后紧跟的地址数组，构成 `app_start` 表：  
- 前 `N` 项为 `app_0_start`, `app_1_start`, ..., `app_{N-1}_start`；
- 最后一项为 `app_{N-1}_end`，作为哨兵标记最后一个应用的结束地址。  
- **布局示例**（2 个应用）：
  ```asm
  _num_app:
      .quad 2
      .quad app_0_start
      .quad app_1_start
      .quad app_1_end
  ```
- **内核使用方式**：`app_start[i+1] - app_start[i]` 即为第 `i` 个应用的大小。

---

```rust
    for (idx, app) in apps.iter().enumerate() {
        println!("app_{}: {}", idx, app);
        writeln!(
            f,
            r#"
    .section .data
    .global app_{0}_start
    .global app_{0}_end
app_{0}_start:
    .incbin "{2}{1}.bin"
app_{0}_end:"#,
            idx, app, TARGET_PATH
        )?;
    }
```

为每个应用生成独立的 `.data` 段区域：  
- **`.global app_X_start/end`**：导出起始和结束符号，供链接器解析。
- **`.incbin "{TARGET_PATH}{app}.bin"`**：将预编译的用户程序二进制（如 `hello.bin`）原样嵌入内核镜像的 `.data` 段。
- **`println!`**：在构建日志中显示应用索引与名称，便于调试。
- **关键前提**：用户程序需预先通过 `objcopy` 等工具转换为纯二进制格式（`.bin`），仅保留代码和数据，不含 ELF 头。

---

```rust
    Ok(())
}
```

成功完成 `link_app.S` 生成，返回 `Ok(())`。该文件随后被内核的链接脚本包含，使所有用户程序成为内核镜像的一部分，可在运行时由 `AppManager::load_app` 复制到用户空间执行。


```rust
#![no_std]
#![no_main]

#[macro_use]
extern crate user_lib;

#[no_mangle]
fn main() -> i32 {
    println!("Hello, world!");
    0
}
```

该用户程序是一个标准的“Hello, world!”示例。  
- **`#![no_std]`**：不链接 Rust 标准库，仅使用 `core` 和自定义 `user_lib`，适用于无操作系统环境。
- **`#![no_main]`**：禁用 Rust 默认的 `main` 入口包装器，由链接脚本和运行时直接跳转到此 `main`。
- **`#[no_mangle]`**：防止符号名被修饰，确保链接器能正确识别入口点（通常由 `_start` 调用）。
- **`println!`**：通过系统调用（如 `sys_write`）输出字符串到标准输出。
- **返回值 `0`**：表示程序正常退出，将作为退出码传递给内核。

---

```rust
#![no_std]
#![no_main]

#[macro_use]
extern crate user_lib;

#[no_mangle]
fn main() -> i32 {
    println!("Into Test store_fault, we will insert an invalid store operation...");
    println!("Kernel should kill this application!");
    unsafe {
        core::ptr::null_mut::<u8>().write_volatile(0);
    }
    0
}
```

该程序用于测试存储异常（Store Fault）处理机制。  
- **`core::ptr::null_mut::<u8>()`**：构造一个空指针（地址 0x0）。
- **`write_volatile(0)`**：尝试向无效地址（零页）写入字节。在大多数系统中，零地址不可写，触发 `StoreFault` 或 `StorePageFault` 异常。
- **预期行为**：内核的 `trap_handler` 捕获该异常，打印错误信息，并调用 `run_next_app()` 终止当前应用，切换到下一个。
- **`unsafe` 原因**：解引用空指针是未定义行为，但在受控测试中用于验证异常处理。

---

```rust
#![no_std]
#![no_main]

#[macro_use]
extern crate user_lib;

const SIZE: usize = 10;
const P: u32 = 3;
const STEP: usize = 100000;
const MOD: u32 = 10007;

#[no_mangle]
fn main() -> i32 {
    let mut pow = [0u32; SIZE];
    let mut index: usize = 0;
    pow[index] = 1;
    for i in 1..=STEP {
        let last = pow[index];
        index = (index + 1) % SIZE;
        pow[index] = last * P % MOD;
        if i % 10000 == 0 {
            println!("{}^{}={}(MOD {})", P, i, pow[index], MOD);
        }
    }
    println!("Test power OK!");
    0
}
```

该程序执行长时间的模幂运算，用于测试内核的批处理调度和应用正常退出流程。  
- **环形缓冲区 `pow`**：仅保留最近 `SIZE=10` 个幂值，节省内存。
- **计算逻辑**：迭代计算 \( P^i \mod \text{MOD} \)，其中 \( P=3, \text{MOD}=10007 \)。
- **周期性输出**：每 10,000 步打印一次中间结果，验证程序持续运行。
- **用途**：确认内核能正确加载、运行完整应用，并在 `sys_exit(0)` 后切换到下一任务。

---

```rust
#![no_std]
#![no_main]

#[macro_use]
extern crate user_lib;

use core::arch::asm;

#[no_mangle]
fn main() -> i32 {
    println!("Try to execute privileged instruction in U Mode");
    println!("Kernel should kill this application!");
    unsafe {
        asm!("sret");
    }
    0
}
```

该程序尝试在用户态执行特权指令 `sret`（Supervisor Return），用于测试非法指令异常处理。  
- **`sret` 指令**：仅在 Supervisor 模式下有效，用于从陷阱返回。用户态执行会触发 `IllegalInstruction` 异常。
- **`asm!` 宏**：内联汇编插入 `sret` 指令。
- **预期行为**：内核捕获 `IllegalInstruction`，终止应用并切换任务。

---

```rust
#![no_std]
#![no_main]

#[macro_use]
extern crate user_lib;

use riscv::register::sstatus::{self, SPP};

#[no_mangle]
fn main() -> i32 {
    println!("Try to access privileged CSR in U Mode");
    println!("Kernel should kill this application!");
    unsafe {
        sstatus::set_spp(SPP::User);
    }
    0
}
```

该程序尝试在用户态修改特权 CSR（Control and Status Register）`sstatus`，用于测试 CSR 访问权限异常。  
- **`sstatus::set_spp(...)`**：试图写入 `sstatus` 寄存器的 `SPP` 字段。在 RISC-V 中，`sstatus` 是 Supervisor 级 CSR，用户态无权访问。
- **硬件行为**：执行 `csrw sstatus, ...` 指令会触发 `IllegalInstruction` 异常（因权限不足）。
- **预期结果**：内核捕获异常，终止应用。  
- **注意**：尽管代码调用的是安全函数，但底层汇编指令仍因特权级不足而非法，故需 `unsafe` 块（因可能引发 trap）。

```rust
use super::write;
use core::fmt::{self, Write};

struct Stdout;

const STDOUT: usize = 1;
```

该模块为用户态程序提供标准输出功能。  
- **`STDOUT: usize = 1`**：定义标准输出的文件描述符为 1，与内核 `sys_write` 中的 `FD_STDOUT` 一致，遵循 POSIX 约定。
- **`Stdout` 结构体**：一个零大小类型（ZST），仅用于实现 `Write` trait，不持有任何状态。

---

```rust
impl Write for Stdout {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        write(STDOUT, s.as_bytes());
        Ok(())
    }
}
```

为 `Stdout` 实现 `core::fmt::Write` trait，使其能被 `print!`/`println!` 宏使用。  
- **`write_str` 方法**：接收字符串切片，将其转换为字节序列后调用 `write` 函数。
- **`write` 函数来源**：来自 `super::write`，即用户库中对 `sys_write` 系统调用的封装（通常通过 `ecall` 触发）。
- **权限视角**：
  - 用户程序无权直接访问硬件（如 UART 寄存器）；
  - 所有输出必须通过系统调用进入内核；
  - 内核验证 `fd == 1` 后，才将数据转发到控制台；
  - 此设计强制用户程序遵守“最小权限原则”——仅能写入预授权的输出流，无法任意操作设备。

---

```rust
pub fn print(args: fmt::Arguments) {
    Stdout.write_fmt(args).unwrap();
}
```

`print` 函数是格式化输出的入口。  
- **`fmt::Arguments`**：由 `format_args!` 宏生成的惰性格式化参数，避免中间分配。
- **`write_fmt`**：调用 `Write` trait 的默认方法，最终分派到 `write_str`。
- **`unwrap()`**：在简易系统中，输出失败（如内核 panic）被视为不可恢复错误，故直接 panic。生产系统应返回错误码。

---

```rust
#[macro_export]
macro_rules! print {
    ($fmt: literal $(, $($arg: tt)+)?) => {
        $crate::console::print(format_args!($fmt $(, $($arg)+)?));
    }
}

#[macro_export]
macro_rules! println {
    ($fmt: literal $(, $($arg: tt)+)?) => {
        $crate::console::print(format_args!(concat!($fmt, "\n") $(, $($arg)+)?));
    }
}
```

导出 `print!` 和 `println!` 宏供用户程序使用。  
- **`#[macro_export]`**：使宏在 `user_lib` crate 外可用（如用户应用中通过 `#[macro_use] extern crate user_lib;` 引入）。
- **`format_args!`**：Rust 内置宏，生成 `fmt::Arguments`，支持类型安全的格式化（如 `{}`、`{:x}`）。
- **权限隔离体现**：
  - 用户代码仅调用高层宏，不感知底层系统调用细节；
  - 实际 I/O 由内核代理执行，用户态无法绕过；
  - 即使用户程序被攻破，也无法直接操控硬件或读取其他进程输出，因所有操作受限于内核的 `sys_write` 实现（当前仅允许 `fd=1`）。

综上，该模块通过 trait 抽象和系统调用封装，在提供便利输出接口的同时，严格维持了用户态与内核态的权限边界。


```rust
#[panic_handler]
fn panic_handler(panic_info: &core::panic::PanicInfo) -> ! {
    let err = panic_info.message();
    if let Some(location) = panic_info.location() {
        println!(
            "Panicked at {}:{}, {}",
            location.file(),
            location.line(),
            err
        );
    } else {
        println!("Panicked: {}", err);
    }
    loop {}
}
```

该函数是 `no_std` 环境下的全局 panic 处理器。  
- **`#[panic_handler]`**：标记此函数为 panic 入口，替代标准库的默认实现。
- **参数 `panic_info`**：包含 panic 消息和源码位置（若编译时启用调试信息）。
- **输出诊断信息**：通过 `println!` 打印文件名、行号和错误消息，便于调试。
- **`loop {}`**：陷入无限循环，因为用户程序在 panic 后不应继续执行。在批处理系统中，这会导致内核无法自动切换到下一应用——但实际中，由于 `println!` 最终触发 `sys_write`，而 panic 本身可能由非法操作引起，内核的 trap handler 通常会在更早阶段（如非法指令、页错误）终止应用。此处的 `loop` 是防御性设计，确保即使 panic 未被 trap 捕获，也不会返回。

---

```rust
#![no_std]
#![feature(linkage)]

#[macro_use]
pub mod console;
mod lang_items;
mod syscall;
```

用户库基础配置与模块组织。  
- **`#![no_std]`**：不依赖标准库，仅使用 `core`。
- **`#![feature(linkage)]`**：启用 `linkage` 属性，用于控制符号链接行为（如弱符号）。
- **`console`**：提供 `print!`/`println!` 宏，封装系统调用输出。
- **`lang_items`**：定义语言项（如 `eh_personality`），满足 `no_std` 编译要求。
- **`syscall`**：封装系统调用接口（如 `sys_write`, `sys_exit`）。

---

```rust
#[no_mangle]
#[link_section = ".text.entry"]
pub extern "C" fn _start() -> ! {
    clear_bss();
    exit(main());
    panic!("unreachable after sys_exit!");
}
```

用户程序入口点 `_start`，由内核或加载器直接跳转执行。  
- **`#[no_mangle]`**：保留符号名为 `_start`，供链接器识别。
- **`#[link_section = ".text.entry"]`**：强制将此函数放入 `.text.entry` 段，确保其位于可执行镜像的起始位置（由链接脚本控制）。
- **`extern "C"`**：使用 C 调用约定，避免 Rust 的名称修饰和 ABI 差异。
- **执行流程**：
  1. **`clear_bss()`**：清零 BSS 段（未初始化的全局变量），符合 C 运行时惯例；
  2. **`exit(main())`**：调用用户定义的 `main` 函数，并将其返回值作为退出码传递给 `exit` 系统调用；
  3. **`panic!`**：理论上不可达，因 `sys_exit` 会终止应用并切换任务。

---

```rust
#[linkage = "weak"]
#[no_mangle]
fn main() -> i32 {
    panic!("Cannot find main!");
}
```

提供弱符号（weak symbol）版本的 `main` 函数。  
- **`#[linkage = "weak"]`**：声明此符号为弱链接。若用户应用提供了同名的强符号 `main`，则链接器优先使用强符号；否则使用此默认实现。
- **作用**：允许用户库作为通用运行时，支持不同应用提供各自的 `main`。若忘记定义 `main`，则在运行时 panic 并提示错误。
- **`#[no_mangle]`**：确保符号名为 `main`，与用户代码中的 `main` 匹配。

---

```rust
fn clear_bss() {
    unsafe extern "C" {
        safe fn start_bss();
        safe fn end_bss();
    }
    (start_bss as usize..end_bss as usize).for_each(|addr| unsafe {
        (addr as *mut u8).write_volatile(0);
    });
}
```

清零 BSS 段，初始化未显式赋值的全局静态变量。  
- **`start_bss` / `end_bss`**：由链接脚本定义的符号，标记 BSS 段的起始和结束地址。
- **`unsafe extern "C"`**：声明外部符号，`safe fn` 表示这些符号可安全调用（实际不调用，仅取地址）。
- **`write_volatile(0)`**：逐字节写入 0，使用 `volatile` 防止编译器优化掉“看似无用”的写操作。
- **必要性**：在 bare-metal 环境中，加载器（如内核）通常只加载 `.text` 和 `.data` 段，BSS 段需由程序自行清零。

---

```rust
use syscall::*;

pub fn write(fd: usize, buf: &[u8]) -> isize {
    sys_write(fd, buf)
}
pub fn exit(exit_code: i32) -> isize {
    sys_exit(exit_code)
}
```

封装系统调用接口，供用户程序和 `console` 模块使用。  
- **`write`**：将字节切片 `buf` 写入指定文件描述符 `fd`，内部调用 `sys_write`（最终通过 `ecall` 进入内核）。
- **`exit`**：终止当前应用并提交退出码，调用 `sys_exit`（永不返回）。
- **权限隔离**：
  - 用户程序只能通过这些封装函数发起系统调用；
  - 实际权限检查（如 `fd` 是否有效）由内核 `sys_write` 实现；
  - 用户态无法绕过这些接口直接执行特权操作，确保了安全边界。


  ```rust
use core::arch::asm;

const SYSCALL_WRITE: usize = 64;
const SYSCALL_EXIT: usize = 93;
```

定义两个系统调用号，与 RISC-V Linux ABI 兼容：  
- **`SYSCALL_WRITE = 64`**：对应 `SYS_write`，用于写入文件描述符。
- **`SYSCALL_EXIT = 93`**：对应 `SYS_exit`，用于终止进程。  
这些常量确保用户程序发起的系统调用能被内核正确识别。

---

```rust
fn syscall(id: usize, args: [usize; 3]) -> isize {
    let mut ret: isize;
    unsafe {
        asm!(
            "ecall",
            inlateout("x10") args[0] => ret,
            in("x11") args[1],
            in("x12") args[2],
            in("x17") id
        );
    }
    ret
}
```

`syscall` 函数是系统调用的底层汇编封装，负责从用户态陷入内核。  
- **RISC-V 用户态 ABI 约定**：
  - 系统调用号通过 `x17`（即 `a7`）传递；
  - 前三个参数依次通过 `x10`（`a0`）、`x11`（`a1`）、`x12`（`a2`）传递；
  - 返回值通过 `x10`（`a0`）返回。
- **`inlateout("x10") args[0] => ret`**：
  - 表示 `x10` 寄存器在 `ecall` 前作为输入（传入 `args[0]`），执行后作为输出（接收返回值 `ret`）；
  - 这是 Rust 内联汇编中处理“输入/输出复用同一寄存器”的标准方式。
- **`unsafe` 原因**：
  - `ecall` 指令会切换到内核态，其行为依赖于内核实现的正确性；
  - 若传入非法参数（如无效指针），可能导致内核 panic 或安全漏洞；
  - 汇编代码绕过了 Rust 的内存安全检查。

---

```rust
pub fn sys_write(fd: usize, buffer: &[u8]) -> isize {
    syscall(SYSCALL_WRITE, [fd, buffer.as_ptr() as usize, buffer.len()])
}
```

`sys_write` 封装 `write` 系统调用，提供类型安全的接口。  
- **参数转换**：
  - `buffer.as_ptr() as usize`：将字节切片的起始地址转换为裸指针整数，作为用户空间缓冲区地址传给内核；
  - `buffer.len()`：传递缓冲区长度。
- **权限控制体现**：
  - 用户程序仅能传递地址和长度，无法控制内核如何解释该地址；
  - 内核在 `sys_write` 中通过 `core::slice::from_raw_parts` 重建切片，并验证 `fd == 1`，确保只能写入标准输出；
  - 即使用户传入任意地址（如内核地址），内核的页表设置（用户态无法访问内核页）或 trap handler（如 `StoreFault`）会阻止非法访问。

---

```rust
pub fn sys_exit(exit_code: i32) -> isize {
    syscall(SYSCALL_EXIT, [exit_code as usize, 0, 0])
}
```

`sys_exit` 封装 `exit` 系统调用，用于终止当前应用。  
- **参数处理**：仅使用第一个参数传递退出码，其余参数填 0（符合 ABI，但内核只读取 `a0`）。
- **行为**：调用后永不返回（内核调用 `run_next_app()` 切换任务），因此返回值实际无意义，但保留 `isize` 以统一接口。
- **权限意义**：允许用户程序主动退出，但不能强制终止其他任务或关机（除非是最后一个应用），体现了受控的生命周期管理。