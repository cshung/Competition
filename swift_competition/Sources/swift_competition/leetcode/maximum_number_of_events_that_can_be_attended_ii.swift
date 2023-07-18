enum maximum_number_of_events_that_can_be_attended_ii {}

extension maximum_number_of_events_that_can_be_attended_ii {
  class Solution {
    func maxValue(_ events: [[Int]], _ k: Int) -> Int {
      var events = events
      events.sort(by: { (a: [Int], b: [Int]) -> Bool in
        return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1])
      })
      var answers: [[Int]] = []
      var next : [Int] = []
      let n = events.count
      for i in 0..<n {
        var lo = i
        var hi = n
        while true {
          if hi - lo == 1 {
            next.append(hi)
            break
          }
          let mid = lo + (hi - lo) / 2
          if events[mid][0] <= events[i][1] {
            lo = mid
          } else {
            hi = mid
          }
        }
        answers.append([])
        for _ in 0..<k {
          answers[i].append(0)
        }
      }
      for i in 0..<k {
        answers[n - 1][i] = events[n - 1][2]
      }
      for i in (0..<(n - 1)).reversed() {
        let event = events[i]
        let event_value = event[2]
        for j in 0..<k {
          if j == 0 {
            answers[i][j] = max(event_value, answers[i + 1][j])
          } else {
            var take_answer = 0
            let take_start = next[i]
            if take_start == n {
              take_answer = event_value
            } else {
              take_answer = event_value + answers[take_start][j - 1]
            }
            let drop_answer = answers[i + 1][j]
            answers[i][j] = max(take_answer, drop_answer)
          }
        }
      }
      return answers[0][k-1]
    }
  }
  static func main() {
    let s = Solution()
    print(s.maxValue([[1,1,1],[2,2,2],[3,3,3],[4,4,4]], 3))
  }
}
