# http://rosalind.info/problems/orf/

from sys import stdin
from libfasta import readFasta
from collections import deque
from libcode import code
from prot import prot
from revc import revc

class TrieNode:
    def __init__(self):
        self.children = {}
        self.failure = None
        self.pattern = None
        self.output = None

    def add(self, s):
        self.__add(s, s)

    def __add(self, s, t):
        if len(s) > 0:
            first = s[0]
            butfirst = s[1:]
            if first not in self.children:
                self.children[first] = TrieNode()
            self.children[first].__add(butfirst, t)
        else:
            self.pattern = t

def bfs(root):
    queue = deque()
    queue.append((None, ' ', root))
    while len(queue) > 0:
        (p, c, v) = queue.popleft()
        while p is not None:
            if p == root:
                break
            if c in p.failure.children:
                v.failure = p.failure.children[c]
                if v.failure.pattern is not None:
                    v.output = v.failure
                elif v.failure.output is not None:
                    v.output = v.failure.output
                break
            p = p.failure
        if v.failure is None:
            v.failure = root
        for child_key in v.children:
            queue.append((v, child_key, v.children[child_key]))

def aho_corasick(text, patterns):
    root = TrieNode()
    for pattern in patterns:
        root.add(pattern)
    bfs(root)
    result = []
    cursor = root
    i = 0
    while True:
        if i == len(text):
            break
        c = text[i]
        if c in cursor.children:
            cursor = cursor.children[c]
            i = i + 1
            if cursor.pattern is not None:
                result.append((i - len(cursor.pattern), cursor.pattern))
            output_cursor = cursor.output
            while output_cursor is not None:
                result.append((i - len(output_cursor.pattern), output_cursor.pattern))
                output_cursor = output_cursor.output
        else:
            if cursor == root:
                i = i + 1
            else:
                cursor = cursor.failure
    return result

def orf_strand(dna, answers):
  matches = aho_corasick(dna, ["ATG","TAG","TGA","TAA"])
  positions = [[],[],[]]
  for (position, codon) in matches:
    if codon == "ATG":
      positions[position % 3].append(position + 1)
    else:
      positions[position % 3].append(-position)
  for remainder in range(0, 3):
    starts = []
    for p in positions[remainder]:
      if p > 0:
        starts.append(p - 1)
      else:
        for start in starts:
          rna = dna[start:(-p)].replace("T","U")
          protein = prot(rna)
          if protein not in answers:
            answers[protein] = True
        starts = []

def orf(dna):
  answers = {}
  orf_strand(dna, answers)
  orf_strand(revc(dna), answers)
  return answers

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  answers = orf(records[0][1])
  for answer in answers:
    print(answer)

if __name__ == "__main__":
  main()
