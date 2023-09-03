enum maximal_network_rank {}

extension maximal_network_rank {
  class Solution {
    func maximalNetworkRank(_ n: Int, _ roads: [[Int]]) -> Int {
      if roads.count == 0 {
        return 0
      }
      var degree = [Int](repeating: 0, count: n)
      var roadSet = Set<library.IntPair>()
      for road in roads {
        let src = road[0]
        let dst = road[1]
        degree[src] = degree[src] + 1
        degree[dst] = degree[dst] + 1
        roadSet.insert(library.IntPair(a: src, b: dst))
        roadSet.insert(library.IntPair(a: dst, b: src))
      }
      var largestDegree = -1
      var secondLargestDegree = -1
      for i in 0..<n {
        if degree[i] > largestDegree {
          secondLargestDegree = largestDegree
          largestDegree = degree[i]
        } else if (degree[i] > secondLargestDegree) {
          secondLargestDegree = degree[i]
        }
      }
      var largestNodes : [Int] = [];
      var secondLargestNodes : [Int] = [];
      for i in 0..<n {
        if degree[i] == largestDegree {
          largestNodes.append(i)
        }
        if degree[i] == secondLargestDegree {
          secondLargestNodes.append(i)
        }
      }
      for largestNode in largestNodes {
        for secondLargestNode in secondLargestNodes {
          if largestNode != secondLargestNode {
            let road = library.IntPair(a: largestNode, b: secondLargestNode)
            if !roadSet.contains(road) {
              return largestDegree + secondLargestDegree
            }
          }
        }
      }
      return largestDegree + secondLargestDegree - 1
    }
  }
  static func main() {
    print(Solution().maximalNetworkRank(4, [[0, 1], [0, 3], [1, 2], [1, 3]]))
  }
}
