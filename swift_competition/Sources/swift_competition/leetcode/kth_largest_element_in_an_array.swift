enum kth_largest_element_in_an_array {}

extension kth_largest_element_in_an_array {
  class Solution {
    private func findKthSmallest(_ nums: inout [Int], _ start: Int, _ end: Int, _ k: Int) -> Int {
      if nums.count == 1 {
        return nums[0]
      }

      let pivotIndex = Int.random(in: start..<end)
      nums.swapAt(start, pivotIndex)

      let pivot = nums[start]
      let left = start
      let right = end

      var smallerEnd = left
      var smallerOrEqualEnd = left + 1
      var largerBegin = right

      while true {
        while smallerOrEqualEnd < nums.count && nums[smallerOrEqualEnd] <= pivot {
          if nums[smallerOrEqualEnd] < pivot {
            nums.swapAt(smallerEnd, smallerOrEqualEnd)
            smallerEnd += 1
          }
          smallerOrEqualEnd += 1
        }

        while largerBegin > 0 && nums[largerBegin - 1] > pivot {
          largerBegin -= 1
        }

        if smallerOrEqualEnd == largerBegin {
          break
        }

        if nums[largerBegin - 1] == pivot {
          nums.swapAt(smallerOrEqualEnd, largerBegin - 1)
          smallerOrEqualEnd += 1
          largerBegin -= 1
        } else {
          nums[smallerEnd] = nums[largerBegin - 1]
          nums[largerBegin - 1] = nums[smallerOrEqualEnd]
          nums[smallerOrEqualEnd] = pivot
          smallerEnd += 1
          smallerOrEqualEnd += 1
          largerBegin -= 1
        }
      }

      let smallPortionLength = smallerEnd - left

      if k < smallPortionLength {
        return findKthSmallest(&nums, left, smallerEnd, k)
      } else {
        var k = k - smallPortionLength
        let pivotPortionLength = smallerOrEqualEnd - smallerEnd

        if k < pivotPortionLength {
          return pivot
        } else {
          k -= pivotPortionLength
          return findKthSmallest(&nums, smallerOrEqualEnd, right, k)
        }
      }
    }

    func findKthLargest(_ nums: [Int], _ k: Int) -> Int {
      var copy = nums
      return findKthSmallest(&copy, 0, nums.count, nums.count - k)
    }
  }
  static func main() {
    print(Solution().findKthLargest([3, 2, 1, 5, 6, 4], 2))
  }
}
