//--------------------------------------------------
//------ PROJET SOKOBAN FEATURING SOLVER EN C ------
//--------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>


//----------------------------------
//------ FONCTIONS GENERALE --------
//----------------------------------

// Structure pour représenter une case dans la grille
typedef struct {
    char contenu;  // Contenu de la case (' ' pour un espace vide, '#' pour un mur, '.' pour la cible, '@' personnage, '*' caisse sur une case finle)
    char ancien_contenue;  // ce qu'il y avait avant dans la case
    int visiter;
} Case;

// Structure pour representer la grille du jeu
typedef struct {
    int ligne;
    int colonne;
    int nb_caisse; // nb de '$'
    int nb_case_finale; // nb de '.' 
    int nb_personnage; // nb de '@'
    int grille_valide;

    Case **cellule;
} Grille;


// Fonction pour initialiser la grille
Grille *initialisation_Grille(int ligne, int colonne) {
    Grille *plateau = (Grille *) malloc (sizeof(Grille));
    plateau->ligne = ligne;
    plateau->colonne = colonne;
    plateau->nb_caisse= 0;
    plateau->nb_case_finale= 0;
    plateau->nb_personnage= 0;
    plateau->grille_valide= 1; //on initialise a 1 pour pouvoir lire la grille et la preparer

    // Allocation  memoire pour chaque cellules de la grille
    plateau->cellule = (Case **)malloc(ligne * sizeof(Case *));
    for (int i = 0; i < ligne; i++) {
        plateau->cellule[i] = (Case *)malloc(colonne * sizeof(Case));
    }

    // Initialisation des cases en les mettant toutes a ' ' 
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            plateau->cellule[i][j].contenu = ' ';
            plateau->cellule[i][j].ancien_contenue = ' ';
            plateau->cellule[i][j].visiter = 1;
        }
    }
    return plateau;
}   



// Fonction pour creer une copie de la grille
Grille *copier_grille(Grille *grille_dorigine) {
    Grille *copie = initialisation_Grille(grille_dorigine->ligne, grille_dorigine->colonne);

    for (int i = 0; i < grille_dorigine->ligne; i++) {
        for (int j = 0; j < grille_dorigine->colonne; j++) {
            copie->cellule[i][j].contenu = grille_dorigine->cellule[i][j].contenu;
            copie->cellule[i][j].ancien_contenue = grille_dorigine->cellule[i][j].ancien_contenue;
            copie->cellule[i][j].visiter = grille_dorigine->cellule[i][j].visiter;
        }
    }
    copie->nb_caisse = grille_dorigine->nb_caisse;
    copie->nb_case_finale = grille_dorigine->nb_case_finale;
    copie->nb_personnage = grille_dorigine->nb_personnage;
    copie->grille_valide = grille_dorigine->grille_valide;

    return copie;
}


//-----------------------------------------------------------
//----------------FONCTION POUR JOUER MANUELLEMENT  ---------
//-----------------------------------------------------------
   

