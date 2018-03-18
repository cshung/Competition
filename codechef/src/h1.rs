// https://www.codechef.com/problems/H1

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

fn h1(stdin: &io::Stdin) -> Option<[i32; 9]>
{
    let mut result: [i32; 9] = [0; 9];
    let read_blank_line_result = read_line(&stdin);
    if read_blank_line_result.is_err()
    {
        return None;
    }    
    return Some(result);
}

pub fn codechef_h1()
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
        h1(&stdin);
    }    
}