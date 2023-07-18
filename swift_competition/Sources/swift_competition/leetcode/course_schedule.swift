enum course_schedule {}

extension course_schedule {
  class Solution {
    func hasCycle(_ i: Int, _ graph: [[Int]], _ visited: inout [Int]) -> Bool {
      visited[i] = 1
      for j in 0..<graph[i].count {
        let neighbor = graph[i][j]
        if visited[neighbor] == 0 {
          let neighborHasCycle = hasCycle(neighbor, graph, &visited)
          if neighborHasCycle {
            return true
          }
        } else if visited[neighbor] == 1 {
          return true
        }
      }
      visited[i] = 2
      return false
    }
    func canFinish(_ numCourses: Int, _ prerequisites: [[Int]]) -> Bool {
      var graph: [[Int]] = []
      var visited: [Int] = []
      for _ in 0..<numCourses {
        graph.append([])
        visited.append(0)
      }
      for pre in prerequisites {
        graph[pre[0]].append(pre[1])
      }
      for i in 0..<numCourses {
        if visited[i] == 0 {
          if hasCycle(i, graph, &visited) {
            return false
          }
        }
      }
      return true
    }
  }
  static func main() {
    let s = Solution()
    print(s.canFinish(2, [[1, 0]]))
  }
}
