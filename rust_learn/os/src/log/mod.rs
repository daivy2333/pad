//! 日志系统模块
//!
//! 提供彩色、可配置的日志输出功能

pub mod level;
pub mod timestamp;
pub mod context;
pub mod config;

use core::fmt::{self, Write};
use core::sync::atomic::{AtomicU8, Ordering};
use spin::Mutex;
use crate::console::{write_str, putchar};

// 导出日志级别
pub use level::LogLevel;

// 全局日志级别
static LOG_LEVEL: AtomicU8 = AtomicU8::new(LogLevel::Info as u8);

// 日志输出锁（防止多核竞争）
pub static LOG_LOCK: Mutex<()> = Mutex::new(());

/// 初始化日志系统
pub fn init(level: LogLevel) {
    set_max_level_silent(level);
    _log(LogLevel::Info, format_args!("level {}", level));
}

/// 设置全局日志级别（静默，不输出日志）
fn set_max_level_silent(level: LogLevel) {
    LOG_LEVEL.store(level as u8, Ordering::SeqCst);
}

/// 设置全局日志级别
pub fn set_max_level(level: LogLevel) {
    set_max_level_silent(level);
    _log(LogLevel::Info, format_args!("level {}", level));
}

/// 获取当前日志级别
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
    write_str(level.color());
    write_str(level.as_str());
    write_str(" ");
    write_str(level.reset_color());

    // 输出日志内容
    let mut buf = [0u8; 256]; // 简单的缓冲区
    let mut offset = 0;

    // 使用闭包来格式化输出
    {
        let mut writer = |s: &str| {
            for c in s.bytes() {
                if offset < buf.len() - 1 {
                    buf[offset] = c;
                    offset += 1;
                }
            }
        };

        // 直接处理格式化参数
        if let Some(s) = args.as_str() {
            writer(s);
        } else {
            // 对于复杂的格式化参数，使用 write_fmt
            struct LogWriter<F: FnMut(&str)> {
                write: F,
            }

            impl<F: FnMut(&str)> fmt::Write for LogWriter<F> {
                fn write_str(&mut self, s: &str) -> fmt::Result {
                    (self.write)(s);
                    Ok(())
                }
            }

            let mut log_writer = LogWriter { write: &mut writer };
            let _ = log_writer.write_fmt(args);
        }
    }

    buf[offset] = b'\n';

    for i in 0..=offset {
        putchar(buf[i]);
    }
}

/// 增强版日志输出
#[doc(hidden)]
pub fn _log_advanced(
    level: LogLevel,
    file: &'static str,
    line: u32,
    function: &'static str,
    args: fmt::Arguments
) {
    if !should_log(level) {
        return;
    }

    // 获取锁
    let _lock = LOG_LOCK.lock();

    // 输出日志前缀
    write_str(level.color());
    write_str("[");
    write_str(file);
    write_str(":");
    write_str(u8_slice_to_str(&itoa(line)));
    write_str(" ");
    write_str(function);
    write_str("] ");
    write_str(level.as_str());
    write_str(" ");
    write_str(level.reset_color());

    // 输出日志内容
    let mut buf = [0u8; 256]; // 简单的缓冲区
    let mut offset = 0;

    // 使用闭包来格式化输出
    {
        let mut writer = |s: &str| {
            for c in s.bytes() {
                if offset < buf.len() - 1 {
                    buf[offset] = c;
                    offset += 1;
                }
            }
        };

        // 直接处理格式化参数
        if let Some(s) = args.as_str() {
            writer(s);
        } else {
            // 对于复杂的格式化参数，使用 write_fmt
            struct LogWriter<F: FnMut(&str)> {
                write: F,
            }

            impl<F: FnMut(&str)> fmt::Write for LogWriter<F> {
                fn write_str(&mut self, s: &str) -> fmt::Result {
                    (self.write)(s);
                    Ok(())
                }
            }

            let mut log_writer = LogWriter { write: &mut writer };
            let _ = log_writer.write_fmt(args);
        }
    }

    buf[offset] = b'\n';

    for i in 0..=offset {
        putchar(buf[i]);
    }
}

// 简单的整数转字符串函数
fn itoa(mut n: u32) -> [u8; 10] {
    let mut buf = [0u8; 10];
    let mut i = 10;
    if n == 0 {
        i -= 1;
        buf[i] = b'0';
    } else {
        while n > 0 {
            i -= 1;
            buf[i] = (n % 10) as u8 + b'0';
            n /= 10;
        }
    }
    let mut result = [0u8; 10];
    let mut j = 0;
    while i < 10 {
        result[j] = buf[i];
        j += 1;
        i += 1;
    }
    result
}

// 将字节数组转换为字符串
fn u8_slice_to_str(slice: &[u8]) -> &str {
    unsafe {
        core::str::from_utf8_unchecked(slice)
    }
}

// 导出宏
#[macro_use]
pub mod macros;
