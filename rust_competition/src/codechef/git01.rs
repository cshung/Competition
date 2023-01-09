// https://www.codechef.com/problems/GIT01

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

pub fn codechef_git01()
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
        let find_space_result = test_line.find(' ');
        if find_space_result.is_none()
        {
            return;
        }
        let space_index = find_space_result.unwrap();
        let test_token_1 = &test_line[..space_index];
        let test_token_2 = &test_line[space_index + 1..];
        let parse_height_result = test_token_1.parse::<usize>();
        let parse_width_result = test_token_2.parse::<usize>();
        if parse_height_result.is_err()
        {
            return;
        }
        if parse_width_result.is_err()
        {
            return;
        }
        let width = parse_width_result.unwrap();
        let height = parse_height_result.unwrap();
        let mut cur_row = 0;
        let mut cost1 = 0;
        let mut cost2 = 0;
        for _row in 0..height
        {
            let read_test_matrix_row_result = read_line(&stdin);
            if read_test_matrix_row_result.is_err()
            {
                return;
            }
            let test_matrix_row = read_test_matrix_row_result.unwrap();
            if test_matrix_row.len() != width
            {
                return;
            }
            let mut cur = cur_row;
            for c in test_matrix_row.chars()
            {
                if c == 'R'
                {
                    if cur == 0
                    {
                        cost2 = cost2 + 5;
                    }
                    else
                    {
                        cost1 = cost1 + 5;
                    }
                }
                else if c == 'G'
                {
                    if cur == 0
                    {
                        cost1 = cost1 + 3;
                    }
                    else
                    {
                        cost2 = cost2 + 3;
                    }
                }
                else
                {
                    return;
                }
                cur = 1 - cur;
            }
            cur_row = 1 - cur_row;
        }
        if cost1 > cost2
        {
            println!("{}", cost2);
        }
        else
        {
            println!("{}", cost1);            
        }
    }
}