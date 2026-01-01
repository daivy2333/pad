我来为你设计一个完整的彩色日志系统。这个系统会包含宏支持、可变参数、日志级别控制等功能。

一、基础彩色输出实现

1. 基础颜色定义

// src/console/color.rs
#![allow(unused)]

/// ANSI 颜色代码
#[allow(dead_code)]
pub mod color {
    pub const RESET: &str = "\x1b[0m";
    pub const BOLD: &str = "\x1b[1m";
    pub const UNDERLINE: &str = "\x1b[4m";
    
    // 前景色
    pub const BLACK: &str = "\x1b[30m";
    pub const RED: &str = "\x1b[31m";
    pub const GREEN: &str = "\x1b[32m";
    pub const YELLOW: &str = "\x1b[33m";
    pub const BLUE: &str = "\x1b[34m";
    pub const MAGENTA: &str = "\x1b[35m";
    pub const CYAN: &str = "\x1b[36m";
    pub const WHITE: &str = "\x1b[37m";
    pub const GRAY: &str = "\x1b[90m";
    
    // 亮色
    pub const BRIGHT_RED: &str = "\x1b[91m";
    pub const BRIGHT_GREEN: &str = "\x1b[92m";
    pub const BRIGHT_YELLOW: &str = "\x1b[93m";
    pub const BRIGHT_BLUE: &str = "\x1b[94m";
    pub const BRIGHT_MAGENTA: &str = "\x1b[95m";
    pub const BRIGHT_CYAN: &str = "\x1b[96m";
    pub const BRIGHT_WHITE: &str = "\x1b[97m";
    
    // 背景色
    pub const BG_BLACK: &str = "\x1b[40m";
    pub const BG_RED: &str = "\x1b[41m";
    pub const BG_GREEN: &str = "\x1b[42m";
    pub const BG_YELLOW: &str = "\x1b[43m";
    pub const BG_BLUE: &str = "\x1b[44m";
    pub const BG_MAGENTA: &str = "\x1b[45m";
    pub const BG_CYAN: &str = "\x1b[46m";
    pub const BG_WHITE: &str = "\x1b[47m";
    pub const BG_GRAY: &str = "\x1b[100m";
}


2. 日志级别定义

// src/log/level.rs
#![allow(unused)]

use core::fmt;

/// 日志级别
#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
pub enum LogLevel {
    /// 错误 - 红色
    Error = 0,
    /// 警告 - 黄色
    Warn  = 1,
    /// 信息 - 蓝色
    Info  = 2,
    /// 调试 - 绿色
    Debug = 3,
    /// 跟踪 - 灰色
    Trace = 4,
}

impl LogLevel {
    /// 获取级别名称
    pub fn as_str(&self) -> &'static str {
        match self {
            LogLevel::Error => "ERROR",
            LogLevel::Warn  => "WARN",
            LogLevel::Info  => "INFO",
            LogLevel::Debug => "DEBUG",
            LogLevel::Trace => "TRACE",
        }
    }
    
    /// 获取级别颜色
    pub fn color(&self) -> &'static str {
        match self {
            LogLevel::Error => "\x1b[1;31m",  // 亮红色
            LogLevel::Warn  => "\x1b[1;33m",  // 亮黄色
            LogLevel::Info  => "\x1b[1;34m",  // 亮蓝色
            LogLevel::Debug => "\x1b[1;32m",  // 亮绿色
            LogLevel::Trace => "\x1b[90m",    // 灰色
        }
    }
    
    /// 获取重置序列
    pub fn reset_color(&self) -> &'static str {
        "\x1b[0m"
    }
}

impl fmt::Display for LogLevel {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.as_str())
    }
}


二、日志系统核心实现

1. 全局日志配置

// src/log/mod.rs
#![allow(unused)]

mod level;
pub use level::LogLevel;

use core::sync::atomic::{AtomicU8, Ordering};
use spin::Mutex;
use crate::console::{putchar, write_str};
use core::fmt;

