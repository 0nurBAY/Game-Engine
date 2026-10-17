import os
    

with open('5000NPC.txt', 'w') as fp:
    for i in range(5000):
        fp.write(f"IMPORT NPC2.ntt NPC{i+1} {200 + (i % 50) * 300} {200 + (i // 50) * 300}\n")