use crate::trap::TrapContext;
use crate::sync::UPSafeCell;
use lazy_static::lazy_static;

const MAX_APP_NUM: usize = 4;
const APP_BASE_ADDRESS: usize = 0x80400000;

struct AppManager {
    num_app: usize,
    current_app: usize,
    app_start: [usize; MAX_APP_NUM + 1],
}

impl AppManager {
    fn get_current_app(&self) -> usize {
        self.current_app
    }

    unsafe fn load_app(&self, app_id: usize) {
        let app_start = self.app_start[app_id];
        let app_end = self.app_start[app_id + 1];
        let app_size = app_end - app_start;
        unsafe {
            core::slice::from_raw_parts_mut(app_start as *const u8 as *mut u8, app_size)
                .copy_from_slice(core::slice::from_raw_parts(APP_BASE_ADDRESS as *const u8, app_size));
        }
    }

    fn move_to_next_app(&mut self) {
        self.current_app += 1;
    }
}

lazy_static! {
    static ref APP_MANAGER: UPSafeCell<AppManager> = unsafe { UPSafeCell::new({
        unsafe extern "C" { fn _num_app(); }
        let num_app_ptr = _num_app as usize as *const usize;
        let num_app = num_app_ptr.read_volatile();
        let mut app_start: [usize; MAX_APP_NUM + 1] = [0; MAX_APP_NUM + 1];
        let app_start_raw: &[usize] = core::slice::from_raw_parts(
            num_app_ptr.add(1), num_app + 1
        );
        app_start[..=num_app].copy_from_slice(app_start_raw);
        AppManager {
            num_app,
            current_app: 0,
            app_start,
        }
    })};
}


const USER_STACK_SIZE: usize = 4096 * 2;
const KERNEL_STACK_SIZE: usize = 4096 * 2;

#[repr(align(4096))]
struct KernelStack {
    data: [u8; KERNEL_STACK_SIZE],
}

#[repr(align(4096))]
struct UserStack {
    data: [u8; USER_STACK_SIZE],
}

static KERNEL_STACK: KernelStack = KernelStack { data: [0; KERNEL_STACK_SIZE] };
static USER_STACK: UserStack = UserStack { data: [0; USER_STACK_SIZE] };

impl UserStack {
    fn get_sp(&self) -> usize {
        self.data.as_ptr() as usize + USER_STACK_SIZE
    }
}

impl KernelStack {
    fn push_context(&self, cx: TrapContext) -> usize {
        let cx_ptr = self.data.as_ptr() as usize + KERNEL_STACK_SIZE - core::mem::size_of::<TrapContext>();
        unsafe {
            (cx_ptr as *mut TrapContext).write(cx);
        }
        cx_ptr
    }
}



pub fn run_next_app() -> ! {
    let mut app_manager = APP_MANAGER.exclusive_access();
    let current_app = app_manager.get_current_app();
    unsafe {
        app_manager.load_app(current_app);
    }
    app_manager.move_to_next_app();
    drop(app_manager);
    // before this we have to drop local variables related to resources manually
    // and release the resources
    unsafe extern "C" { fn __restore(cx_addr: usize); }
    unsafe {
        __restore(KERNEL_STACK.push_context(
            TrapContext::app_init_context(APP_BASE_ADDRESS, USER_STACK.get_sp())
        ));
    }

    panic!("Unreachable in batch::run_current_app!");
}