/// 全局日志级别
static LOG_LEVEL: AtomicU8 = AtomicU8::new(LogLevel::Info as u8);

/// 日志输出锁（防止多核竞争）
static LOG_LOCK: Mutex<()> = Mutex::new(());

/// 设置全局日志级别
pub fn set_max_level(level: LogLevel) {
    LOG_LEVEL.store(level as u8, Ordering::Relaxed);
}

/// 获取当前日志级别
pub fn max_level() -> LogLevel {
    match LOG_LEVEL.load(Ordering::Relaxed) {
        0 => LogLevel::Error,
        1 => LogLevel::Warn,
        2 => LogLevel::Info,
        3 => LogLevel::Debug,
        4 => LogLevel::Trace,
        _ => LogLevel::Info,
    }
}

/// 检查是否应该输出指定级别的日志
pub fn should_log(level: LogLevel) -> bool {
    (level as u8) <= LOG_LEVEL.load(Ordering::Relaxed)
}

/// 基础日志输出函数
#[doc(hidden)]
pub fn _log(level: LogLevel, args: fmt::Arguments) {
    if !should_log(level) {
        return;
    }
    
    // 获取锁，防止多核竞争输出
    let _lock = LOG_LOCK.lock();
    
    // 输出日志前缀
    let prefix = format!(
        "{}{:<5}{} ",
        level.color(),
        level.as_str(),
        level.reset_color()
    );
    
    write_str(&prefix);
    
    // 输出日志内容
    write_str(&format!("{}", args));
    
    // 确保换行
    putchar(b'\n');
}


2. 宏定义实现

// src/log/macros.rs
#![allow(unused)]

/// 核心宏实现
#[macro_export]
macro_rules! log_internal {
    ($level:expr, $($arg:tt)*) => {{
        use $crate::log::_log;
        _log($level, format_args!($($arg)*));
    }};
}

/// ERROR 级别日志
#[macro_export]
macro_rules! error {
    ($($arg:tt)*) => {
        $crate::log_internal!($crate::log::LogLevel::Error, $($arg)*);
    };
}

/// WARN 级别日志
#[macro_export]
macro_rules! warn {
    ($($arg:tt)*) => {
        $crate::log_internal!($crate::log::LogLevel::Warn, $($arg)*);
    };
}

/// INFO 级别日志
#[macro_export]
macro_rules! info {
    ($($arg:tt)*) => {
        $crate::log_internal!($crate::log::LogLevel::Info, $($arg)*);
    };
}

/// DEBUG 级别日志
#[macro_export]
macro_rules! debug {
    ($($arg:tt)*) => {
        $crate::log_internal!($crate::log::LogLevel::Debug, $($arg)*);
    };
}

/// TRACE 级别日志
#[macro_export]
macro_rules! trace {
    ($($arg:tt)*) => {
        $crate::log_internal!($crate::log::LogLevel::Trace, $($arg)*);
    };
}


三、增强版日志系统（带时间戳、CPU、线程信息）

1. 时间戳支持

// src/log/timestamp.rs
#![allow(unused)]

use core::sync::atomic::{AtomicU64, Ordering};
use core::fmt;

/// 系统启动后的纳秒数
static SYSTEM_NANOS: AtomicU64 = AtomicU64::new(0);

/// 更新时间戳
pub fn update_nanos(nanos: u64) {
    SYSTEM_NANOS.store(nanos, Ordering::Relaxed);
}

/// 获取当前时间戳
pub fn current_timestamp() -> u64 {
    SYSTEM_NANOS.load(Ordering::Relaxed)
}

/// 格式化时间戳
pub fn format_timestamp(nanos: u64) -> String {
    let seconds = nanos / 1_000_000_000;
    let millis = (nanos % 1_000_000_000) / 1_000_000;
    let micros = (nanos % 1_000_000) / 1_000;
    
    format!("[{:>5}.{:03}.{:03}]", seconds, millis, micros)
}


2. CPU 和线程信息

// src/log/context.rs
#![allow(unused)]

