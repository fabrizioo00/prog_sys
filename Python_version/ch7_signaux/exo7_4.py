n = int(input("n=? "))
tab = [int(input(f"tab[{i}]=? ")) for i in range(n)]

while True:
    try:
        i = int(input("i=? "))
        if i >= n or i < 0: raise IndexError
        print(tab[i])
        break
    except IndexError:
        print("Erreur de segmentation virtuelle (IndexError)")
