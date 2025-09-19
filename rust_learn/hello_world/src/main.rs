use std::cmp::Ordering;
use std::io;

use rand::Rng;

fn main()
{
    println!("Guess the number!");

    let secret_number = rand::thread_rng().gen_range(1..=100);

    loop
    {
        println!("please input");

        let mut guess = String::new();

        io::stdin()
        .read_line(&mut guess)
        .expect("failed to in");

        let guess: u32 = match guess.trim().parse()
        {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("you guessed:{guess}");

        match guess.cmp(&secret_number)
        {
            Ordering::Less => println!("too small"),
            Ordering::Greater => println!("Too big"),
            Ordering::Equal =>
            {
                println!("you win");
                break;
            }
        }
    }
}