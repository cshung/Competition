enum number_of_black_blocks {}

extension number_of_black_blocks {
  class Solution {
    func countBlackBlocks(_ m: Int, _ n: Int, _ coordinates: [[Int]]) -> [Int] {
      var map = [Int: Int]()
      var answers = [(m - 1) * (n - 1), 0, 0, 0, 0]

      func updateAnswers(_ row: Int, _ col: Int) {
        let cell = row * n + col
        let a = map[cell] ?? 0
        let b = map[cell + 1] ?? 0
        let c = map[cell + n] ?? 0
        let d = map[cell + n + 1] ?? 0
        let count = a + b + c + d
        answers[count] -= 1
        answers[count + 1] += 1
      }

      for coordinate in coordinates {
        let row = coordinate[0]
        let col = coordinate[1]
        if row > 0 && col > 0 {
          updateAnswers(row - 1, col - 1)
        }
        if row > 0 && col < (n - 1) {
          updateAnswers(row - 1, col)
        }
        if row < (m - 1) && col > 0 {
          updateAnswers(row, col - 1)
        }
        if row < (m - 1) && col < (n - 1) {
          updateAnswers(row, col)
        }
        map[row * n + col] = 1
      }
      return answers
    }
  }
  static func main() {
    print(Solution().countBlackBlocks(3, 3, [[0, 0]]))
  }
}
