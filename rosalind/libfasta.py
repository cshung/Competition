def readFasta(data):
  data.append(">")
  records = []
  label = None
  dna = ""
  for line in data:
    if line[0] == '>':
      if label != None:
        records.append((label, dna))
      label = line[1:] 
      dna = ""
    else:
      dna = dna + line
  return records
