# http://rosalind.info/problems/lgis/

import six
import bisect

def lis(data):
  # This function computes the longest strictly increasing subsequence
  #
  # The problem is solved by maintaining the set of dominating feasible prefixes
  # when we scan through the array.
  # 
  # A prefix is simply a subsequence
  # A feasible prefix is a strictly increasing subsequence
  #
  # A prefix A dominates a prefix B if prefix B cannot form a longer feasible
  # sequence than prefix A does.
  #  
  # This definition allows us to quickly discard prefix B, but it doesn't help us
  # to determine if a prefix A dominates a prefix B
  #
  # Here is an operational criterion:
  # A prefix A dominates a prefix B if length(prefix A) >= length(prefix B) and
  # the end of prefix A less than the length of prefix B
  # 
  # One can prove these two criteria are equivalent 
  #
  # Now we begin the dynamic programming formulation:
  # 
  # The sub problem is the set of dominating feasible prefixes for the string with all 
  # but the last character.
  #
  # With that, we have three cases:
  # 1.) The last character is smaller than the end of all dominating feasible prefixes
  # 2.) The last character is larger than the end of all dominating feasible prefixes
  # 3.) Otherwise
  #
  # In case 1, we have a new length 1 dominating feasible prefix. If there was a length 1
  # dominating feasible prefix, then it is replaced, because its end is larger than the
  # current number.
  #
  # In case 2, consider the dominating feasible prefix situation as follow:
  # a
  # p q
  # 
  # Suppose the next number X is the largest amongst a, q, while we could have add X to
  # a to form [a X] as a feasible prefix, I claim it is being dominated by [p q]
  # This is because [a q] is being dominated by [p q] and X > q, so it make no sense to 
  # add [a X]. In fact, the only sensible new dominating feasible prefix is [p q X]
  # Note that we keep [p q] because [p q] has a shorter length than [p q X] and therefore
  # not being dominated
  #
  # In case 3, there must be a subset of dominating feasible prefixes that can be extended
  # using a reasoning similar to case 2, it only make sense to extend the longest one.
  # Suppose we happen to have a dominating feasible prefix with exactly the same length 
  # That is going to be dominated, because the new number added is smaller than the 
  # current number
  #
  # All three cases maintains two invariants.
  # 1.) If there is a dominating feasible prefix of length N > 1, then there is a dominating
  # feasile prefix of length N - 1 
  # 2.) A number belong as most one dominating feasible prefix
  #
  # These invariants allow us to represent these dominating feasible prefix compactly as follow
  # end_indices[i - 1] represents the index (int the data array) of the last element in the 
  # dominating feasible prefix of length i. This is possible because of 1.
  # parent[i] represents the index of the previous character
  end_indices = [0]
  parents = [-1] * len(data)
  for index in range(1, len(data)):    
    value = data[index]
    which_end = bisect.bisect_left([data[e] for e in end_indices], value)
    if which_end == 0:
      end_indices[0] = index
    elif which_end == len(end_indices):
      parents[index] = end_indices[-1]
      end_indices.append(index)
    else:
      parents[index] = end_indices[which_end - 1]
      end_indices[which_end] = index
    if False:
      print("After processing % s, the dominating feasible prefixes are:" % str(value))
      for end_index in end_indices:
        print(prefix(data, end_index, parents))
  return prefix(data, end_indices[-1], parents)

def prefix(data, end_index, parents):
  dominating_feasible_prefix = []
  while True:
    if end_index == -1:
      break
    dominating_feasible_prefix.append(data[end_index])
    end_index = parents[end_index]
  dominating_feasible_prefix.reverse()
  return dominating_feasible_prefix

def lgis(data):
  return (lis(data),[-e for e in lis([-f for f in data])])

def main():
  line = six.moves.input()
  line = six.moves.input()
  tokens = line.split(' ')
  numbers = [int(t) for t in tokens]  
  inc,dec = lgis(numbers)
  print(' '.join(str(n) for n in inc))
  print(' '.join(str(n) for n in dec))

if __name__ == "__main__":
  main()
