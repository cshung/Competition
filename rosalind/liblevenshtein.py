def levenshtein(str1, str2, allowReplacement):
  m = len(str1)
  n = len(str2)
  #
  # cost[i][j] represents the minimum cost of editing str1[0, i) to str2[0, j)
  # choice[i][j] records the last editing operation used.
  #
  # There are three editing operation that we could use:
  # Insert a character to str1 (choice = 1)
  # Delete a character from str1 (choice = 2)
  # Replace a character (choice = 3)
  # Each of them has a cost of 1
  #  
  cost = [[0 for i in range(0, n + 1)] for j in range(0, m + 1)]   
  choice = [[-1 for i in range(0, n + 1)] for j in range(0, m + 1)] 
  #
  # If str2 is the empty string, the only reasonable editing operation is deleting character from str1
  #
  for i in range(0, m + 1):
    cost[i][0] = i
    choice[i][0] = 2
  #
  # If str1 is the empty string, the only reasonable editing operation is inserting character to str1
  #
  for j in range(0, n + 1):
    cost[0][j] = j
    choice[0][j] = 1
  #
  # We should not be reading this value, so we put a bad token here so that we can detect bad reads
  #
  choice[0][0] = 10086
  #
  # Otherwise we use this dynamic programming algorithm
  #
  for i in range(1, m + 1):
    for j in range(1, n + 1):
      c1 = str1[i - 1]
      c2 = str2[j - 1]
      if c1 == c2:
        # If the last character happens to match, there is no need to do any operation
        cost[i][j] = cost[i - 1][j - 1]
        choice[i][j] = 0
      else:
        # The last editing step could be inserting c2 to str1, before that we must have already made str1[0, i) == str2[0, j - 1)        
        insertion_cost = 1 + cost[i][j - 1]

        # The last editing step could be deleting c1 from str1, before that we must have already made str1[0, i - 1) == str2[0, j)
        deletion_cost = 1 + cost[i - 1][j]

        cost[i][j] = min(insertion_cost, deletion_cost)
        if allowReplacement:
          # The last editing step could be replacing c1->c2 in str1, before that we must have already made str1[0, i - 1) == str2[0, j - 1)
          replacementCost = 1 + cost[i - 1][j - 1]
          cost[i][j] = min(cost[i][j], replacementCost)
        if cost[i][j] == insertion_cost:
          choice[i][j] = 1
        elif cost[i][j] == deletion_cost:
          choice[i][j] = 2
        elif cost[i][j] == replacementCost:
          choice[i][j] = 3
        else:
          raise ValueError()
      if choice[i][j] == -1:
        raise ValueError()
  return (cost, choice)