use core::sync::atomic::{AtomicU32, Ordering};
use core::cell::Cell;
use core::fmt;

/// 获取当前 CPU 核心 ID
pub fn current_cpu_id() -> u32 {
    #[cfg(target_arch = "riscv64")]
    {
        let hartid: usize;
        unsafe {
            core::arch::asm!("mv {}, tp", out(reg) hartid);
        }
        hartid as u32
    }
    #[cfg(not(target_arch = "riscv64"))]
    {
        0
    }
}

/// 当前线程 ID
thread_local! {
    static CURRENT_THREAD_ID: Cell<u32> = Cell::new(0);
}

/// 设置当前线程 ID
pub fn set_current_thread_id(id: u32) {
    CURRENT_THREAD_ID.with(|cell| cell.set(id));
}

/// 获取当前线程 ID
pub fn current_thread_id() -> u32 {
    CURRENT_THREAD_ID.with(|cell| cell.get())
}

/// 线程名称
thread_local! {
    static THREAD_NAME: Cell<&'static str> = Cell::new("unknown");
}

/// 设置线程名称
pub fn set_thread_name(name: &'static str) {
    THREAD_NAME.with(|cell| cell.set(name));
}

/// 获取线程名称
pub fn thread_name() -> &'static str {
    THREAD_NAME.with(|cell| cell.get())
}


3. 增强版日志输出

// src/log/advanced.rs
#![allow(unused)]

use crate::log::{LogLevel, _log};
use crate::console::{write_str, putchar};
use core::fmt;
use spin::Mutex;
use crate::log::timestamp;
use crate::log::context;

/// 增强版日志输出
#[doc(hidden)]
pub fn _log_advanced(
    level: LogLevel,
    file: &'static str,
    line: u32,
    function: &'static str,
    args: fmt::Arguments
) {
    use crate::log::should_log;
    
    if !should_log(level) {
        return;
    }
    
    // 获取锁
    let _lock = crate::log::LOG_LOCK.lock();
    
    // 构建完整的日志前缀
    let prefix = format!(
        "{}{} {}[CPU{}][T{}:{}] {:<5}{} {}:{} {}(): ",
        level.color(),
        timestamp::format_timestamp(timestamp::current_timestamp()),
        "\x1b[90m",  // 灰色
        context::current_cpu_id(),
        context::current_thread_id(),
        context::thread_name(),
        level.as_str(),
        level.reset_color(),
        file,
        line,
        function
    );
    
    write_str(&prefix);
    write_str(&format!("{}", args));
    putchar(b'\n');
}


4. 增强版宏

// src/log/macros_advanced.rs
#![allow(unused)]

/// 带位置信息的日志宏
#[macro_export]
macro_rules! log_internal_advanced {
    ($level:expr, $($arg:tt)*) => {{
        use $crate::log::_log_advanced;
        _log_advanced(
            $level,
            file!(),
            line!(),
            function!(),
            format_args!($($arg)*)
        );
    }};
}

/// 增强版 ERROR
#[macro_export]
macro_rules! error {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Error, $($arg)*);
    };
}

/// 增强版 WARN
#[macro_export]
macro_rules! warn {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Warn, $($arg)*);
    };
}

/// 增强版 INFO
#[macro_export]
macro_rules! info {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Info, $($arg)*);
    };
}

/// 增强版 DEBUG
#[macro_export]
macro_rules! debug {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Debug, $($arg)*);
    };
}

/// 增强版 TRACE
#[macro_export]
macro_rules! trace {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Trace, $($arg)*);
    };
}


四、集成到现有系统

1. 模块导出

// src/log/mod.rs（完整版）
#![allow(unused)]

pub mod level;
mod timestamp;
mod context;
#[macro_use]
mod macros;
mod advanced;
mod macros_advanced;

pub use level::LogLevel;
pub use timestamp::{update_nanos, current_timestamp, format_timestamp};
pub use context::{current_cpu_id, set_current_thread_id, current_thread_id, set_thread_name, thread_name};

