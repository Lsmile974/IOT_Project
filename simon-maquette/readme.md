# Projet : Simon Game (Version Web & Ébauche d'Intégration avec ESP32)

## Description
Ce projet consiste en la création d'une version web du jeu **Simon**, où les joueurs doivent suivre une séquence de couleurs qui s'allument à l'écran et les reproduire. Le jeu devient de plus en plus difficile à mesure que la séquence s'allonge. L'interface web permet de jouer directement depuis le navigateur.

En plus de la version web, ce projet contient une ébauche de code pour intégrer le jeu à une carte **ESP32**. L'objectif est de permettre à la carte ESP32 de contrôler des LEDs physiques qui s'allument pour afficher la séquence de couleurs, tout en communiquant avec l'interface web pour définir la difficulté du jeu (nombre de couleurs, vitesse de la séquence, etc.).

## Objectifs

1. **Version Web :** 
   - Créer une interface de jeu Simon où les utilisateurs peuvent sélectionner la difficulté et jouer en ligne.
   - L'interface est composée de boutons colorés et de menus de sélection pour ajuster la difficulté du jeu.

2. **Intégration avec ESP32 :**
   - **ESP32** contrôle les LEDs physiques correspondant aux couleurs du jeu (rouge, vert, bleu, jaune).
   - La carte ESP32 récupère les choix de l'utilisateur via une page web et envoie les couleurs à afficher en temps réel sur les LEDs.
   - Une logique de séquence est mise en place sur l'ESP32 pour gérer les entrées utilisateur (boutons) et la gestion de la séquence.

## Technologies Utilisées

- **HTML / CSS / JavaScript** : Pour la partie front-end (jeu web).
- **ESP32 / Arduino IDE** : Pour l'intégration avec la carte ESP32, contrôle des LEDs et gestion des entrées utilisateurs (boutons).
- **SPIFFS (Système de fichiers SPI)** : Pour héberger la page web sur l'ESP32.
- **Wi-Fi** : Pour permettre à l'ESP32 d'héberger un serveur web et interagir avec l'utilisateur.


Pour lancé la version web, double cliqué sur le fichier index.hmtl depuis votre gestion de fichier. 