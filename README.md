Fonctionnalités :
-
Barre :
-
* Générer la barre puis afficher la barre
* La déplacer en utilisant le joystick
* Gérer le fait de pouvoir relancer la balle avec le pouvoir
du magnet.

Brique :
-

Chaque brique à une position sur le tableau de briques. Elle a aussi des coordonnées réelles sur l'écran. 
Création d'un type de structure brique avec position sur le tableau, id et état actuel.

Différents types de briques avec identifiants:
* 0 = Pas de brique
* 1 = Brique simple : met un coup à se casser
* 2 = Brique double : met deux coups à se casser, passe d'id 2 à 1 quand on la touche une fois
* 3 = Brique invincible : impossible de la casser
* 4 = Brique à bonus : contient un power-up lorsqu'elle est cassée
* 5 = Brique explosive : explose lorsqu'elle est touchée, détruisant les briques autour d'elle
* 6 = Brique toxique : inverse les commandes du joueur quand elle est touchée
* 7 = Brique Faveur : donne forcément un bonus lorsqu'elle est cassée, disparait vite

Tableau de briques :
-

A chaque début de niveau on génère un nouveau tableau aléatoirement.
Chaque brique à une chance différente d'apparaître.
Il faut faire en sorte que les briques invincibles n'empêchent pas la complétion du niveau
Le niveau se termine quand tout le tableau comporte seulement des briques invinciples

Vies : 
-
* On dispose de 3 vies de base
* Possibilité de gagner des vies bonus avec le powerup

Powerups :
-

Malus :
* 1 - Rétrécir la taille de la barre pendant 15 sec
* 2 - Inversion des contrôles pendant 15 secondes
* 3 - Perte de points
* 4 - Balle rapide : augmente la vitesse de la balle pendant 15 sec

Bonus :
* 5 - Agrandir la taille de la barre pendant 30 sec
* 6 - Barre magnétique : on garde la balle et on appuie pour la relancer
* 7 - Balles explosives : la balle explose lorsqu'elle touche une brique,
  ce qui fait un effet de zone
* 8 - Multiplicateur de points : pendant 30 secondes nous gagnons le double de pts
* 9 - Vie bonus (rare)
Score :
-

Un système de score avec un tableau de hi-score à la fin de la partie
On gagne des pts a chaque fois qu'on casse une brique, qu'on prend un powerup ou qu'on
finit un niveau.