Grille *lire_grille(char *nom_fichier2, Grille *plateau){
    //Ouverture du fichier grille
    FILE * fichier;
    fichier = fopen(nom_fichier2,"r");
    if (fichier== NULL) {
        printf("Erreuur fopen\n");
        plateau->grille_valide = 0;
        return false;
    }

    int ligne_max = 100; // Nb max arbitraire
    int colonne_max = 100; 

    //Grille temporaire recevant le fichier .txt 
    char **grille_temporaire = (char **)malloc(ligne_max * sizeof(char *));
    for (int j = 0; j < ligne_max; j++) {
        grille_temporaire[j] = (char *)malloc((colonne_max + 1) * sizeof(char)); // +1 pour le caractere  nul
    }
    
    int nombre_de_lignes = 0;
    //Attribution des Valeur du fichier au tableau2D
    while (fgets(grille_temporaire[nombre_de_lignes], colonne_max + 1, fichier)) {
        grille_temporaire[nombre_de_lignes][strcspn(grille_temporaire[nombre_de_lignes], "\n")] = '\0';
        
        // Si la ligne n'est pas vide on incremente le compteur de lignes
        if (grille_temporaire[nombre_de_lignes][0] != '\0') {
            nombre_de_lignes++;
        }
    }
    
    // On verifie que chaque ligne a le meme nombre de caractere pour avoir un carré ou un rectangle 
    int longueur_premiere_ligne = strlen(grille_temporaire[0]);
    plateau = initialisation_Grille (nombre_de_lignes, longueur_premiere_ligne);

    for (int y = 1; y < nombre_de_lignes; y++) {
        // on compte pas les lignes vides
        if (grille_temporaire[y][0] == '\0') {
            continue;
        }

        int longueur_actuel = strlen(grille_temporaire[y]);

        int longueur_ligne = 0;
        for (int x = 0; x < longueur_actuel; x++) {
            longueur_ligne++;
        }

        if (longueur_ligne != longueur_premiere_ligne) {
            plateau->grille_valide = 0;
            longueur_premiere_ligne = 0;
            break;
        }
    }

    // Attribution des dimensions de la grille au plateau
    plateau->ligne= nombre_de_lignes; 
    plateau->colonne =  longueur_premiere_ligne; //car cest un carre ou rectangle donc la premiere ligne EST la longueur des autres 
    

    //Conversion des charactere en nombres
    for(int y=0; y< plateau->ligne  ; y++){
        for (int i = 0; i < plateau->colonne; i++)
        {
            if (grille_temporaire[y][i]== '#'){
                plateau->cellule[y][i].contenu= '#';
            }
            else if (grille_temporaire[y][i]== '$')
            {
                plateau->cellule[y][i].contenu= '$';
                plateau->nb_caisse += 1; 
            }
            else if (grille_temporaire[y][i]== '.')
            {
                plateau->cellule[y][i].contenu= '.';
                plateau->cellule[y][i].ancien_contenue= '.'; //car cest des cases fixes 
                plateau->nb_case_finale += 1;  
            }
            else if (grille_temporaire[y][i]== '@')
            {
                plateau->cellule[y][i].contenu= '@';
                plateau-> nb_personnage += 1; 
            }
            else if (grille_temporaire[y][i]== '*')
            {
                plateau->cellule[y][i].contenu= '*';
                plateau->cellule[y][i].ancien_contenue= '.';
            }
            else if (grille_temporaire[y][i]== ' ')
            {
                plateau->cellule[y][i].contenu= ' ';
                plateau->cellule[y][i].ancien_contenue= ' ';
            }
        } 
    }
    //Verification que le nombre d'objet dans la grille est correct 
    if ( plateau->nb_caisse != plateau->nb_case_finale || plateau->nb_personnage == 0 || plateau->nb_personnage > 1 )
    {
        plateau->grille_valide = 0;
    }

    //on verifie que le plateau soit composé dune ligne en haut et en bas de Mur ('#')
    for (int x = 0;   x < plateau->colonne   ; x++) {
        if (grille_temporaire[0][x] != '#' || grille_temporaire[nombre_de_lignes - 1][x] != '#') {
            plateau->grille_valide = 0;
            break;
        }
    }

    //et que les bords sur les coté soit des '#' donc le premier et dernier caractere des ligne intermediare
    for (int y = 1;  y < plateau->ligne - 1  ; y++) {
        if (grille_temporaire[y][0] != '#' || grille_temporaire[y][longueur_premiere_ligne - 1] != '#') {
            plateau->grille_valide = 0;
            break;
        }
    }

    //verification que les objet sont posé a des endroits correct
    //et non pas qu'une solution existe
    for (int y = 1; y < nombre_de_lignes - 1; y++) {
        for (int x = 1; x < longueur_premiere_ligne - 1; x++) {
            char element = grille_temporaire[y][x];

            // Vérification si l'objet est entouré par des murs
            if (element == '.' || element == '$' || element == '@') {
                if (grille_temporaire[y - 1][x] == '#' && grille_temporaire[y + 1][x] == '#' &&  // En haut et en dessous
                    grille_temporaire[y][x - 1] == '#' && grille_temporaire[y][x + 1] == '#') {  // a gauche et droite
                    plateau->grille_valide = 0;
                    printf("Position Impossible!\n");
                    break;
                }
            }
        }
    }
    fclose(fichier);
    return plateau;   
}


