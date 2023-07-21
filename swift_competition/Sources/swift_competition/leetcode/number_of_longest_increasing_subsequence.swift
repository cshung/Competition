enum number_of_longest_increasing_subsequence {}

extension number_of_longest_increasing_subsequence {

  class Solution {
    func find_count(_ n: Int, _ deck: inout [(Int, Int)]) -> Int {
      if deck[0].0 < n {
        return deck[deck.count - 1].1
      }
      var lo = 0
      var hi = deck.count - 1
      while true {
        if hi - lo == 1 {
          return deck[deck.count - 1].1 - deck[lo].1
        } else {
          let mid = lo + (hi - lo) / 2
          let mid_value = deck[mid].0
          if mid_value < n {
            hi = mid
          } else {
            lo = mid
          }
        }
      }
    }
    func findNumberOfLIS(_ nums: [Int]) -> Int {
      var decks: [[(Int, Int)]] = []
      for n in nums {
        if decks.count == 0 {
          decks.append([(n, 1)])
          continue
        }
        if decks[0][decks[0].count - 1].0 >= n {
          decks[0].append((n, decks[0].count + 1))
          continue
        }
        if decks[decks.count - 1][decks[decks.count - 1].count - 1].0 < n {
          decks.append([(n, find_count(n, &decks[decks.count - 1]))])
          continue
        }
        var lo = 0
        var hi = decks.count - 1
        while true {
          if hi - lo == 1 {
            break
          }
          let mid = lo + (hi - lo) / 2
          let mid_value = decks[mid][decks[mid].count - 1].0
          if mid_value < n {
            lo = mid
          } else {
            hi = mid
          }
        }
        decks[hi].append((n, decks[hi][decks[hi].count - 1].1 + find_count(n, &decks[hi - 1])))
      }
      return decks[decks.count - 1][decks[decks.count - 1].count - 1].1
    }
  }
  static func main() {
    print(Solution().findNumberOfLIS([1, 3, 5, 4, 7]))
  }
}
