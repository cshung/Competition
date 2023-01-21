mod codechef;
mod leetcode;

fn main() {
    if 1 == 0 {
        //
        // Please the Rust compiler happy with dead code
        //
        codechef::nw1::codechef_nw1();
        codechef::git01::codechef_git01();
        codechef::rectangl::codechef_rectangl();

        leetcode::two_sum::two_sum();
        leetcode::minimum_rounds_to_complete_all_tasks::minimum_rounds_to_complete_all_tasks();
        leetcode::maximum_ice_cream_bars::maximum_ice_cream_bars();
        leetcode::minimum_number_of_arrows_to_burst_balloons::minimum_number_of_arrows_to_burst_balloons();
        leetcode::gas_station::gas_station();
        leetcode::max_points_on_a_line::max_points_on_a_line();
        leetcode::binary_tree_preorder_traversal::binary_tree_preorder_traversal();
        leetcode::same_tree::same_tree();
        leetcode::minimum_time_to_collect_all_apples_in_a_tree::minimum_time_to_collect_all_apples_in_a_tree();
        leetcode::number_of_nodes_in_the_sub_tree_with_the_same_label::number_of_nodes_in_the_sub_tree_with_the_same_label();
        leetcode::longest_path_with_different_adjacent_characters::longest_path_with_different_adjacent_characters();
        leetcode::lexicographically_smallest_equivalent_string::lexicographically_smallest_equivalent_string();
        leetcode::number_of_good_paths::number_of_good_paths();
        leetcode::insert_interval::insert_interval();
        leetcode::flip_string_to_monotone_increasing::flip_string_to_monotone_increasing();
        leetcode::maximum_sum_circular_subarray::maximum_sum_circular_subarray();
        leetcode::subarray_sums_divisible_by_k::subarray_sums_divisible_by_k();
        leetcode::non_decreasing_subsequences::non_decreasing_subsequences();
    }
    leetcode::restore_ip_addresses::restore_ip_addresses();
}
