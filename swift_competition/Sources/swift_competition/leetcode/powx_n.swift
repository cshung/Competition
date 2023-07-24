enum powx_n {}

extension powx_n {
  class Solution {
    func myPow(_ x: Double, _ n: Int) -> Double {
      if n < 0 {
        return myPow(1 / x, -n)
      } else if n == 0 {
        return 1
      } else {
        let multiplier = (n % 2 == 1) ? x : 1
        let half = myPow(x, n / 2)
        return multiplier * half * half
      }
    }
  }
  static func main() {
    print(Solution().myPow(2, 10))
  }
}