use core::fmt;
use core::sync::atomic::{AtomicU8, Ordering};
use spin::Mutex;
use crate::console::{write_str, putchar};

// 配置
static LOG_LEVEL: AtomicU8 = AtomicU8::new(LogLevel::Info as u8);
static LOG_LOCK: Mutex<()> = Mutex::new(());

// 简单版本导出
pub use macros::*;
// 或者使用增强版本
// pub use macros_advanced::*;

// 配置函数
pub fn init(level: LogLevel) {
    set_max_level(level);
    info!("日志系统初始化完成，级别: {}", level);
}

pub fn set_max_level(level: LogLevel) {
    LOG_LEVEL.store(level as u8, Ordering::SeqCst);
    info!("设置日志级别为: {}", level);
}

pub fn get_max_level() -> LogLevel {
    match LOG_LEVEL.load(Ordering::Relaxed) {
        0 => LogLevel::Error,
        1 => LogLevel::Warn,
        2 => LogLevel::Info,
        3 => LogLevel::Debug,
        4 => LogLevel::Trace,
        _ => LogLevel::Info,
    }
}

#[doc(hidden)]
pub fn _log_simple(level: LogLevel, args: fmt::Arguments) {
    if (level as u8) > LOG_LEVEL.load(Ordering::Relaxed) {
        return;
    }
    
    let _lock = LOG_LOCK.lock();
    
    // 简单前缀
    write_str(&format!(
        "{}{:<5}{} ",
        level.color(),
        level.as_str(),
        level.reset_color()
    ));
    
    write_str(&format!("{}", args));
    putchar(b'\n');
}


2. 在 main.rs 中使用

// src/main.rs
#![no_std]
#![no_main]

mod console;
mod log;
mod sbi;

use log::{LogLevel, info, error, warn, debug, trace, init};
use core::panic::PanicInfo;

#[no_mangle]
pub extern "C" fn rust_main() -> ! {
    // 初始化日志系统
    log::init(LogLevel::Debug);
    
    info!("操作系统启动...");
    
    // 测试不同级别的日志
    error!("这是一个错误信息");
    warn!("这是一个警告信息");
    info!("这是一个信息级别消息");
    debug!("这是一个调试信息");
    trace!("这是一个跟踪信息");
    
    // 显示内存布局
    let s_text = 0x8020_0000usize;
    let e_text = 0x8021_0000usize;
    let s_rodata = 0x8021_0000usize;
    let e_rodata = 0x8022_0000usize;
    let s_data = 0x8022_0000usize;
    let e_data = 0x8023_0000usize;
    
    info!(".text [{:#x}, {:#x})", s_text, e_text);
    info!(".rodata [{:#x}, {:#x})", s_rodata, e_rodata);
    info!(".data [{:#x}, {:#x})", s_data, e_data);
    
    // 切换日志级别
    info!("切换日志级别为 INFO");
    log::set_max_level(LogLevel::Info);
    
    // 这些不会输出
    debug!("这个调试信息不会显示");
    trace!("这个跟踪信息也不会显示");
    
    // 这些会输出
    error!("错误信息仍然显示");
    warn!("警告信息也显示");
    info!("信息级别显示");
    
    // 使用格式化
    let x = 42;
    let y = 3.14;
    info!("格式化输出: x = {}, y = {:.2}", x, y);
    
    loop {}
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    error!("系统发生 panic: {}", info);
    sbi::shutdown();
}


3. console.rs 更新

// src/console.rs
#![allow(unused)]

use core::fmt;
use crate::sbi::console_putchar;

/// 打印字符到控制台
pub fn putchar(c: u8) {
    console_putchar(c as usize);
}

/// 打印字符串到控制台
pub fn write_str(s: &str) {
    for c in s.bytes() {
        putchar(c);
    }
}

/// 实现 Write trait
pub struct Stdout;

impl fmt::Write for Stdout {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        write_str(s);
        Ok(())
    }
}

/// 打印宏
#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => {{
        use core::fmt::Write;
        let _ = write!($crate::console::Stdout, $($arg)*);
    }};
}

