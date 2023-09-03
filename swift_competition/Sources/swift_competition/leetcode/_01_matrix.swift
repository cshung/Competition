enum _01_matrix {}

extension _01_matrix {
  class Solution {
    func updateMatrix(_ mat: [[Int]]) -> [[Int]] {
      let m = mat.count
      let n = mat[0].count
      var queue = library.Deque<(library.IntPair, Int)>()
      var enqueued = Set<library.IntPair>()
      var result = [[Int]](repeating: [Int](repeating: 0, count: n), count: m)
      for r in 0..<m {
        for c in 0..<n {
          if mat[r][c] == 0 {
            let p = library.IntPair(a: r, b: c)
            let _ = queue.append((p, 0))
            enqueued.insert(p)
          }
        }
      }
      while !queue.isEmpty {
        let (src, cost) = queue.removeFirst()!
        let src_r = src.a
        let src_c = src.b
        result[src_r][src_c] = cost
        let drs = [-1, 0, 1, 0]
        let dcs = [0, -1, 0, 1]
        for move in 0..<4 {
          let dr = drs[move]
          let dc = dcs[move]
          let dst_r = src_r + dr
          let dst_c = src_c + dc
          if 0 <= dst_r && dst_r < m && 0 <= dst_c && dst_c < n {
            let dst = library.IntPair(a: dst_r, b: dst_c)
            if !enqueued.contains(dst) {
              enqueued.insert(dst)
              let _ = queue.append((dst, cost + 1))
            }
          }
        }
      }
      return result
    }
  }
  static func main() {
    print(Solution().updateMatrix([[0, 0, 0], [0, 1, 0], [0, 0, 0]]))
  }
}