//Fonction pour afficher la grille
void afficher_grille(Grille *plateau) {
    if (plateau->grille_valide == 1) {
        for (int i = 0; i < plateau->ligne; i++) {
            for (int j = 0; j < plateau->colonne; j++) {

                //Creation de la couleur en fonction du contenu de la cellule
                switch (plateau->cellule[i][j].contenu) {
                    case '#':
                        printf("\033[41m \033[0m"); //Mur en rouge
                        break;
                    case '$':
                        printf("\033[48;5;208m$\033[0m");//Caisse en marron
                        break;
                    case '*':
                        printf("\033[42m*\033[0m"); // caisse bien place en Vert 
                        break;
                    case '.':
                        printf("\033[1;43m.\033[0m"); //Cible en jaune 
                        break;
                    case '@':
                        printf("\033[1m@\033[0m"); //Joueur en gras 
                        break;
                    default:
                        printf("%c", plateau->cellule[i][j].contenu);
                }
            }
            printf("\n");
        }
    }
    //si la grille n'est pas valide on affiche rien 
    else {
        printf("Grille Non Valide !!");
    }
}


//pour trouver la position du joueur
typedef struct {
    int pos_x;
    int pos_y;
} Position;

Position position_element(Grille *plateau , char element_rechercher) {
    Position ensemble_pos = {-1, -1};
    for (int i = 0; i < plateau->ligne; i++) {
        for (int j = 0; j < plateau->colonne; j++) {
            if (plateau->cellule[i][j].contenu == element_rechercher) {
                ensemble_pos.pos_x = j;
                ensemble_pos.pos_y = i;
                return ensemble_pos;
            }
        }
    }
    return ensemble_pos; //Retourne la position non modifié si cest pas bon 
}


//Fonction pour deplacer le personnage
void deplacer(Grille *plateau, int deplacement_x, int deplacement_y) {
    // Pour les positions du personnage
    int pos_x_Joueur = -1;
    int pos_y_Joueur = -1;

    Position position_joueur = position_element(plateau,'@');
    pos_x_Joueur= position_joueur.pos_x;
    pos_y_Joueur = position_joueur.pos_y;

    //oN verifie que le personnage a été trouvé
    if (pos_x_Joueur == -1 || pos_y_Joueur == -1) {
        printf("Position du personnage non trouvée\n");
        return;
    }

    // Nouvelle position après le deplacement
    int nouveau_pos_x = pos_x_Joueur + deplacement_x;
    int nouveau_pos_y = pos_y_Joueur + deplacement_y;

    //On verifie que la nouvelle position reste dans les limites de la grille
    if (nouveau_pos_x < 0 || nouveau_pos_x >= plateau->colonne || nouveau_pos_y < 0 || nouveau_pos_y >= plateau->ligne) {
        printf("Déplacement en dehors de la grille\n");
        return;
    }

    //Déplacement en fonction du contenu de la nouvelle position
    char nouveau_contenu_case = plateau->cellule[nouveau_pos_y][nouveau_pos_x].contenu;
    int nouveau_pos_x_boite=0;
    int nouveau_pos_y_boite=0;

    switch (nouveau_contenu_case) {
        case ' ':
        case '.':
            //Modification de lancienne case et remplacement de la case actuelle par ce qu'il y avait avant
            plateau->cellule[nouveau_pos_y][nouveau_pos_x].contenu = '@';
            plateau->cellule[pos_y_Joueur][pos_x_Joueur].contenu = plateau->cellule[pos_y_Joueur][pos_x_Joueur].ancien_contenue;  
            break;

        case '$':
        case '*':
            //Creation de la position après la caisse
            nouveau_pos_x_boite = nouveau_pos_x + deplacement_x;
            nouveau_pos_y_boite = nouveau_pos_y + deplacement_y;
            char nouveau_contenu_boite = plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].contenu;

            // On deplace la caisse si possible et on gere les cas en fonction des contenus de la case qui sera modifier 
            if (nouveau_contenu_boite == ' ' || nouveau_contenu_boite == '.') {
                if (nouveau_contenu_boite == '.') {
                    plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].contenu = '*'; //Si '.' devient '*'
                } else {
                    plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].contenu = '$'; //Si ' ' devient '$'
                }

                //enfin on deplace le personnage 
                plateau->cellule[nouveau_pos_y][nouveau_pos_x].contenu = '@';
                plateau->cellule[pos_y_Joueur][pos_x_Joueur].contenu = plateau->cellule[pos_y_Joueur][pos_x_Joueur].ancien_contenue;
            } 
            else {
                printf("Impossible de pousser la caisse\n");
                break;
            }
            break;

        default:
            printf("Déplacement impossible en [%d, %d]\n", nouveau_pos_x, nouveau_pos_y);
            break;
    }
}


