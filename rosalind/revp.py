# http://rosalind.info/problems/revp/

from sys import stdin
from libfasta import readFasta

def complement(n):
  if n == 'A':
    return 'T'
  elif n == 'C':
    return 'G'
  elif n == 'G':
    return 'C'
  elif n == 'T':
    return 'A'

#
# This function is the implementation of the modified Manacher's algorithm
# First, this function does not detect palindrome substrings, it detects 
# restriction sites (i.e. substring of the dna that equals to its reverse complement)
# Second, it only consider substrings of even length, because substrings of odd 
# length can never be equal to its reverse complement, in particular, the center will
# never match.
#
# With that convention in mind, center is defined to be the index of the character 
# after the actual center. For example:
#
# Index  : 012345 6789...
# String : TCAATG|CATGCGGGTCTATATGCAT
#             (     )
#
# We define the center to be 6 in this case, the half length is 3 and therefore
# The substring is [6-3, 6+3) = [3,9) 
#
# Note the beauty of the symmetry
#
def modified_manacher(dna):
  half_lengths = [0] * len(dna)
  rightmost_palindrome_center = 0
  rightmost_palindrome_half_length = 0
  # For each center, we have a loop to find its longest half length
  for center in range(1, len(dna)):
    # Leveraging the information we already knew
    # We can make some inferences:
    #
    # Names  :     R     Q       P p       q     r
    # String : . . . A A A | A A A a a a | a a a .
    #
    # Suppose the current rightmost palindrome has center p with length (r - p)
    # and we want to know the half length for q.
    #
    # We know (R, P] = [p, r), and we also knew the half length for Q + 1 (*), so  
    # we will have some hint about the half length of q.
    #
    # (*) Remember center is defined to be the character after the actual center
    # 
    # In particular, q's half length is at least min(half_length(Q + 1), r - q), it
    # could be longer. The rest is just simple arithmetic to compute it:
    # 
    # q - p = (P - Q)
    # Q + 1 = P - q + p + 1
    #       = 2p - q - 1 + 1
    #       = 2p - q
    #
    # Of course, this apply only if q in [p, r)
    #
    p = rightmost_palindrome_center
    r = rightmost_palindrome_center + rightmost_palindrome_half_length
    q = center
    if p <= q and q < r:
      half_length = min(half_lengths[2 * p - q], r - q)
    else:
      half_length = 0
    while True:
      next_right = center + half_length
      next_left = center - half_length - 1
      if next_left >= 0 and next_right < len(dna) and dna[next_left] == complement(dna[next_right]):
        half_length = half_length + 1
      else:
        break
    half_lengths[center] = half_length
    right = center + half_length
    if right > rightmost_palindrome_center + rightmost_palindrome_half_length:
      rightmost_palindrome_center = center
      rightmost_palindrome_half_length = half_length
  return half_lengths

def revp(dna):
  half_lengths = modified_manacher(dna)
  answer = []
  for i in range(0, len(half_lengths)):
    half_length = half_lengths[i]
    if half_length > 1:
      for j in range(2, min(half_length, 6) + 1):
        answer.append((i - j + 1, j *2))
  return answer

def main():
  data = []
  for line in stdin:
    data.append(line.strip())
  records = readFasta(data)
  answers = revp(records[0][1])
  for answer in answers:
    print("%d %d" % answer)

if __name__ == "__main__":
  main()
