import re

# Reactions
numElements = 0
numSpecies = 0
elements = []
species = []

with open('chem.inp') as f:
    for line in f:
        if 'ELEMENTS' in line:
            break
    for line in f:
        line = line.strip()
        if 'END' in line:
            break
        else:
            line = re.split(r'\s+',line)
            for name in line:
                elements.append(name)
                numElements += 1
    
    for line in f:
        if 'SPECIES' in line:
            break
    for line in f: 
        line = line.strip()
        if 'END' in line:
            break
        else:
            line = re.split(r'\s+', line)
            for name in line:
                species.append(name)
                numSpecies += 1

with open('reactions','w+') as f:
    f.write('elements\n')
    f.write(f'{numElements}')
    f.write('\n(\n')
    for elem in elements:
        f.write(elem)
        f.write('\n')

    f.write(')\n;\n\nspecies\n')
    f.write(f'{numSpecies}')
    f.write('\n(\n')
    for spec in species:
        f.write(spec)
        f.write('\n')

    f.write(')\n;\n\nreactions\n{\n')
    f.write('\tun-named-reaction\n\t{\n\t\ttype\t\t\treversibleArrheniusReaction;\n')
    f.write('\t\treaction\t\t\"O + H2 = H + OH\";\n')
    f.write('\t\tA\t\t\t\t38.7;\n')
    f.write('\t\tbeta\t\t\t2.7;\n')
    f.write('\t\tTa\t\t\t\t3149.98;\n')
    f.write('\t}\n}')


# Thermodynamics
weightDict = {'C ':12, 'C':12, 'H':1, 'H ':1, 'N':14, 'N ':14, 'O':16, 'O ':16, 'HE':4, 'AR':40}
with open('therm.dat') as f, open('thermodynamics','w+') as w:
    while True:
        specie = ''
        coeffs = []
        elements = []
        elemNum = []
        for line in f:
            line = line.strip()
            if line[-1] == '1':
                elements.append(line[24:26])
                elemNum.append(int(line[27:29]))
                if line[29] != ' ':
                    elements.append(line[29])
                    elemNum.append(int(line[32:34]))
                if line[34] != ' ':
                    elements.append(line[34])
                    elemNum.append(int(line[37:39]))
                molWeight = 0.0
                for i,elem in enumerate(elements):
                    molWeight+=elemNum[i]*weightDict[elem]
                line = re.split(r'\s+', line)
                length = len(line)
                specie = line[0]
                Tcommon = line[-2]
                Thigh = line[-3]
                Tlow = line[-4]
                break
        for line in f:
            if line[-2] != '4':
                coeffs.append(line[0:15])
                coeffs.append(line[15:30])
                coeffs.append(line[30:45])
                coeffs.append(line[45:60])
                coeffs.append(line[60:75])
            else:   
                coeffs.append(line[0:15])
                coeffs.append(line[15:30])
                coeffs.append(line[30:45])
                coeffs.append(line[45:60])
                break
        if specie=='':
            break
        w.write(specie+'\n{\n\tspecie\n\t{\n\t\tmolWeight\t\t'+f'{molWeight}'+';\n\t}\n')
        w.write('\tthermodynamics\n\t{\n\t\tTlow\t\t\t'+ \
            f'{Tlow};\n\t\tThigh\t\t\t{Thigh};\n\t\tTcommon\t\t\t{Tcommon};\n')
        w.write('\t\thighCpCoeffs\t'+f'( {coeffs[0]} {coeffs[1]} {coeffs[2]} {coeffs[3]} {coeffs[4]}'+ \
            f' {coeffs[5]} {coeffs[6]} );\n')
        w.write('\t\tlowCpCoeffs\t\t'+f'( {coeffs[7]} {coeffs[8]} {coeffs[9]} {coeffs[10]} {coeffs[11]}'+ \
            f' {coeffs[12]} {coeffs[13]} );\n')
        w.write('\t}\n\ttransport\n\t{\n\t\tAs\t\t\t\t1.67212e-06;\n\t\tTs\t\t\t\t170.672;\n\t}\n')
        w.write('\telements\n\t{\n')
        for i,elem in enumerate(elements):
            w.write('\t\t'+elem + '\t\t\t\t' + f'{elemNum[i]};' + '\n')
        w.write('\t}\n}\n')
