enum asteroid_collision {}

extension asteroid_collision {

  class Solution {
    func sign(_ i: Int) -> Int {
      if i > 0 {
        return 1
      } else {
        return -1
      }
    }
    func asteroidCollision(_ asteroids: [Int]) -> [Int] {
      var result: [Int] = []
      for i in 0..<asteroids.count {
        let cur = asteroids[i]
        let cur_sign = sign(cur)
        let cur_abs = cur * cur_sign
        while true {
          if result.count == 0 {
            result.append(cur)
            break
          } else {
            let top = result[result.count - 1]
            let top_sign = sign(top)
            if top_sign == cur_sign || cur_sign == 1 {
              result.append(cur)
              break
            } else {
              let top_abs = top * top_sign
              if top_abs > cur_abs {
                break
              } else if top_abs < cur_abs {
                result.remove(at: result.count - 1)
              } else {
                result.remove(at: result.count - 1)
                break
              }
            }
          }
        }
      }
      return result
    }
  }
  static func main() {
    print(Solution().asteroidCollision([5,10,-5]))
  }
}