//Fonction pour libérer la mémoire quon utilise par la grille
void freeGrille(Grille *plateau) {
    for (int i = 0; i < plateau->ligne; i++) {
        free(plateau->cellule[i]);
    }
    free(plateau->cellule);
    free(plateau);
}


//Fonction qui permettra de stopper le jeu
bool condition_victoire(Grille *plateau) {
    int nombre_points = 0;
    int nombre_caisse = 0;

    for (int i = 0; i < plateau->ligne; i++) {
        for (int j = 0; j < plateau->colonne; j++) {
            if (plateau->cellule[i][j].contenu == '.') {
                nombre_points++;
            }
            if (plateau->cellule[i][j].contenu == '$') {
                nombre_caisse++;
            }
        }
    }

    if (nombre_points == 0 && nombre_caisse == 0){
        return true; //autrement dit sil y a que des '*' sur la grille
    }
    else{
        return false;
    }
}


//Fonction pour remettre la grille comme au debut
void restaurer_grille(Grille *plateau, Grille *sauvegarde) {
    for (int i = 0; i < plateau->ligne; i++) {
        for (int j = 0; j < plateau->colonne; j++) {
            plateau->cellule[i][j].contenu = sauvegarde->cellule[i][j].contenu;
            plateau->cellule[i][j].ancien_contenue = sauvegarde->cellule[i][j].ancien_contenue;
            plateau->cellule[i][j].visiter = sauvegarde->cellule[i][j].visiter;
        }
    }
    plateau->nb_caisse = sauvegarde->nb_caisse;
    plateau->nb_case_finale = sauvegarde->nb_case_finale;
    plateau->nb_personnage = sauvegarde->nb_personnage;
    plateau->grille_valide = sauvegarde->grille_valide;
}


// Fonction principale pour jouer
void jouer(Grille *plateau) {
    //Creation d'une copie au cas ou le joueur se coince et voudrais recommencer 
    Grille *copie_plateau = copier_grille(plateau);

    //Boucle pour interpreter les touche du clavier
    while ( condition_victoire (plateau) == false) {
      
        afficher_grille(plateau);
        printf("Utilisez Z pour haut, D pour droite, S pour bas, Q pour gauche. Pour quitter, utilisez X\n");

        char mouvement;
        scanf(" %c", &mouvement);

        // Quitter le jeu si X
        if (mouvement == 'X' || mouvement == 'x') {
            printf("\n---------------------------------------------------");
            printf("\n------- FIN DE LA PARTIE !! AU REVOIR !! ----------");
            printf("\n---------------------------------------------------\n\n");
            return;
        }

        // Déplacer le personnage en fonction de l'entrée
        switch (mouvement) {
            case 'z':
            case 'Z':
                deplacer(plateau, 0, -1); //haut
                break;
            case 'd':
            case 'D':
                deplacer(plateau, 1, 0); //droite
                break;

            case 's':
            case 'S':
                deplacer(plateau, 0, 1); //bas
                break;

            case 'q':
            case 'Q':
                deplacer(plateau, -1, 0); //gauche
                break;

            case 'r':
            case 'R':
                printf("\n-------------------------------------------------------------------");
                printf("\n------- MISE A ZERO DE LA GRILLE !! LA PARTIE RECOMMENCE ----------");
                printf("\n-------------------------------------------------------------------\n\n");
                restaurer_grille(plateau,copie_plateau);
                break;

            default:
                //Si l'utilisateur n'entre pas une touche attendu 
                printf("\nEcrivez autre chose !! Utilisez Z, D, S, Q , R(recharger la grille) ou X(quitter)\n");
                break;
        }
    }

    if ( condition_victoire (plateau) == 1){ 
        afficher_grille(plateau); //Car ca arrete tout de suite donc on verrais pas la grille en etape finale
        printf("\n-------------------------------------------------------------------");
        printf("\n------- FELICITATION VOUS AVEZ REUSSI A FINIR LE SOKOBAN ----------");
        printf("\n-------------------------------------------------------------------\n");
    }
}



//----------------------------------------------------------
//------------  FONCTION POUR LE SOLVER UTILISER -----------
//----------------------------------------------------------


//structure qui contient la grille mais aussi les information sur la position  
//du joueurx a linstant T
typedef struct JeuInstant_T {
    Grille *plateau;
    int joueur_x;
    int joueur_y;
} JeuInstant_T;

