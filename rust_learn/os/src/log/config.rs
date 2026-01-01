//! 日志配置

use spin::Once;

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

/// 默认配置
const DEFAULT_CONFIG: LogConfig = LogConfig {
    enable_timestamp: true,
    enable_cpu_id: true,
    enable_thread_info: true,
    enable_location: true,
    enable_function: true,
    enable_color: true,
};

/// 全局配置
static CONFIG: Once<LogConfig> = Once::new();

/// 初始化配置
pub fn init_config(config: LogConfig) {
    CONFIG.call_once(|| config);
}

/// 获取配置
pub fn config() -> &'static LogConfig {
    CONFIG.get().unwrap_or(&DEFAULT_CONFIG)
}