#[macro_export]
macro_rules! println {
    () => {
        $crate::print!("\n")
    };
    ($($arg:tt)*) => {{
        $crate::print!($($arg)*);
        $crate::print!("\n");
    }};
}


五、编译开关控制

1. 条件编译配置

// src/log/config.rs
#![allow(unused)]

/// 日志配置
#[derive(Debug, Clone, Copy)]
pub struct LogConfig {
    /// 是否启用时间戳
    pub enable_timestamp: bool,
    /// 是否启用 CPU ID
    pub enable_cpu_id: bool,
    /// 是否启用线程信息
    pub enable_thread_info: bool,
    /// 是否启用文件名和行号
    pub enable_location: bool,
    /// 是否启用函数名
    pub enable_function: bool,
    /// 是否启用彩色输出
    pub enable_color: bool,
}

impl Default for LogConfig {
    fn default() -> Self {
        Self {
            enable_timestamp: true,
            enable_cpu_id: true,
            enable_thread_info: true,
            enable_location: true,
            enable_function: true,
            enable_color: true,
        }
    }
}

/// 全局配置
static CONFIG: spin::Once<LogConfig> = spin::Once::new();

/// 初始化配置
pub fn init_config(config: LogConfig) {
    CONFIG.call_once(|| config);
}

/// 获取配置
pub fn config() -> &'static LogConfig {
    CONFIG.get().unwrap_or(&LogConfig::default())
}


2. 根据配置动态调整

// 使用配置的日志输出
pub fn format_log_prefix(
    level: LogLevel,
    file: &str,
    line: u32,
    function: &str
) -> String {
    let config = crate::log::config::config();
    let mut prefix = String::new();
    
    if config.enable_color {
        prefix.push_str(level.color());
    }
    
    if config.enable_timestamp {
        prefix.push_str(&format!("{} ", timestamp::format_timestamp(
            timestamp::current_timestamp()
        )));
    }
    
    if config.enable_cpu_id {
        prefix.push_str(&format!("[CPU{}] ", context::current_cpu_id()));
    }
    
    if config.enable_thread_info {
        prefix.push_str(&format!("[T{}:{}] ", 
            context::current_thread_id(),
            context::thread_name()
        ));
    }
    
    if config.enable_color {
        prefix.push_str(&format!("{:<5}{} ", 
            level.as_str(), 
            level.reset_color()
        ));
    } else {
        prefix.push_str(&format!("{:<5} ", level.as_str()));
    }
    
    if config.enable_location {
        prefix.push_str(&format!("{}:{} ", file, line));
    }
    
    if config.enable_function {
        prefix.push_str(&format!("{}(): ", function));
    }
    
    prefix
}


六、测试和使用示例

1. 完整测试代码

// tests/log_test.rs
#![no_std]
#![no_main]

#[test_case]
fn test_log_levels() {
    use crate::log::{LogLevel, set_max_level};
    
    // 测试 ERROR 级别
    set_max_level(LogLevel::Error);
    error!("这个应该显示");
    warn!("这个不应该显示");
    info!("这个不应该显示");
    
    // 测试 INFO 级别
    set_max_level(LogLevel::Info);
    error!("这个应该显示");
    warn!("这个应该显示");
    info!("这个应该显示");
    debug!("这个不应该显示");
    trace!("这个不应该显示");
    
    // 测试 TRACE 级别
    set_max_level(LogLevel::Trace);
    trace!("所有级别都应该显示");
}

#[test_case]
fn test_log_format() {
    info!("简单信息");
    info!("带参数: x = {}, y = {}", 10, 20);
    info!("内存地址: {:#x}", 0x80200000);
    info!("二进制: {:b}", 42);
    
    let name = "操作系统";
    let version = 1.0;
    info!("{} 版本: {:.1}", name, version);
}


2. 在实际代码中使用

