enum letter_combinations_of_a_phone_number {}

extension letter_combinations_of_a_phone_number {

  class Solution {

    struct MyCollection: Sequence {
      let digits: String

      func makeIterator() -> MyIterator {
        return MyIterator(
          items: Array(digits), currentIndex: Array(repeating: 0, count: digits.count),
          done: digits.count == 0)
      }
    }

    struct MyIterator: IteratorProtocol {
      let items: [Character]
      var currentIndex: [Int]
      var done: Bool

      mutating func next() -> [Character]? {
        var map = [Character: [Character]]()
        map[Array("2")[0]] = Array("abc")
        map[Array("3")[0]] = Array("def")
        map[Array("4")[0]] = Array("ghi")
        map[Array("5")[0]] = Array("jkl")
        map[Array("6")[0]] = Array("mno")
        map[Array("7")[0]] = Array("pqrs")
        map[Array("8")[0]] = Array("tuv")
        map[Array("9")[0]] = Array("wxyz")
        if done {
          return nil
        }
        var answer: [Character] = []
        for i in 0..<items.count {
          let c = items[i]
          let a = map[c]![currentIndex[i]]
          answer.append(a)
        }
        var digit = items.count - 1
        while true {
          if currentIndex[digit] + 1 == map[items[digit]]!.count {
            currentIndex[digit] = 0
            digit = digit - 1
            if digit == -1 {
              done = true
              break
            }
          } else {
            currentIndex[digit] = currentIndex[digit] + 1
            break
          }
        }
        return answer
      }
    }

    func letterCombinations(_ digits: String) -> [String] {
      var answer: [String] = []
      for item in MyCollection(digits: digits) {
        answer.append(String(item))
      }
      return answer
    }
  }
  static func main() {
    print(Solution().letterCombinations("23"))
  }
}