//Creation dun noeud de pile classique 
typedef struct Noeud {
    JeuInstant_T *etape;
    struct Noeud *suivant;
} Noeud;

//Structure de la pile
typedef struct {
    Noeud *tete;
} Pile;


// Fonction pour creer une pile
Pile* creationPile() {
    Pile *ensemble_pile = (Pile*) malloc(sizeof(Pile));
    ensemble_pile->tete = NULL;
    return ensemble_pile;
}

// Fonction pour ajouter un élément à la pile
void ajout_noeud(Pile *ensemble_pile, JeuInstant_T *instantjeu) {
    Noeud *nouvelle_etape = (Noeud*) malloc(sizeof(Noeud));
    if (nouvelle_etape != NULL){
        nouvelle_etape->etape = instantjeu;
        nouvelle_etape->suivant = ensemble_pile->tete;
        ensemble_pile->tete = nouvelle_etape;
    }   
}


//Focntion qui retire des elements dune pile
JeuInstant_T* retirer_noued(Pile *ensemble_pile) {
    if (ensemble_pile->tete == NULL) {
        return NULL;
    }
    Noeud *noeud_premier_pile = ensemble_pile->tete;
    JeuInstant_T *etape = noeud_premier_pile->etape;
    ensemble_pile->tete = noeud_premier_pile->suivant;
    free(noeud_premier_pile);
    return etape;
}


//cette fonction permet de creer une nouvelle etape 
//Elle se base sur la fonction deplacer mais en plus simplifier et avec des difference comme la creation de letape

JeuInstant_T* creation_prochaine_etape(JeuInstant_T *tour_actuel, int directionX, int directionY) {
    //On cree la prochaine etape de la solution mais faut copier l'étape actuel
    JeuInstant_T *nouveau_tour = (JeuInstant_T *)malloc(sizeof(JeuInstant_T));
    nouveau_tour->plateau = copier_grille(tour_actuel->plateau);
    nouveau_tour->joueur_x = tour_actuel->joueur_x;
    nouveau_tour->joueur_y = tour_actuel->joueur_y;

    //Modification de la position du joueur
    nouveau_tour->joueur_x += directionX;
    nouveau_tour->joueur_y += directionY;

    //Deplacement en fonction du contenu de la nouvelle position
    char contenu_case_cible = nouveau_tour->plateau->cellule[nouveau_tour->joueur_y][nouveau_tour->joueur_x].contenu;

    if (contenu_case_cible == '$' || contenu_case_cible == '*') {
        int nouveau_pos_x_boite = nouveau_tour->joueur_x + directionX;
        int nouveau_pos_y_boite = nouveau_tour->joueur_y + directionY;
        
        // deplacer la caisse
        if (nouveau_tour->plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].ancien_contenue == '.') {
            nouveau_tour->plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].contenu = '*';
        } else {
            nouveau_tour->plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].contenu = '$';
        }
        // msie a jour  del'ancien contenu si la caisse quitte une cible
        if (contenu_case_cible == '*') {
            nouveau_tour->plateau->cellule[nouveau_tour->joueur_y][nouveau_tour->joueur_x].ancien_contenue = '.';
        }
    }

    // Mettre à jour la position du joueur dans la grille
    nouveau_tour->plateau->cellule[nouveau_tour->joueur_y][nouveau_tour->joueur_x].contenu = '@';
    if (tour_actuel->plateau->cellule[tour_actuel->joueur_y][tour_actuel->joueur_x].ancien_contenue == '.') {
        nouveau_tour->plateau->cellule[tour_actuel->joueur_y][tour_actuel->joueur_x].contenu = '.';
    } 
    else {
        nouveau_tour->plateau->cellule[tour_actuel->joueur_y][tour_actuel->joueur_x].contenu = ' ';
    }

    return nouveau_tour;
}


