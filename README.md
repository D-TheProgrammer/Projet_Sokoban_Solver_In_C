# Projet_Sokoban_Solver_In_C
[French] Projet Solver de Sokoban en C   (D'abord ce sera le README en français, puis en anglais)  
[English] Image  Steganography Project in Python  (First it will be the French README then the English README After)

![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=black)
![AI](https://img.shields.io/badge/AI-Solver-orange)
![Game](https://img.shields.io/badge/Game-Puzzle-blue)
![Status](https://img.shields.io/badge/Status-Complete-success)

#### SOMMAIRE / SUMMARY
- [Présentation en francais / Presentation in French](#presentation-en-francais)
- [Démonstration en français /Demonstration in French](#démonstration)
- [Présentation en anglais / Presentation in English](#english-presentation)
- [Démonstration en anglais /Demonstration in English](#demonstration)

## [PRESENTATION EN FRANCAIS]
Le Sokoban est un jeu de réflexion créé en 1982 où un joueur, souvent appelé 'gardien d'entrepôt', doit déplacer des caisses vers des cibles en se déplaçant dans quatre directions : haut, droite, bas et gauche. Le joueur doit être prudent lorsqu'il pousse les caisses, car il ne peut pas les déplacer à travers les murs et n'a pas la force nécessaire pour pousser deux caisses en même temps. Ce casse-tête est très intéressant car le joueur peut se retrouver bloqué, incapable de résoudre la grille. De plus, le nombre de caisses (qui doit être le même que le nombre de cibles finales) peut être illimité, et ces caisses peuvent être disposées sur n'importe quelle cible sans distinction. Malgré sa simplicité apparente, le Sokoban est assez robuste en termes de complexité de résolution, nécessitant parfois des dizaines de milliers de déplacements pour qu'une intelligence artificielle trouve une solution.


### 1. <ins> [GENERAL] </ins>
Ce projet a été réalisé par D-TheProgrammer malheureusement parce que je suis français et que je cherche maintenant un emploi en France, tous les textes et commentaires du programme sont en français

Le but de ce projet est de réaliser le jeu Sokoban ainsi que son résolveur. Ce dossier comprend :

- Le programme principal se nomme  _"projet_sokoban_D-TheProgrammer.c"_  et est conçu pour fonctionner avec le fichier _"grille.txt"_ pour ses différentes fonctions. Certaines informations seront affichées sur le terminal à titre informatif et visuel.

- Un makefile permettant de compiler le code en utilisant la commande `make` dans le terminal et `make clean` pour nettoyer le dossier.

- Un fichier .txt nommé _"README"_ qui est le document que vous lisez actuellement.
  
### 2. <ins> [REGLE / RULES] </ins>

Le jeu Sokoban se déroule sur une grille, ici rectangulaire ou carrée, subdivisée en cellules qui peuvent ne rien contenir, contenir une boîte/caisse ('$'), une case finale ('.'), une caisse bien placée ('*'), ou le joueur ('@').

La règle du jeu est simple : vous contrôlez '@' et pouvez le déplacer avec les touches suivantes :
- Z : haut    
- Q : gauche  
- S : bas  
- D : droite

Votre objectif est de placer chaque caisse en les poussant sur leur emplacement final, de sorte qu'elles deviennent des '*'. Lorsque toutes les caisses sont bien placées sur une zone finale, vous gagnez. À tout moment, si vous êtes coincé, vous pouvez **redémarrer** la partie en appuyant sur **'R'**, et si vous souhaitez mettre **fin au jeu**, vous pouvez appuyer sur **'X'**! Bonne partie à vous et bonne chance!


### 3. <ins> [Création du jeu à partir d’un fichier .txt] </ins>

Le jeu du Sokoban se déroule sur un plateau de jeu ou une grille. Dans mon programme, au lieu d'avoir une grille statique définie
dans un simple tableau 2D, il est possible de créer son propre plateau de jeu en modifiant un fichier .txt nommé __"grille.txt"__ , cela permet aux joueurs de tester leur niveaux. Pour que le plateau de jeu soit considéré comme valide, ici, valide dans le sens “jouable” et non pas dans lesens "qui possède une solution", quelques conditions doivent être remplies :  
- Le plateau doit posséder un seul joueur représenté par '@'.  
- Il doit y avoir le même nombre de caisses ('$') que de cases finales ('.').  
- Les éléments ne doivent pas être entourés de murs ('#'), cela afin d'éviter que la partie commence sans aucun déplacement possible de base, ou qu'une caisse soit complètement inatteignable.  
- La dernière vérification effectuée est que la grille doit être un carré ou un rectangle et qu'elle doit être entourée, c'est-à-dire avoir des bords constitués de murs et avoir le même nombre d’éléments par ligne. permet d'empecher au joueur de sortir de la zone de jeu.

Voici un exemple de grille qui serait accepté ou refusée :

<div align="center">
  <img width="237" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/9ddc7ed0-4b81-4c01-a235-871ea19b97be">
  <img width="141" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/50eb6e0e-8940-4fc4-b0bd-6e69d2a2857b">

</div>
  

## [Démonstration]

### ÉTAPE 1: Le menu du principal du jeu   
<div align="center">
	<img width="626" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/bdbb73ee-7a25-44a8-a02e-bbff5d1ef445">
</div>

### ÉTAPE 2: Sous-menu si on décide de jouer manuellement  
<div align="center">
	<img width="503" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/4c488813-e568-41dd-86de-c525cb4cf7fa">
</div>

### ÉTAPE 3 : Déplacement du personnage et transformation de la caisse sur la case finale 
<div align="center">
	<img width="298" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/52b6429f-5da7-45ac-a096-56aa562f1092">
</div>

### ÉTAPE 4 : Utilisation du Solver (avec affichage des étapes) 
<div align="center">
	<img width="406" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/29237bc9-9add-4ec1-9745-a00026d55114">
 <img width="389" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/aee0809a-16aa-44ed-a1cf-2dbf2cd2e1ab">
</div>


___


## [ENGLISH PRESENTATION]
Sokoban is a puzzle game created in 1982 where a player, often referred to as the 'warehouse keeper', must move boxes to targets by moving in four directions: up, right, down, and left. The player must be careful when pushing boxes, as they cannot move them through walls and do not have the strength to push two boxes at the same time. This puzzle is very engaging as the player may become stuck, unable to solve the grid. Additionally, the number of boxes (which must match the number of final targets) can be unlimited, and these boxes can be placed on any target without distinction. Despite its apparent simplicity, Sokoban is quite robust in terms of resolution complexity, sometimes requiring tens of thousands of moves for an artificial intelligence to find a solution.


### 1. <ins> [GENERAL] </ins>

This project was realized by D-TheProgrammer unfortunatelly because i am french and  now searching for a job in France all the texte and comments in the program are in French .

The purpose of this project is to create the Sokoban game as well as its solver. This directory includes:

- The main program is named _"projet_sokoban_D-TheProgramme.c"_ and is designed to work with the _"grille.txt"_ file for its various functions. Some information will be displayed on the terminal for informational and visual purposes.

- A makefile for compiling the code using the "make" command in the terminal and "make clean" to clean the directory.

- A .txt file named _"README"_ which is the document you are currently reading.



### 2. <ins> [RULES] </ins>

The Sokoban game takes place on a grid, here rectangular or square, subdivided into cells which may contain nothing, a box ('$'), a final square ('.'), a well-placed box ('*'), or the player ('@').

The rule of the game is simple: you control '@' and can move it with the following keys:
- Z: up    
- Q: left  
- S: down  
- D: right

Your goal is to place each box by pushing it onto its final square, so that they become '*'. When all the boxes are well placed on a final square, you win. At any time, if you are stuck, you can **restart** the game by pressing **'R'**, and if you want to **end the game**, you can press **'X'**! Have a good game and good luck!


### 3. <ins> [Creating the game from a .txt file] </ins>

The Sokoban game takes place on a game board or grid. In my program, instead of having a static grid defined in a simple 2D array, it is possible to create your own game board by modifying a .txt file named __"grille.txt"__, allowing players to test their levels. For the game board to be considered valid, here, valid in the sense of "playable" and not in the sense of "having a solution", a few conditions must be met:
- The board must have only one player represented by '@'.
- There must be the same number of boxes ('$') as final squares ('.').
- Elements must not be surrounded by walls ('#'), to prevent the game from starting with no possible basic movement, or for a box to be completely unreachable.
- The last check performed is that the grid must be a square or rectangle and must be surrounded, meaning it must have borders consisting of walls and have the same number of elements per line, preventing the player from leaving the playing area.

Here is an example of a grid that would be rejected:
<div align="center">
  <img width="237" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/9ddc7ed0-4b81-4c01-a235-871ea19b97be">
  <img width="141" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/50eb6e0e-8940-4fc4-b0bd-6e69d2a2857b">

</div>


## [Demonstration]

### STEP 1: The main menu of the game  
<div align="center">
	<img width="626" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/bdbb73ee-7a25-44a8-a02e-bbff5d1ef445">
</div>

### STEP 2: Sub-menu if the player chooses to play manually  
<div align="center">
	<img width="503" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/4c488813-e568-41dd-86de-c525cb4cf7fa">
</div>
 
### STEP 3 : Character movement and transformation of the box onto the final square  
<div align="center">
	<img width="298" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/52b6429f-5da7-45ac-a096-56aa562f1092">
</div>

### STEP 4 : Use of the Solver (with display of the steps)
<div align="center">
	<img width="406" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/29237bc9-9add-4ec1-9745-a00026d55114">
 <img width="389" alt="image" src="https://github.com/D-TheProgrammer/Projet_Sokoban_Solver_In_C/assets/151149998/aee0809a-16aa-44ed-a1cf-2dbf2cd2e1ab">
</div>


