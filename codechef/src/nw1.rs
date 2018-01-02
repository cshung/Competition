// https://www.codechef.com/problems/NW1

use std::io;

fn read_line(stdin: &io::Stdin) -> io::Result<String>
{
    let mut input = String::new();
    match stdin.read_line(&mut input)
    {
        Ok(_) => Ok(input.trim().to_string()),
        Err(e) => Err(e)
    }
}

fn to_day_of_week(input: &str) -> Option<usize>
{
    if input == "mon"
    {
        Some(0)
    }
    else if input == "tues"
    {
        Some(1)
    }
    else if input == "wed"
    {
        Some(2)
    }
    else if input == "thurs"
    {
        Some(3)
    }
    else if input == "fri"
    {
        Some(4)
    }
    else if input == "sat"
    {
        Some(5)
    }
    else if input == "sun"
    {
        Some(6)
    }
    else
    { 
        None
    }
}

pub fn codechef_nw1()
{
    let stdin = io::stdin();
    let read_first_line_result = read_line(&stdin);
    if read_first_line_result.is_ok()
    {
        let first_line = read_first_line_result.unwrap();
        let parse_first_line_result = first_line.parse::<i32>();
        if parse_first_line_result.is_ok()
        {
            let t = parse_first_line_result.unwrap();
            for _i in 0..t
            {
                let read_test_line_result = read_line(&stdin);
                if read_test_line_result.is_ok()
                {
                    let test_line = read_test_line_result.unwrap();
                    let find_space_result = test_line.find(' ');
                    if find_space_result.is_some()
                    {
                        let space_index = find_space_result.unwrap();
                        let test_token_1 = &test_line[..space_index];
                        let test_token_2 = &test_line[space_index + 1..];
                        let parse_day_result = test_token_1.parse::<i32>();
                        if parse_day_result.is_ok()
                        {
                            let days = parse_day_result.unwrap();
                            let day_of_week_result = to_day_of_week(test_token_2);
                            if day_of_week_result.is_some()
                            {
                                let mut day_of_week = day_of_week_result.unwrap();
                                let mut stats = [0, 0, 0, 0, 0, 0, 0];
                                for _d in 0..days
                                {
                                    stats[day_of_week] = stats[day_of_week] + 1;
                                    day_of_week = day_of_week + 1;
                                    day_of_week = day_of_week % 7;
                                }
                                println!("{} {} {} {} {} {} {}", stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6]);
                            }                            
                        }
                    }
                }
            }
        }
    }
}