// src/back_of_house.rs
pub fn fix_incorrect_order() {
    cook_order();
    crate::front_of_house::serving::serve_order();
}

pub fn cook_order() {}