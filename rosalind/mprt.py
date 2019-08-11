# http://rosalind.info/problems/mprt/

from sys import stdin
import urllib2

input = []
for line in stdin:
    input.append(line.strip())

data = []
for line in input:
    contents = urllib2.urlopen("http://www.uniprot.org/uniprot/" + line + ".fasta").read()
    lines = [i for i in contents.split("\n") if i]
    lines = lines[1:]
    lines = [">" + line] + lines
    data = data + lines
data.append('>')

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

for (label, dna) in records:
    state = 0
    start = 0
    answer = []
    for i in range(0, len(dna)):
        c = dna[i]
        if state == 0:
            if c == 'N':
                state = 1
                start = i
            elif c == 'P':
                state = 0
            elif c == 'S' or c == 'T':
                state = 0
            else:
                state = 0
        elif state == 1:
            if c == 'N':
                state = 2
            elif c == 'P':
                state = 0
            elif c == 'S' or c == 'T':
                state = 3
            else:
                state = 3
        elif state == 2:
            if c == 'N':
                state = 2
                start = i - 1
            elif c == 'P':
                state = 0
            elif c == 'S' or c == 'T':
                state = 4
            else:
                state = 3
        elif state == 3:
            if c == 'N':
                state = 1
                start = i
            elif c == 'P':
                state = 0
            elif c == 'S' or c == 'T':
                state = 5
            else:
                state = 0
        elif state == 4:
            if c == 'N':
                answer.append(start)
                start = i
                state = 1
            elif c == 'P':
                state = 0
            elif c == 'S' or c == 'T':
                answer.append(start)
                start = i - 2
                state = 5
            else:
                answer.append(start)
                state = 0
        elif state == 5:
            if c == 'N':
                answer.append(start)
                start = i                
                state = 1
            elif c == 'P':
                state = 0
            elif c == 'S' or c == 'T':
                answer.append(start)
                state = 0
            else:
                answer.append(start)
                state = 0
    if len(answer) > 0:
        print(label)
        s = ""
        for position in answer:
            s = s + str(position + 1) + " "
        print(s)

