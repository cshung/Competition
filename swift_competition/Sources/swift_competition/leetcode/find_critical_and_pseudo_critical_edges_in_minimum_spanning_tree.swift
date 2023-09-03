enum find_critical_and_pseudo_critical_edges_in_minimum_spanning_tree {}

extension find_critical_and_pseudo_critical_edges_in_minimum_spanning_tree {
  class Solution {
    func find(_ sets: inout [Int], _ i: Int) -> Int {
      if sets[i] < 0 {
        return i
      } else {
        sets[i] = find(&sets, sets[i])
        return sets[i]
      }
    }
    func union(_ sets: inout [Int], _ i: Int, _ j: Int) {
      let p = find(&sets, i)
      let q = find(&sets, j)
      let neg_size_p = sets[p]
      let neg_size_q = sets[q]
      if neg_size_p > neg_size_q {
        sets[p] = q
        sets[q] = neg_size_p + neg_size_q
      } else {
        sets[q] = p
        sets[p] = neg_size_p + neg_size_q
      }
    }
    func mst(_ n: Int, _ sorted_edges: inout [[Int]]) -> Int {
      var sets = [Int](repeating: -1, count: n)
      var cost = 0
      let e = sorted_edges.count
      for edgeIndex in 0..<e {
        let edge = sorted_edges[edgeIndex]
        let i = edge[0]
        let j = edge[1]
        let k = edge[2]
        if edge[4] & 4 != 0 {
          cost = cost + k
          union(&sets, i, j)
        }
      }
      for edgeIndex in 0..<e {
        let edge = sorted_edges[edgeIndex]
        let i = edge[0]
        let j = edge[1]
        let k = edge[2]
        if edge[4] & 2 == 0 {
          if find(&sets, i) != find(&sets, j) {
            sorted_edges[edgeIndex][4] |= 1
            cost = cost + k
            union(&sets, i, j)
          } else {
            sorted_edges[edgeIndex][4] &= ~1
          }
        }
      }
      return cost
    }
    func findCriticalAndPseudoCriticalEdges(_ n: Int, _ edges: [[Int]]) -> [[Int]] {
      let e = edges.count
      var sorted_edges: [[Int]] = []
      for i in 0..<e {
        let edge = edges[i]
        sorted_edges.append([edge[0], edge[1], edge[2], i, 0])
      }
      sorted_edges.sort {
        (a, b) -> Bool in
        a[2] < b[2]
      }
      let optimal = mst(n, &sorted_edges)
      var mst_edges: [Int] = []
      
      for edgeIndex in 0..<e {
        if sorted_edges[edgeIndex][4] & 1 == 1 {
          mst_edges.append(edgeIndex)
        }
      }
      var critical_edges: [Int] = []
      for m in mst_edges {
        sorted_edges[m][4] = 2
        let answer = mst(n, &sorted_edges)
        if answer != optimal {
          critical_edges.append(sorted_edges[m][3])
        }
        sorted_edges[m][4] = 0
      }
      var pseudo_edges: [Int] = []
      for m in 0..<e {
        sorted_edges[m][4] = 4
        let answer = mst(n, &sorted_edges)
        if answer == optimal {
          if !critical_edges.contains(sorted_edges[m][3]) {
            pseudo_edges.append(sorted_edges[m][3])
          }
        }
        sorted_edges[m][4] = 0
      }
      return [critical_edges, pseudo_edges]
    }
  }
  static func main() {
    print(
      Solution().findCriticalAndPseudoCriticalEdges(
        5, [[0, 1, 1], [1, 2, 1], [2, 3, 2], [0, 3, 2], [0, 4, 3], [3, 4, 3], [1, 4, 6]]))
  }
}
