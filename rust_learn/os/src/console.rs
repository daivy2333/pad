use crate::sbi::console_putchar;
use core::fmt::{self,Write};

struct Stdout;

impl Write for Stdout {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        for c in s.bytes() {
            console_putchar(c as usize);
        }
        Ok(())
    }
}

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

pub fn print(args: fmt::Arguments)
{
    Stdout.write_fmt(args).unwrap();
}

#[macro_export]
macro_rules! print {
    ($fmt: literal $(, $($arg:tt)+)?) => {
        $crate::console::print(format_args!($fmt $(,$($arg)+)?));
    }
}

#[macro_export]
macro_rules! println {
    ($fmt: literal $(, $($arg: tt)+)?) => {
        $crate::console::print(format_args!(concat!($fmt, "\n") $(, $($arg)+)?));
    }
}