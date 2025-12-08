// src/main.rs
use hello_package::eat_at_restaurant;
use hello_package::front_of_house;
use hello_package::back_of_house;

fn main() {
    println!("{}", eat_at_restaurant());
    println!("{}", front_of_house::hosting::seat_at_table());
    back_of_house::fix_incorrect_order();
}