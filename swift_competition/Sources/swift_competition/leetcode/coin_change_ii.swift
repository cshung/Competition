enum coin_change_ii {}

extension coin_change_ii {
  class Solution {
    func changeHelper(
      _ amount: Int, _ coins: [Int], _ count: Int, _ memo: inout [library.IntPair: Int]
    ) -> Int {
      let key = library.IntPair(a: amount, b: count)
      if let result = memo[key] {
        return result
      } else if amount == 0 {
        return 1
      } else if count <= 0 {
        return 0
      } else {
        var ans = 0
        for i in stride(from: count - 1, through: 0, by: -1) {
          if amount >= coins[i] {
            ans += changeHelper(amount - coins[i], coins, i + 1, &memo)
          }
        }
        memo[key] = ans
        return ans
      }
    }

    func change(_ amount: Int, _ coins: [Int]) -> Int {
      var mutableCoins = coins
      mutableCoins.sort()
      var memo = [library.IntPair: Int]()
      return changeHelper(amount, mutableCoins, coins.count, &memo)
    }
  }
  static func main() {
    print(Solution().change(5, [1, 2, 5]))
  }
}
