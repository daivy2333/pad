//! 日志宏定义

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
macro_rules! error_advanced {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Error, $($arg)*);
    };
}

/// 增强版 WARN
#[macro_export]
macro_rules! warn_advanced {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Warn, $($arg)*);
    };
}

/// 增强版 INFO
#[macro_export]
macro_rules! info_advanced {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Info, $($arg)*);
    };
}

/// 增强版 DEBUG
#[macro_export]
macro_rules! debug_advanced {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Debug, $($arg)*);
    };
}

/// 增强版 TRACE
#[macro_export]
macro_rules! trace_advanced {
    ($($arg:tt)*) => {
        $crate::log_internal_advanced!($crate::log::LogLevel::Trace, $($arg)*);
    };
}
