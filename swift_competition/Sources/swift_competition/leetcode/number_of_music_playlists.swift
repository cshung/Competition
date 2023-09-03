enum number_of_music_playlists {}

extension number_of_music_playlists {
  class Solution {
    func numMusicPlaylists(_ n: Int, _ goal: Int, _ k: Int) -> Int {
      let height = n - k
      let width = goal - k
      var buffer1 = Array(repeating: 0, count: height)
      var buffer2 = Array(repeating: 0, count: height)
      buffer1[0] = 1
      for c in 1..<width {
        buffer2[0] = 1
        for r in 1..<min(c + 1, height) {
          buffer2[r] = (buffer1[r-1] + ((buffer1[r] * (r + 1)) % 1000000007)) % 1000000007
        }
        buffer1 = buffer2
        buffer2 = Array(repeating: 0, count: height)
      }
      var answer = buffer1[height - 1]
      for i in 1..<(n+1) {
        answer = (answer * i) % 1000000007
      }
      return answer
    }
  }
  static func main() {
    print(Solution().numMusicPlaylists(3, 3, 1))
  }
}
