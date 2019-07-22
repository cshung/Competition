# http://rosalind.info/problems/revc/

def complement(n):
    if n == 'A':
        return 'T'
    elif n == 'C':
        return 'G'
    elif n == 'G':
        return 'C'
    elif n == 'T':
        return 'A'
        

dna = raw_input()
nt = len(dna)
answer = ""
for i in range(0, nt):
    j = nt - 1 - i
    answer += complement(dna[j])

print(answer)