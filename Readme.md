## INTRODUCTION
ENSEA Shell est un TP qui permet d'exécuter des commandes Linux avec des fonctionnalités comme la gestion des arguments, les redirections d'entrée/sortie, et les pipes. Ce TP a pour but de nous apprendre à manipuler les processus, les appels système et la gestion de l'entrée/sortie en C.

## Fonctionnalités réalisées
Affichage du prompt initial et final : Le shell affiche un message de bienvenue au démarrage et un message d'au revoir lors de la sortie.

Exécution de commandes simples avec arguments : Permet d'exécuter des commandes avec des arguments,à l'exemple hostname -i.

Gestion des redirections d'entrée/sortie (<, >): Supporte les redirections d'entrée (<) et de sortie (>), à l'exemple du cas fait en TP ls > filelist.txt.

Gestion des pipes (|) : Supporte les pipes pour chaîner plusieurs commandes,à l' exemple ls | wc -l.

Affichage des informations de statut : Affiche le code de retour ou le signal de la commande exécutée ainsi que le temps d'exécution en millisecondes.

## Fichiers
main.c : Contient la boucle principale du shell et gère l'affichage des prompts et l'exécution des commandes.

enseash.h : Fichier d'en-tête contenant les déclarations de constantes, de macros, et de fonctions.

Q6.c : Gère l'exécution des commandes complexes avec arguments.

Q7.c : Gère les redirections d'entrée et de sortie (<, >).

Q8.c : Gère l'exécution des commandes avec pipes (|).

## Défis rencontrés
Lecture et gestion de l'entrée utilisateur
La lecture de l'entrée utilisateur à partir de la console, la suppression des caractères de nouvelle ligne, et la gestion des commandes de sortie (exit) ont posé des défis initiaux. 
la division des commandes en argments et les passer à 'lexecvp' pour l'exécution à deander une gestion de tokens précises