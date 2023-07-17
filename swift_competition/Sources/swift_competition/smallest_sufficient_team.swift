enum smallest_sufficient_team {}

extension smallest_sufficient_team {
  class Solution {
    func solve(
      _ own: Int, _ i: Int, _ target: Int, _ people: [Int], _ results: inout [[Int]],
      _ choices: inout [[Bool]]
    ) {
      let n = people.count
      let take_mask = own | people[i]
      if own == target {
        results[i][own] = 1
      } else if results[i][own] == 0 {
        if i == n - 1 {
          if take_mask == target {
            results[i][own] = 2
            choices[i][own] = true
          } else {
            results[i][own] = -1
          }
        } else {
          solve(take_mask, i + 1, target, people, &results, &choices)
          solve(own, i + 1, target, people, &results, &choices)
          let take_result = results[i + 1][take_mask]
          let leave_result = results[i + 1][own]
          if take_result == -1 {
            results[i][own] = -1
          } else {
            let take_count = results[i + 1][take_mask]
            if leave_result == -1 {
              results[i][own] = take_count + 1
              choices[i][own] = true
            } else {
              let leave_count = results[i + 1][own] - 1
              if leave_count < take_count {
                results[i][own] = leave_count + 1
                choices[i][own] = false
              } else {
                results[i][own] = take_count + 1
                choices[i][own] = true
              }
            }
          }
        }
      }
    }
    func smallestSufficientTeam(_ req_skills: [String], _ people: [[String]]) -> [Int] {
      var results: [[Int]] = []
      var choices: [[Bool]] = []
      var people_bits: [Int] = []
      var skills: [String: Int] = [:]
      var bit = 1
      var target = 0
      for skill in req_skills {
        skills[skill] = bit
        target = target + bit
        bit = bit * 2
      }
      for person in people {
        var bit = 0
        for skill in person {
          bit = bit + skills[skill]!
        }
        people_bits.append(bit)
        var empty_int: [Int] = []
        var empty_bool: [Bool] = []
        for _ in 0..<65536 {
          empty_int.append(0)
          empty_bool.append(false)
        }
        results.append(empty_int)
        choices.append(empty_bool)
      }
      solve(0, 0, target, people_bits, &results, &choices)
      var mask = 0
      var result: [Int] = []
      for i in 0..<people.count {
        if choices[i][mask] {
          mask = mask | people_bits[i]
          result.append(i)
        }
      }
      return result
    }
  }
  static func main() {
    let s = Solution()
    print(
      s.smallestSufficientTeam(
        ["java", "nodejs", "reactjs"], [["java"], ["nodejs"], ["nodejs", "reactjs"]]))
  }
}
