enum soup_servings {}

extension soup_servings {

  struct Pair: Hashable {
    var a: Int
    var b: Int

    func hash(into hasher: inout Hasher) {
      hasher.combine(a)
      hasher.combine(b)
    }

    static func == (left: Pair, right: Pair) -> Bool {
      return left.a == right.a && left.b == right.b
    }
  }

  class Solution {
    func soupServings(_ n: Int) -> Double {
      if n == 0 {
        return 0.5
      }
      if n > 4800 {
        return 1
      }
      var memo = [Pair: Double]()
      return soupServings(Pair(a: n, b: n), &memo)
    }
    func soupServings(_ state: Pair, _ memo: inout [Pair: Double]) -> Double {
      if let val = memo[state] {
        return val
      }
      var answer: Double = 0
      if state.a <= 100 {
        answer += 0.25
      } else {
        answer += 0.25 * soupServings(Pair(a: state.a - 100, b: state.b), &memo)
      }
      if state.a <= 75 {
        if state.b <= 25 {
          answer += 0.125
        } else {
          answer += 0.25
        }
      } else if state.b > 25 {
        answer += 0.25 * soupServings(Pair(a: state.a - 75, b: state.b - 25), &memo)
      }
      if state.a <= 50 {
        if state.b <= 50 {
          answer += 0.125
        } else {
          answer += 0.25
        }
      } else if state.b > 50 {
        answer += 0.25 * soupServings(Pair(a: state.a - 50, b: state.b - 50), &memo)
      }
      if state.a <= 25 {
        if state.b <= 75 {
          answer += 0.125
        } else {
          answer += 0.25
        }
      } else if state.b > 75 {
        answer += 0.25 * soupServings(Pair(a: state.a - 25, b: state.b - 75), &memo)
      }
      memo[state] = answer
      return answer
    }
  }
  static func main() {
    print(Solution().soupServings(50))
  }
}
