/* Ex 6.1: Calculs géométrie disque dur
 * 2 plateaux, 4 faces, 1000 cylindres/face, 60 secteurs, 1024 octets/secteur
 */
#include <stdio.h>

int main(void)
{
    // Déclaration des constantes physiques du disque
    int plateaux = 2;
    int faces_par_plateau = 2;
    int cylindres = 1000;
    int secteurs = 60;
    int oct_sect = 1024;
    
    int faces = plateaux * faces_par_plateau;

    // Calcul des tailles des contenants 
    long taille_piste = (long)secteurs * oct_sect;               // 61 440 octets
    long taille_cylindre = (long)faces * taille_piste;           // 245 760 octets
    long total = (long)cylindres * taille_cylindre;              // 245 760 000 octets

    printf("a) Capacité = %ld octets = %.2f Mo = %.2f Go\n",
           total, total / 1e6, total / 1e9);

    /* b) octet 300 du secteur 45, cylindre 350, face 2 du 1er plateau
     * Indexation (base 0) : Face 2 du 1er plateau = face_idx 1.
     * Ordre physique : Cylindre -> Face -> Secteur
     */
    int cible_cyl = 350;
    int cible_face = 1;
    int cible_sect = 45;
    int cible_oct = 300;

    long pos = (cible_cyl * taille_cylindre) 
             + (cible_face * taille_piste) 
             + (cible_sect * oct_sect) 
             + cible_oct;
             
    printf("b) Position de l'octet = %ld\n", pos);

    // c) octet numéro 78000000 
    long n = 78000000;
    
    // On divise par le plus gros contenant (le cylindre)
    int cyl = n / taille_cylindre;
    long reste = n % taille_cylindre;
    
    // On divise le reste par la taille d'une face (une piste)
    int face_idx = reste / taille_piste;
    reste %= taille_piste;
    
    // On divise le reste par la taille d'un secteur
    int sect = reste / oct_sect;
    int posit = reste % oct_sect;
    
    printf("c) Octet %ld : cylindre %d, face %d, secteur %d, position %d\n",
           n, cyl, face_idx, sect, posit);
           
    return 0;
}