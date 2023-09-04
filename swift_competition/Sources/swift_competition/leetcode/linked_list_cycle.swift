enum linked_list_cycle {}

extension linked_list_cycle {
  class Solution {
    func reorganizeString(_ s: String) -> String {
      let s = Array(s)
      let a = Array("a")[0].asciiValue!
      var freq = [Int](repeating: 0, count: 26)
      for c in s {
        let n = Int(c.asciiValue! - a)
        freq[n] += 1
      }
      var heap = library.BinaryHeap<IntPair>(26)
      for i in 0..<26 {
        heap.push(IntPair(a:-freq[i], b:i))
      }
      return ""
    }
  }
  static func main() {
    
    Solution().reorganizeString("abab")
  }
}
