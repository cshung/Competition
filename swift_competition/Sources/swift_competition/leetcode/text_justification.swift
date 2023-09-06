enum text_justification {}

extension text_justification {
  class Solution {
    func fullJustify(_ words: [String], _ maxWidth: Int) -> [String] {
      var result: [String] = []
      var packedSize = -1
      var from = 0
      var line = Array(repeating: Character(" "), count: maxWidth)

      for i in 0...words.count {
        let isLastWord = i == words.count
        let additionalSize = isLastWord ? 0 : (words[i].count + 1)
        var l = 0

        if packedSize + additionalSize > maxWidth || isLastWord {
          // Emit a line with words coming from [from, i)
          let numWords = i - from

          if numWords == 1 || isLastWord {
            // Emit left justified
            for j in from..<i {
              // Emit all words
              for char in words[j] {
                line[l] = char
                l += 1
              }

              // Between each word, emit a space
              if j != i - 1 {
                line[l] = " "
                l += 1
              }
            }

            // Emit spaces until we reach the end
            for _ in l..<maxWidth {
              line[l] = " "
              l += 1
            }
          } else {
            // Emit full justified
            let numGaps = numWords - 1
            let numSpaces = maxWidth - packedSize + numGaps
            let smallGaps = numSpaces / numGaps
            let numBigGaps = numSpaces % numGaps

            for j in from..<i {
              // Emit all words
              for char in words[j] {
                line[l] = char
                l += 1
              }

              if j != i - 1 {
                // Between each word, emit a small gap
                for _ in 0..<smallGaps {
                  line[l] = " "
                  l += 1
                }

                // Emit one more space for big gaps
                if j - from < numBigGaps {
                  line[l] = " "
                  l += 1
                }
              }
            }
          }

          // Null terminate the line
          let lineString = String(line)
          result.append(lineString)

          // The next iteration will consider word (i + 1), so we account for the word i here
          from = i
          packedSize = additionalSize - 1
        } else {
          packedSize += additionalSize
        }
      }

      return result
    }
  }
  static func main() {
    print(Solution().fullJustify(["This", "is", "an", "example", "of", "text", "justification."], 16))
  }
}
