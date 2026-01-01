//! 时间戳支持

use core::sync::atomic::{AtomicU64, Ordering};
use crate::console::{write_str, putchar};

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

/// 格式化并输出时间戳
pub fn format_timestamp(nanos: u64) {
    let seconds = nanos / 1_000_000_000;
    let millis = (nanos % 1_000_000_000) / 1_000_000;
    let micros = (nanos % 1_000_000) / 1_000;

    write_str("[");
    write_num(seconds as u32);
    write_str(".");
    write_num(millis as u32);
    write_str(".");
    write_num(micros as u32);
    write_str("]");
}

fn write_num(mut n: u32) {
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
    while i < 10 {
        putchar(buf[i]);
        i += 1;
    }
}
