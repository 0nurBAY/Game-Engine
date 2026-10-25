import os
    

with open('50K_NPC.txt', 'w') as fp:
    for i in range(50000):
        fp.write(f"IMPORT NPC2.ntt NPC{i+1} {200 + (i % 500) * 300} {200 + (i // 500) * 300}\n")