// 在启动代码中使用
pub extern "C" fn rust_main() -> ! {
    // 初始化日志
    log::init(LogLevel::Debug);
    
    // 设置线程信息
    log::set_current_thread_id(1);
    log::set_thread_name("main");
    
    info!("操作系统启动中...");
    
    // 内存初始化
    unsafe {
        zero_bss();
        info!("BSS 段已清零");
        
        init_heap();
        info!("堆初始化完成，大小: {} KB", HEAP_SIZE / 1024);
    }
    
    // 设备初始化
    init_serial();
    info!("串口初始化完成");
    
    init_timer();
    info!("定时器初始化完成");
    
    // 启动调度器
    let num_tasks = scheduler::init();
    info!("调度器初始化完成，任务数: {}", num_tasks);
    
    // 启动第一个任务
    scheduler::run();
    
    error!("不应执行到这里");
    loop {}
}

// 在异常处理中使用
#[no_mangle]
pub extern "C" fn trap_handler() {
    use riscv::register::{scause, stval, sepc};
    
    let cause = scause::read().cause();
    let value = stval::read();
    let pc = sepc::read();
    
    error!("发生异常: {:?}", cause);
    error!("异常值: {:#x}", value);
    error!("异常地址: {:#x}", pc);
    error!("调用栈:");
    
    // 打印调用栈
    backtrace::trace(|frame| {
        let ip = frame.ip();
        error!("  -> {:#x}", ip);
        true
    });
}


七、Makefile 配置

# Makefile
LOG_LEVEL ?= INFO

# 根据日志级别设置编译标志
ifeq ($(LOG_LEVEL),ERROR)
	RUSTFLAGS += -D LOG_LEVEL_ERROR
else ifeq ($(LOG_LEVEL),WARN)
	RUSTFLAGS += -D LOG_LEVEL_WARN
else ifeq ($(LOG_LEVEL),INFO)
	RUSTFLAGS += -D LOG_LEVEL_INFO
else ifeq ($(LOG_LEVEL),DEBUG)
	RUSTFLAGS += -D LOG_LEVEL_DEBUG
else ifeq ($(LOG_LEVEL),TRACE)
	RUSTFLAGS += -D LOG_LEVEL_TRACE
endif

# 运行目标
run:
	@echo "日志级别: $(LOG_LEVEL)"
	qemu-system-riscv64 \
		-machine virt \
		-nographic \
		-kernel target/riscv64gc-unknown-none-elf/debug/os \
		-smp 1 \
		-m 128M

# 不同级别的运行
run-error:
	@make run LOG_LEVEL=ERROR

run-warn:
	@make run LOG_LEVEL=WARN

run-info:
	@make run LOG_LEVEL=INFO

run-debug:
	@make run LOG_LEVEL=DEBUG

run-trace:
	@make run LOG_LEVEL=TRACE


八、输出效果示例


[0.000.000] [CPU0][T1:main] ERROR   src/main.rs:45 rust_main(): 操作系统启动...
[0.001.234] [CPU0][T1:main] WARN    src/memory.rs:128 init_heap(): 堆内存不足，使用备用区域
[0.002.345] [CPU0][T1:main] INFO    src/memory.rs:45 init_heap(): 堆初始化完成，大小: 1024 KB
[0.003.456] [CPU0][T2:sched] DEBUG   src/scheduler.rs:89 schedule(): 切换到任务 3
[0.004.567] [CPU0][T3:task1] TRACE   src/syscall.rs:23 sys_write(): 写入 1024 字节到文件描述符 1


总结

这个彩色日志系统具有以下特点：

1. 完整的日志级别：ERROR、WARN、INFO、DEBUG、TRACE
2. 彩色输出：每个级别有不同颜色
3. 可变参数：支持格式化字符串
4. 运行时控制：可动态调整日志级别
5. 丰富信息：时间戳、CPU、线程、文件位置
6. 线程安全：使用锁防止多核竞争
7. 配置灵活：可通过配置开启/关闭功能
8. 易于使用：通过宏提供简洁的API

这样的日志系统可以极大地提高操作系统开发和调试的效率。