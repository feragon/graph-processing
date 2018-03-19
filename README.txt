Projet de modélisation
Par Roméo Florian et Webert Chris

== Prérequis:
https://cmake.org/download/
Pour Windows, la version "Windows win32-x86 ZIP" permet de se passer de l'installation
L'exécutable se trouve dans bin/cmake-gui.exe

== Compilation:
- Lancer CMake-GUI
- Cliquer sur "Browse Source..." et choisir le dossier du projet (celui où se trouve ce fichier README.txt)
- Cliquer sur "Browse build..." et choisir un dossier temporaire qui contiendra les fichiers compilés (ex: build)
- Cliquer sur "Configure" et choisir le bon compilateur, puis "Finish"
- Attendre que la configuration se fasse et cliquer sur "Generate"
- Fermer CMake-GUI
- Ouvrir le dossier build, la solution Visual Studio (ou autre selon le compilateur choisi) a été crée, l'ouvrir

== Lancer le projet:
Le programme va chercher les fichiers GPR dans son répertoire, qui sera donné lors de l'exécution.
Soit il faut lancer le programme une première fois, puis de copier les fichiers GPR dans le dossier donné avant de relancer le programme.
Soit il faut aller dans la configuration du projet "projet-modelisation" : clic droit sur "projet-modelisation" > "Propriétés" > "Propriétés de configuration" > "Débogage" et éditer la valeur de "Répertoire de travail"

- Clic droit sur le projet "projet-modelisation" > "Déboguer" > "Démarrer une nouvelle instance"

== Lancer les tests unitaires:
Les tests unitaires doivent être lancés dans le dossier source "tests/src" (voir configuration du projet au-dessus)

- Clic droit sur le projet "unittests" > "Définir comme projet de démarrage"
- Faire Ctrl+F5 ou cliquer sur le menu "Déboguer" dans la barre de menus, et cliquer sur "Exécuter sans débogage"


== Visualisation des graphes:
Le programme permet d'exporter des programmes au format DOT afin de les lire depuis GraphViz (http://www.graphviz.org/) ou tout autre programme compatible.
Pour les graphes les plus simples, il est possible de les visualiser sur un navigateur: https://dreampuf.github.io/GraphvizOnline/
Pour les graphes plus complexes, le logiciel Gephi https://gephi.org/ est très performant (mais n'affiche pas toutes les informations)
