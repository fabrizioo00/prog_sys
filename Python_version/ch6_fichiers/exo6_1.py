p, f, c, s, o = 2, 2, 1000, 60, 1024
print(f"Capacité: {p*f*c*s*o} octets")

position = (0 * f * c * s + 1 * c * s + 350 * s + 45) * o + 300
print(f"Position: {position}")

oct_n = 78000000
cyl = (oct_n // (s * o)) % c
sec = (oct_n // o) % s
pos = oct_n % o
plat = oct_n // (f * c * s * o)
face = (oct_n // (c * s * o)) % f
print(f"Plateau {plat}, Face {face}, Cylindre {cyl}, Secteur {sec}, Position {pos}")
