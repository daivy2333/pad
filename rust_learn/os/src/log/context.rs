//! CPU 和线程信息支持

use core::sync::atomic::{AtomicU32, Ordering};

/// 当前线程 ID
static CURRENT_THREAD_ID: AtomicU32 = AtomicU32::new(0);

/// 当前线程名称
static mut THREAD_NAME: [u8; 32] = [b'u', b'n', b'k', b'n', b'o', b'w', b'n', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

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

/// 设置当前线程 ID
pub fn set_current_thread_id(id: u32) {
    CURRENT_THREAD_ID.store(id, Ordering::Relaxed);
}

/// 获取当前线程 ID
pub fn current_thread_id() -> u32 {
    CURRENT_THREAD_ID.load(Ordering::Relaxed)
}

/// 设置线程名称
pub fn set_thread_name(name: &'static str) {
    unsafe {
        let bytes = name.as_bytes();
        let len = bytes.len().min(31);
        THREAD_NAME[..len].copy_from_slice(&bytes[..len]);
        THREAD_NAME[len] = 0;
    }
}

/// 获取线程名称
pub fn thread_name() -> &'static str {
    unsafe {
        // 使用 addr_of! 宏获取地址，不创建共享引用
        let ptr = core::ptr::addr_of!(THREAD_NAME) as *const u8;
        let mut len = 0;
        while len < 32 && *ptr.add(len) != 0 {
            len += 1;
        }
        core::str::from_utf8_unchecked(core::slice::from_raw_parts(ptr, len))
    }
}
