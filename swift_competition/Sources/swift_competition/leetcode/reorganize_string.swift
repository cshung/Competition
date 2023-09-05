enum reorganize_string {}

extension reorganize_string {
  class Solution {
    func toChar(_ d: Int) -> Character {
      Character(UnicodeScalar(d)!)
    }    
    func reorganizeString(_ s: String) -> String {
      let s = Array(s)
      let a = Int(Array("a")[0].asciiValue!)
      var freq = [Int](repeating: 0, count: 26)
      for c in s {
        let n = Int(c.asciiValue!) - a
        freq[n] += 1
      }
      let heap = library.BinaryHeap<library.IntPair>(26)
      for i in 0..<26 {
        if freq[i] != 0 {
          heap.push(library.IntPair(a: -freq[i], b: i))
        }
      }
      var answer: [Character] = []
      var last = heap.pop()
      answer.append(toChar(last.b + a))
      while heap.count() > 0 {
        let now = heap.pop()
        if last.a + 1 < 0 {
          heap.push(library.IntPair(a: last.a + 1, b: last.b))
        }
        last = now
        answer.append(toChar(last.b + a))
      }
      if answer.count == s.count {
        return String(answer)
      } else {
        return ""
      }
    }
  }
  static func main() {

    print(Solution().reorganizeString("aab"))
  }
}
