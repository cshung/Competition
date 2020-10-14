#include "stdafx.h"

// https://leetcode.com/problems/image-overlap/

#include "LEET_IMAGE_OVERLAP.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_IMAGE_OVERLAP
{
    class Solution
    {
    public:
        // The max length of the vector
        const int n = 64;

        // The prime modulus for the finite field
        const int prime = 1153;

        // A primitive nth root of unity
        const int a = 943;

        // Multiplicative inverse of n mod prime
        const int inverse = 1135;

        int powers[64];

        int mod(int x, int p)
        {
            return ((x % p) + p) % p;
        }

        void init_powers()
        {
            int p = 1;
            for (int i = 0; i < n; i++)
            {
                powers[i] = p;
                p = mod(p * a, prime);
            }
        }

        void fast_number_theoretic_transform_helper(int length, int input_offset, int stride, vector<int>& input, int output_offset, int output_stride, vector<int>& output, int sign)
        {
            if (length == 1)
            {
                output[output_offset] = input[input_offset];
            }
            else
            {
                int half = length / 2;
                fast_number_theoretic_transform_helper(half, input_offset, stride * 2, input, output_offset, output_stride, output, sign);
                fast_number_theoretic_transform_helper(half, input_offset + stride, stride * 2, input, output_offset + half * output_stride, output_stride, output, sign);
                for (int i = 0; i < half; i++)
                {
                    int a = output[output_offset + i * output_stride];
                    int b = output[output_offset + (i + half) * output_stride];
                    int c = mod(a + mod(powers[mod(-i * n / length * sign, n)] * b, prime), prime);
                    int d = mod(a + mod(powers[mod((half - i) * n / length * sign, n)] * b, prime), prime);
                    output[output_offset + i * output_stride] = c;
                    output[output_offset + (i + half) * output_stride] = d;
                }
            }
        }

        void fast_number_theoretic_transform(int length, int input_offset, int stride, vector<int>& input, int output_offset, int output_stride, vector<int>& output)
        {
            fast_number_theoretic_transform_helper(length, input_offset, stride, input, output_offset, output_stride, output, 1);
        }

        void inverse_fast_number_theoretic_transform(int length, int input_offset, int stride, vector<int>& input, int output_offset, int output_stride, vector<int>& output)
        {
            fast_number_theoretic_transform_helper(length, input_offset, stride, input, output_offset, output_stride, output, -1);
            for (int f = 0; f < length; f++)
            {
                // TODO - this only works for length == 64 because inverse is hard coded here
                output[output_offset + f * output_stride] = mod(output[output_offset + f * output_stride] * inverse, prime);
            }
        }

        Solution()
        {
            init_powers();
        }

        int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2)
        {
            vector<int> padded_image1(4096, 0);
            vector<int> padded_image2(4096, 0);
            vector<int> image1_rows(4096, 0);
            vector<int> image2_rows(4096, 0);
            vector<int> image1_rows_cols(4096, 0);
            vector<int> image2_rows_cols(4096, 0);
            vector<int> product(4096, 0);
            vector<int> product_rows(4096, 0);
            vector<int> product_rows_cols(4096, 0);

            for (int row = 0; row < img1.size(); row++)
            {
                for (int col = 0; col < img1[0].size(); col++)
                {
                    padded_image1[row * 64 + col] = img1[row][col];
                }
            }

            for (int row = 0; row < img2.size(); row++)
            {
                for (int col = 0; col < img2[0].size(); col++)
                {
                    padded_image2[row * 64 + col] = img2[img2.size() - row - 1][img2[0].size() - col - 1];
                }
            }

            for (int row = 0; row < 64; row++)
            {
                fast_number_theoretic_transform(64, row * 64, 1, padded_image1, row * 64, 1, image1_rows);
                fast_number_theoretic_transform(64, row * 64, 1, padded_image2, row * 64, 1, image2_rows);
            }
            for (int col = 0; col < 64; col++)
            {
                fast_number_theoretic_transform(64, col, 64, image1_rows, col, 64, image1_rows_cols);
                fast_number_theoretic_transform(64, col, 64, image2_rows, col, 64, image2_rows_cols);
            }
            for (int i = 0; i < 4096; i++)
            {
                product[i] = mod(image1_rows_cols[i] * image2_rows_cols[i], prime);
            }
            for (int row = 0; row < 64; row++)
            {
                inverse_fast_number_theoretic_transform(64, row * 64, 1, product, row * 64, 1, product_rows);
            }
            for (int col = 0; col < 64; col++)
            {
                inverse_fast_number_theoretic_transform(64, col, 64, product_rows, col, 64, product_rows_cols);
            }
            int answer = -1;
            for (int row = 0; row < 64; row++)
            {
                for (int col = 0; col < 64; col++)
                {
                    answer = max(answer, product_rows_cols[row * 64 + col]);
                }
            }

            return answer;
        }
    };
};

using namespace _LEET_IMAGE_OVERLAP;

int LEET_IMAGE_OVERLAP()
{
    Solution solution;
    vector<vector<int>> img1(3, vector<int>(3, 0));
    vector<vector<int>> img2(3, vector<int>(3, 0));

    img1[0][0] = 1; img1[0][1] = 1; img1[0][2] = 0;
    img1[1][0] = 0; img1[1][1] = 1; img1[1][2] = 0;
    img1[2][0] = 0; img1[2][1] = 1; img1[2][2] = 0;

    img2[0][0] = 0; img2[0][1] = 0; img2[0][2] = 0;
    img2[1][0] = 0; img2[1][1] = 1; img2[1][2] = 1;
    img2[2][0] = 0; img2[2][1] = 0; img2[2][2] = 1;

    cout << solution.largestOverlap(img1, img2) << endl;
    return 0;
}