//Fonction pour verifier si un mouvement est faisable (se base aussi sur deplacer() )
bool testDeplacement(JeuInstant_T *tour_actuel,int directionX, int directionY) {
    int nouveau_pos_x = tour_actuel->joueur_x + directionX;
    int nouveau_pos_y = tour_actuel->joueur_y + directionY;

    //on test si la nouvelle position est dans un mur
    if (tour_actuel->plateau->cellule[nouveau_pos_y][nouveau_pos_x].contenu == '#') {
        return false;
    }

    //verification si le prochain mouvement pousse une caisse
    if (tour_actuel->plateau->cellule[nouveau_pos_y][nouveau_pos_x].contenu == '$' || tour_actuel->plateau->cellule[nouveau_pos_y][nouveau_pos_x].contenu == '*') {
        int nouveau_pos_x_boite = nouveau_pos_x + directionX;
        int nouveau_pos_y_boite = nouveau_pos_y + directionY;

        // Vérifier si la caisse est poussée dans un mur ou une autre caisse
        if (tour_actuel->plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].contenu == '#' || tour_actuel->plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].contenu == '$' || tour_actuel->plateau->cellule[nouveau_pos_y_boite][nouveau_pos_x_boite].contenu == '*') {
            return false;
        }
    }
    return true;
}



static int nombre_tentaive = 0;

//Fonction qui a partir des autres fonction creer le solver 
//on enregistre chaque etape en verifiant quels sont possible 
void solverJeu(JeuInstant_T *tour_initial , int afficher_toute_etape) {
    Pile *ensemble_pile = creationPile();
    ajout_noeud(ensemble_pile, tour_initial);

    //liste des etape faite et visite
    int liste_visite[100000] = {0}; //j'ai choisi cette taille pour les plus grand tableau 
    int compteur_etape_unique = 0;

    while (ensemble_pile->tete != NULL) {
        JeuInstant_T *tour_actuel = retirer_noued(ensemble_pile); 

        if (condition_victoire(tour_actuel->plateau)) {
            if (tour_actuel == NULL) {
                printf("Aucune solution trouvée.\n");
                return;
            }

            printf("Voici la solution pour la grille de Sokoban :\n");
            printf("Nombre de tentative : %d\n", nombre_tentaive);
            //pour afficher la grille
            afficher_grille(tour_actuel->plateau);
            break;
        }

        //pour chaque etape on attibuee un nuemro qui sera unique pour voir si elle se ressemble
        int numero_unique_etape = 0;
        for (int y = 0; y < tour_actuel->plateau->ligne; y++) {
            for (int x = 0; x < tour_actuel->plateau->colonne; x++) {
                numero_unique_etape = numero_unique_etape * 31 + tour_actuel->plateau->cellule[y][x].contenu; 
            }
        }
        //on verifie que le plateau actuel na pas ete visité 
        bool deja_visiter = false;
        for (int i = 0; i < compteur_etape_unique; i++) {
            if (liste_visite[i] == numero_unique_etape) {
                deja_visiter = true;
                break;
            }
        }
        if (deja_visiter == true) {
            continue;
        }

        //on attribue ce nnumero unique a la liste des etats verifier 
        liste_visite[compteur_etape_unique++] = numero_unique_etape;

        //on test les deplacement , cree une etape et on lajoute 
        int liste_deplacements[][2] = {{0, -1},{0, 1},{-1, 0}, {1, 0}};
        for (int direction = 0; direction < 4; direction++) {
            if (testDeplacement(tour_actuel, liste_deplacements[direction][0], liste_deplacements[direction][1])) {
                JeuInstant_T *tour_suivant = creation_prochaine_etape(tour_actuel, liste_deplacements[direction][0], liste_deplacements[direction][1] );
                ajout_noeud(ensemble_pile, tour_suivant);
                nombre_tentaive ++;
            }
        }

        if (afficher_toute_etape == 1) {
            afficher_grille(tour_actuel->plateau);
            printf("\n");
        }   
        free(tour_actuel);
    }
    free(ensemble_pile);
}



void regles(){

    printf("----------------------------------------------------------------------\n");
    printf("----------------------------   REGLES  -------------------------------\n");
    printf("----------------------------------------------------------------------\n");
    printf("Le jeu Sokoban se joue sur une grille ici rectangulaire ou carre \n");
    printf("subdivise en cellule qui peuvent ne rien contenir , contenir une boite/caisse '$' \n");
    printf("une case final '.' , une caisse bien place '*' ou le joueur '@'\n");
    printf("La regle du jeu est simple vous controleZ '@' et vous pouvez le deplacer avec :\n");
    printf("Z : haut , Q : gauche , S : bas et D : droite , \n");
    printf("Votre objectif est de placer chaque caisse en les poussant sur leur emplacement final\n");
    printf("dans le but que ces caisses deviennent des ' * ' symbolisant qu'elles sont bien place  \n");
    printf("Lorsque toutes les caisses sont bien placer sur une zone finale vous gagnez \n");
    printf("A tout moment lorsque vous etes coince vous pouvez redemarrer la partie en appuant sur R \n");
    printf("et si vous voulez vous pouvez mettre fin au jeu en appuyant sur X ! \n");
    printf("Bonne Partie A Vous et BONNE CHANCE !\n");
    printf("\n");
    printf("--------------------- !!! FIN REGLES !!! -------------------------------\n\n");

}


