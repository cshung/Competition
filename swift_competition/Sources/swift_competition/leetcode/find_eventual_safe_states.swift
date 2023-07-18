enum find_eventual_safe_states {}

extension find_eventual_safe_states {
  class Solution {
    func dfs(_ i: Int, _ graph: [[Int]], _ visited: inout [Int], _ safe: inout [Bool]) {
      visited[i] = 1
      for j in 0..<graph[i].count {
        let neighbor = graph[i][j]
        if visited[neighbor] == 0 {
          dfs(neighbor, graph, &visited, &safe)
          if !safe[neighbor] {
            safe[i] = false
          }
        } else if visited[neighbor] == 1 {
          safe[i] = false
        } else if !safe[neighbor] {
          safe[i] = false
        }
      }
      visited[i] = 2
    }
    func eventualSafeNodes(_ graph: [[Int]]) -> [Int] {
      let n = graph.count
      var visited: [Int] = []
      var safe: [Bool] = []
      for _ in 0..<n {
        visited.append(0)
        safe.append(true)
      }
      for i in 0..<n {
        if visited[i] == 0 {
          dfs(i, graph, &visited, &safe)
        }
      }
      var answer: [Int] = []
      for i in 0..<n {
        if safe[i] {
          answer.append(i)
        }
      }
      return answer
    }
  }
  static func main() {
    let s = Solution()
    print(s.eventualSafeNodes([[1, 2], [2, 3], [5], [0], [5], [], []]))
  }
}
