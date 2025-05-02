# Ordonnanceur de Processus

Ce projet implémente un simulateur d'ordonnancement de processus avec plusieurs algorithmes classiques utilisés dans les systèmes d'exploitation.

## 🧠 Algorithmes Supportés

- **FCFS** (First Come First Serve)
- **SJF** (Shortest Job First)
- **RR** (Round Robin, avec quantum)
- **PRIO** (Priorité)

## 📁 Structure du Projet

- `main.c` : point d’entrée principal, interface en ligne de commande.
- `ordonnanceur.c` : fonctions communes et graphiques (ex. graphe de Gantt).
- `fcfs.c`, `sjf.c`, `rr.c`, `priority.c` : implémentations des algorithmes.
- `ordonnanceur.h` : définitions de structures et prototypes.
- `config.txt` : fichier d’entrée décrivant la liste des processus.
- `Makefile` : pour compiler le projet facilement.

## 🛠 Compilation

Utilisez simplement `make` :

```bash
make
```

Cela génère un exécutable nommé `ordonnanceur`.

## 🚀 Utilisation

Lancez le simulateur en ligne de commande :

```bash
./ordonnanceur config.txt
```

Ensuite, suivez le menu interactif pour choisir l’algorithme d’ordonnancement.

### Exemple de menu :

```
==========choisir votre type d'ordonnancement:============
	1- fcfs (first come first served)
	2- sjf (shortest job first)
	3- rr (round robin)
	4- priorite
	5- sortir
donner votre choix:
```

On vous demandera si vous souhaitez une **IHM Gantt interactive** (`y/n`), et pour Round Robin, de spécifier le quantum.

## 📝 Format du Fichier `config.txt`

Chaque ligne valide contient :

```
<nom> <arrival_time> <burst_time> <priorité>
```

Exemple :
```
P1 0 3 1
P2 2 6 2
P3 4 4 4
P4 6 5 3
P5 8 2 5
```

Commentaires sont autorisés avec `//`.

## 📊 Graphe de Gantt

Affichage console avec ou sans interaction utilisateur, selon le mode choisi.
