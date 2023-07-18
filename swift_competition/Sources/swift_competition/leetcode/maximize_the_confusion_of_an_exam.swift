enum maximize_the_confusion_of_an_exam {}

extension maximize_the_confusion_of_an_exam {
  class Solution {
    func maxConsecutiveAnswers(_ answerKey: String, _ k: Int) -> Int {
      let answers = Array(answerKey)
      let t = Array("T")[0]
      var tQueue: [Int] = []
      var fQueue: [Int] = []
      for _ in 0..<k {
        tQueue.append(0)
        fQueue.append(0)
      }
      var tEmpty = true
      var fEmpty = true
      var tHead = 0
      var tTail = 0
      var fHead = 0
      var fTail = 0
      var tStart = 0
      var fStart = 0
      var best = 1
      if answers[0] == t {
        fEmpty = false
        fQueue[fTail] = 0
        fTail += 1
        fTail = fTail % k
      } else {
        tEmpty = false
        tQueue[tTail] = 0
        tTail += 1
        tTail = tTail % k
      }
      for i in 1..<answers.count {
        if answers[i] == t {
          if best < i - tStart + 1 {
            best = i - tStart + 1
          }
          if !fEmpty && fTail == fHead {
            fStart = fQueue[fHead] + 1
            fHead = fHead + 1
            fHead = fHead % k
          }
          fEmpty = false
          fQueue[fTail] = i
          fTail += 1
          fTail = fTail % k
          if best < i - fStart + 1 {
            best = i - fStart + 1
          }
        } else {
          if !tEmpty && tTail == tHead {
            tStart = tQueue[tHead] + 1
            tHead = tHead + 1
            tHead = tHead % k
          }
          tEmpty = false
          tQueue[tTail] = i
          tTail += 1
          tTail = tTail % k
          if best < i - tStart + 1 {
            best = i - tStart + 1
          }
          if best < i - fStart + 1 {
            best = i - fStart + 1
          }
        }
      }
      return best
    }
  }

  static func main() {
    let s = Solution()
    print(s.maxConsecutiveAnswers("TTFTTTTTFT", 1))
  }
}
