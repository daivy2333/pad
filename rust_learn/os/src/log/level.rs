//! 日志级别定义

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
