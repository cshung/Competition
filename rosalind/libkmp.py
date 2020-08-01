def kmp_overlap(left, right, right_shifts):
  (indexes, shift) = kmp_walk(left, right, right_shifts)
  return len(left) - shift

def kmp_search(text, pattern):
  shifts = build_kmp_shift(pattern)
  (indexes, shift) = kmp_walk(text, pattern, shifts)
  return indexes

def kmp_walk(text, pattern, shifts):
  answers = []
  text_cursor = 0
  pattern_cursor = 0
  shift = 0
  while True:
    if pattern_cursor == len(pattern):
      answers.append(text_cursor - len(pattern))
    if text_cursor == len(text):
      break
    if pattern_cursor == len(pattern):
      shift = shift + shifts[pattern_cursor - 1]
      pattern_cursor -= shifts[pattern_cursor - 1]
    elif text[text_cursor] == pattern[pattern_cursor]:
      text_cursor = text_cursor + 1
      pattern_cursor = pattern_cursor + 1
    elif (pattern_cursor == 0):
      shift = shift + 1
      text_cursor = text_cursor + 1
    else:
      shift = shift + shifts[pattern_cursor - 1]
      pattern_cursor -= shifts[pattern_cursor - 1]
  return (answers, shift)

def build_kmp_shift(pattern):
  #
  # To build a shift table we use the concepts of a z-box
  # A z-box is a proper substring such that it matches a prefix
  # and it cannot be extended further to the right and still
  # matches the prefix
  #
  # z[i] is the length of the z-box starting from i
  z = build_z(pattern)
  #
  # shifts[i] is the amount of shift possible if a mismatch happens
  # on the i + 1 character. Mismatching on the 0th character needs
  # to be special cased.
  #
  # Ideally, one would want to shift all the way so that the first
  # character of the pattern aligns with the mismatching character
  # The default value is these ideal shifts.
  #
  # z-boxes are getting in our way though, if a mismatch happens
  # right after a z-box, then we have to shift less, so that the
  # prefix aligns with the z-box, otherwise we might miss a match
  #
  # Just in case the mismatch happened within the z-box, there is
  # no need to align the pattern, because we knew it wouldn't match.
  #
  shifts = list(range(1, len(pattern) + 1))
  for i in range(1, len(pattern)):
    length = z[i]
    if i < shifts[i + length - 1]:
      #
      # After detecting a z-box, we need to update the shifts so that the z-box 
      # align with the prefix, this is done by shifting the pattern by i step
      # 
      # The comparation above is there to make sure if there are two z-box
      # terminate at exactly the same position, we take the shorter shift
      #
      shifts[i + length - 1] = i
  if False:
    for i in range(0, len(pattern)):
      print(' ' * (i + 1) + '*')
      print(pattern)
      print(' ' * shifts[i] + pattern)
  return shifts

def build_z(pattern):
  z = [0] * len(pattern)
  rightmost_zbox_left = 0
  rightmost_zbox_right = 0
  for i in range(1, len(pattern)):
    if i < rightmost_zbox_right:
      #
      # Denote l as rightmost_zbox_left, r as rightmost_zbox_right
      #
      # Being a z-box, we have:
      # pattern[l, r) = pattern[0, r - l)
      #
      # Since l < i < r, we have:
      # pattern[i, r) = pattern[i - l, r - l)
      #
      # We have already computed z[i - l], so we have
      # pattern[i - l, i - l + z[i - l]) = pattern[0, z[i - l])
      #
      # Therefore we can conclude the below, as a starting point before the search begins
      #
      length = min(z[i - rightmost_zbox_left], rightmost_zbox_right - i)
    else:
      length = 0
    #
    # Extend the z-box as much as possible
    #
    while True:
      if i + length < len(pattern) and pattern[i + length] == pattern[length]:
        length = length + 1
      else:
        break
    #
    # Record the z-box's length
    #
    z[i] = length
    if i + length > rightmost_zbox_right:
      rightmost_zbox_left = i
      rightmost_zbox_right = i + length
  return z
