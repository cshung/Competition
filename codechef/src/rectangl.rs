// https://www.codechef.com/problems/RECTANGL

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

pub fn codechef_rectangl()
{
    let stdin = io::stdin();
    let read_first_line_result = read_line(&stdin);
    if read_first_line_result.is_err()
    {
        return;
    }
    let first_line = read_first_line_result.unwrap();    
    let parse_first_line_result = first_line.parse::<usize>();
    if parse_first_line_result.is_err()
    {
        return;
    }
    let t = parse_first_line_result.unwrap();
    for _i in 0..t
    {
        let read_test_line_result = read_line(&stdin);
        if read_test_line_result.is_err()
        {
            return;
        }
        let test_line = read_test_line_result.unwrap();
        let mut iter = test_line.split_whitespace();
        let optional_token_1 = iter.next();
        if optional_token_1.is_none()
        {
            return;
        }
        let optional_token_2 = iter.next();
        if optional_token_2.is_none()
        {
            return;
        }
        let optional_token_3 = iter.next();
        if optional_token_3.is_none()
        {
            return;
        }
        let optional_token_4 = iter.next();
        if optional_token_4.is_none()
        {
            return;
        }
        let token1 = optional_token_1.unwrap();
        let token2 = optional_token_2.unwrap();
        let token3 = optional_token_3.unwrap();
        let token4 = optional_token_4.unwrap();
        let token1_parse_result = token1.parse::<i32>();
        let token2_parse_result = token2.parse::<i32>();
        let token3_parse_result = token3.parse::<i32>();
        let token4_parse_result = token4.parse::<i32>();
        if token1_parse_result.is_err()
        {
            return;
        }
        if token2_parse_result.is_err()
        {
            return;
        }
        if token3_parse_result.is_err()
        {
            return;
        }
        if token4_parse_result.is_err()
        {
            return;
        }
        let a = token1_parse_result.unwrap();
        let b = token2_parse_result.unwrap();
        let c = token3_parse_result.unwrap();
        let d = token4_parse_result.unwrap();
        if (a == b && c == d) || (a == c) && (b == d) || (a == d) && (b == c)
        {
            println!("YES");
        }
        else {
            println!("NO");
        }
    }
}