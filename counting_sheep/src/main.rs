use std::io;
use std::io::prelude::*;
use std::i64;

fn all_seen(digits_seen: &[bool]) -> bool {
    digits_seen.iter().all(|&x| x)
}

fn add_digits(n: &str, digits_seen: &mut [bool]) {
    for c in n.chars() {
        let index = char::to_digit(c, 10).unwrap();
        digits_seen[index as usize] = true;
    }
}

fn count(n: i64) -> i64 {
    let mut mult = 1;
    let mut n_str: String = "".to_string();
    let mut digits_seen: Vec<bool> = vec![false; 10];

    while !all_seen(&digits_seen) {
        n_str = (n * mult).to_string();
        add_digits(&n_str, &mut digits_seen);
        mult += 1;
    }

    i64::from_str_radix(&n_str, 10).expect("Error")
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).expect("Error reading stdin");

    let print_out = |line: i64, count: &str| println!("Case #{}: {}", line, count);

    let mut line_number = 0;
    // Skip first line
    for line in input.split("\n").skip(1) {
        line_number += 1;
        let number = line.trim();
        if line.is_empty() {
            continue;
        }
        if line == "0" {
            print_out(line_number, "INSOMNIA");
            continue;
        }
        let n: i64 = i64::from_str_radix(&number, 10).expect("Invalid argument");
        print_out(line_number, &count(n).to_string());
    }
}
