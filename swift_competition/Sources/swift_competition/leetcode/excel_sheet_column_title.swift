enum excel_sheet_column_title {}

extension excel_sheet_column_title {
  class Solution {
    func convertToTitle(_ n: Int) -> String {
      var result = [Character]()
      var num = n

      while num > 0 {
        var d = num % 26
        if d == 0 {
          d = 26
        }
        num -= d
        num /= 26
        let char = Character(UnicodeScalar(d + Int("A".unicodeScalars.first!.value) - 1)!)
        result.append(char)
      }

      return String(result.reversed())
    }
  }
  static func main() {
    print(Solution().convertToTitle(701))
  }
}