void DemarrerSokoban(Grille *plateau, int afficher_toute_etape) {
    printf("\n\n-----------------------------------------------------------------------------------------\n");
    printf("----- LE SOLVER EST EN TRAIN DE CHERCHER UNE SOLUTION !! LAISSEZ LE TRAVAILLER !!! ------\n");
    printf("-----------------------------------------------------------------------------------------\n");
    //initialiser l'état du jeu
    JeuInstant_T *tour_actuel = (JeuInstant_T *)malloc(sizeof(JeuInstant_T));
    tour_actuel->plateau = plateau;
    
    //trouver la position initiale du joueur
    Position pos_joueur = position_element(plateau,'@');
    tour_actuel->joueur_x = pos_joueur.pos_x;
    tour_actuel->joueur_y = pos_joueur.pos_y;

    //pour résoudre le Sokoban on lance aussi le timer 
    clock_t debut_timer = clock();

    //Appel de la fonction solver
    solverJeu(tour_actuel, afficher_toute_etape);

    clock_t fin_timer = clock();
    double temps_timer = ((double)(fin_timer - debut_timer)) / CLOCKS_PER_SEC;
    printf("Temps de resolution du solver : %.6f secondes\n", temps_timer);

    // Libération de la mémoire
    freeGrille(plateau);
    free(tour_actuel);
}





int main() {
    //Chemin vers le fichier de la grille
    char *nom_fichier = "./grille.txt";
    
    //Initialiser une grille vide
    Grille *plateau = initialisation_Grille(10, 10); //taille arbitraire, sera ajustée par lire_grille
    
    //Charger la grille à partir d'un fichier
    plateau = lire_grille(nom_fichier, plateau);

    // Vérifier si la grille est valide
    if (!plateau || !plateau->grille_valide) {
        printf("Grille invalide ou impossible de charger le fichier\n");
        return 1;
    }


    printf("\n------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------- !!! SOKOBAN !!! Par D-TheProgrammer ----------------------------------------------\n");
    printf("------------------------------------------------------------------------------------------------------------\n");    
    printf("\n");
    printf("\n");  

    //---------- MENU PRINCIPAL ----------------------
    int choixJoueurMenu=0;
    printf("Bienvenue dans le jeu du Sokoban !! Tout d'abord petite question\n");
    while (! (0<choixJoueurMenu && choixJoueurMenu <=4)){
        printf("Voulez -vous ?\n");
        printf("----------------------------------------------------------------------------------------------\n");
        printf("| 1 :  Jouer au jeux Normalement   |   2 :  Utiliser le Solver (sans afficher les etapes )   |\n");
        printf("---------------------------------------------------------------------------------------------------------------\n");
        printf("| 3 :  Utiliser le Solver (en affichant les etapes attention c'est peut etre long) |  4 :  Quitter le Jeux    |\n");
        printf("---------------------------------------------------------------------------------------------------------------\n");
        scanf("%d",&choixJoueurMenu);
    }
        
    if (choixJoueurMenu == 1 ){
        regles();
        printf("\n"); 
        printf("\n"); 

        printf("Ecrivez puis entrez n'importe quoi pour continuer : ");
        char ok;
        scanf(" %s",&ok);
        jouer(plateau);
        //libération de la mémoire
        freeGrille(plateau);
    }

    else if (choixJoueurMenu == 2 ){
        //pour lancer le solver 
        int afficher_toute_etape= 0;
        DemarrerSokoban(plateau , afficher_toute_etape);
    }

    else if (choixJoueurMenu == 3 ){
        int afficher_toute_etape= 1;
        DemarrerSokoban(plateau , afficher_toute_etape);
    }
    else{
        printf("Passez une bonne journee et n'hesitez pas a venir rejouer");
        return 0;
    }
    
    return 0;
}
