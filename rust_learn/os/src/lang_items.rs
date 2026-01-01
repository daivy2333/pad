use core::panic::PanicInfo;
use crate::{sbi::shutdown};

#[panic_handler]
fn panic(info: &PanicInfo) -> !
{
    if let Some(location) = info.location() {
        crate::log::_log(
            crate::log::LogLevel::Error,
            format_args!(
                "Panicked at {}:{} {}",
                location.file(),
                location.line(),
                info.message().as_str().unwrap()
            )
        );
    } else {
        crate::log::_log(
            crate::log::LogLevel::Error,
            format_args!("Panicked: {}", info.message().as_str().unwrap())
        );
    }

    shutdown(true)
}