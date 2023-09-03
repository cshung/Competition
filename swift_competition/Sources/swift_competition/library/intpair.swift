extension library {
  struct IntPair: Hashable {
    var a: Int
    var b: Int

    func hash(into hasher: inout Hasher) {
      hasher.combine(a)
      hasher.combine(b)
    }

    static func == (left: IntPair, right: IntPair) -> Bool {
      return left.a == right.a && left.b == right.b
    }
  }
}
