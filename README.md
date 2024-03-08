# Projet_Sokoban_Solver_In_C
[French] Projet Solver de Sokoban en C  
[English] Image  Steganography Project in Python  
(D'abord le readme Francais puis l'anglais /French Readme First , English Readme After)

## [PRESENTATION]
Qu'est-ce que le Sokoban ? Il s'agit d'un jeu de réflexion créé en 1982, où un joueur, souvent appelé "gardien d'entrepôt", doit déplacer des caisses vers des cibles en se déplaçant dans quatre directions : haut, droite, bas et gauche. Le joueur doit être prudent lorsqu'il pousse les caisses, car il ne peut pas les déplacer à travers les murs et n'a pas la force nécessaire pour pousser deux caisses
en même temps. Ce casse-tête est donc très interessant, car le joueur peut se retrouver bloqué, incapable de résoudre la grille. De plus, il faut savoir que le nombre de caisses (qui doit être le même que le nombre de cibles finales) peut être illimité, et que ces caisses peuvent être disposées sur n'importe quelle cible sans distinction. Il est donc évident de dire qu'en termes de complexité de résolution, le Sokoban,
malgré sa simplicité apparente, est assez robuste. Pour certaines grilles, des dizaines de milliers de déplacements peuvent être nécessaires à une intelligence artificielle pour trouver une solution.



###  __[FRANCAIS]__ 
#### 1. <ins> [GENERAL] </ins>
Ce projet a été réalisé par D-TheProgrammer

Le but de ce projet est de réaliser le jeu Sokoban ainsi que son solver, 
ce dossier contient :

- Un projet d'intégration d'un programme de Sokoban interactif (et d'une intelligence qui resout le plateau) 
 en se basant sur une grille dans un fichier .txt.
 Ce programme se nomme "projet_sokoban_D-TheProgrammer.c" et est pensé pour fonctionner avec le fichier "grille.txt" 
 pour ses différentes fonctions
	(certaines informations seront affichées sur le terminal mais elles sont à titre informatif et visuel)

- Un makefile permettant de compiler le code en écrivant "make" dans le terminal  et "make clean" pour nettoyer le dossier

- Un fichier .txt nommé "README" qui est le document que vous lisez actuellement
  
#### 2. <ins> [REGLE / RULES] </ins>

Le jeu Sokoban se joue sur une grille ici rectangulaire ou carre subdivise en cellule qui peuvent ne rien contenir , contenir : 
- une boite/caisse '$'
- une case final '.'
- une caisse bien place '*'
- le joueur '@'

La regle du jeu est simple vous controlez '@' et vous pouvez le deplacer avec :
- Z : haut
- Q : gauche
- S : bas
- D : droite   

Votre objectif est de placer chaque caisse en les poussant sur leur emplacement final dans le but que ces caisses deviennent des ' * ' symbolisant qu'elles sont bien placé. Lorsque toutes les caisses sont bien placer sur une zone finale vous gagnez. A tout moment lorsque vous etes coince vous pouvez **redemarrer** la partie en appuant sur **R**  et si vous voulez vous pouvez mettre **fin au jeu** en appuyant sur **X** ! Bonne Partie A Vous et BONNE CHANCE !


#### 3. Création du jeu à partir d’un fichier .txt


Bien que cela puisse paraître évident, le jeu du Sokoban se déroule sur un plateau
de jeu ou une grille. Dans mon programme, au lieu d'avoir une grille statique définie
dans un simple tableau 2D, il est possible de créer son propre plateau de jeu en
modifiant un fichier .txt nommé "grille.txt" , cela permet d’avoir une certaine versatilité
et permet aux joueurs de s’amuser à tester leur niveaux. Pour que le plateau de jeu
soit considéré comme valide, ici, valide dans le sens “jouable” et non pas dans le
sens "qui possède une solution", quelques conditions doivent être remplies :
- Le plateau doit posséder un seul joueur représenté par '@'.
- Il doit y avoir le même nombre de caisses ('$') que de cases finales ('.').
- Les éléments ne doivent pas être entourés de murs ('#'), cela afin d'éviter que
la partie commence sans aucun déplacement possible de base, ou qu'une
caisse soit complètement inatteignable.
- La dernière vérification effectuée est que la grille doit être un carré ou un
rectangle et qu'elle doit être entourée, c'est-à-dire avoir des bords constitués
de murs et avoir le même nombre d’éléments par ligne.
permet d'empecher au joueur de sortir de la zone de jeu.

Voici un exemple de grille qui serait refusée :






### __[ENGLISH]__ 

  

## [Démonstration / Demonstration]

### ÉTAPE 1: Vérification de conditions clé pour considérer une grille comme valide
### STEP 1: 
<div align="center">
  <img width="237" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/9ddc7ed0-4b81-4c01-a235-871ea19b97be">
  <img width="141" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/50eb6e0e-8940-4fc4-b0bd-6e69d2a2857b">

</div>

### ÉTAPE 1 / STEP 1 
<div align="center">
	<img width="139" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/157b6dba-98e1-4092-b6d7-915d5098c9ab">

</div>

### ÉTAPE 2 / STEP 2 : Choisir les images / Choose the images
<div align="center">
	<img width="298" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/52b6429f-5da7-45ac-a096-56aa562f1092">
</div>

## ÉTAPE 3 / STEP 3 : Choisir le taux de stéganographie / Choose the steganography rate
<div align="center">
	<img width="366" alt="image" src="https://github.com/D-TheProgrammer/Image_Stegranography_python/assets/151149998/88c50756-ee19-4aaf-8ab6-49cb0c876431">
</div>

## ÉTAPE 4 / STEP 4 : Lancer la stéganographie et voir  / Choose the steganography rate
<div align="center">
	<img width="280" alt="image" src="https://github.com/D-TheProgrammer/Image_Stegranography_python/assets/151149998/f9d76057-cd8f-4891-83be-8fab602e953b">
	<img width="362" alt="image" src="https://github.com/D-TheProgrammer/Image_Stegranography_python/assets/151149998/c6d5134e-b8eb-4cc9-9dac-fc25f0c71ac4">
</div>

## ÉTAPE 5 / STEP 5 : Choisir Image pour déchiffrer / Choose the image to decrypt
<div align="center">
	<img width="257" alt="image" src="https://github.com/D-TheProgrammer/Image_Stegranography_python/assets/151149998/604f9704-69ff-454d-8de3-4e5bfad89664">
</div>

## ÉTAPE 6 / STEP 6 : Lancer et voir les résultats  / Start and see the Results
<div align="center">
	<img width="259" alt="image" src="https://github.com/D-TheProgrammer/Image_Stegranography_python/assets/151149998/b1707735-59b7-47c0-b923-095b1d638368">
</div>


