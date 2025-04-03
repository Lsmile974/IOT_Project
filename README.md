## Fonctionnement du Simon communautaire:

Les utilisateur (un compte pour chaque utilisateur) doivent pouvoir créer leurs propres niveaux de Simon et jouer à ceux de la communauté: 
- Pour la création ils doivent pouvoir faire leur propre suite de LED avec une vitesse d'execution personnalisable entre 60 et 120 (donc une à deux LED par seconde affichés) **PRIORITAIRE**
- Les points accordés par une map dépandent de la vitesse et de la longueur du niveau
- Les création doivent être stockés dans la db et être accessible pour le reste de la communauté **PRIORITAIRE**
- Lorsque l'on joue un niveaux, on doit pouvoir choisir entre trois modes (qui influencent les points gagnés), le mode normal, le mode aveugle (Seulement le buzzer, pas les LED), et le mode sourd (Seulement les LED, sans le buzzer)
- Bien sûr les points gagnés dans les différents niveaux doivent être stockés dans la db et afficher sur le compte de l'utilisateur (les points des map doivent s'ajouté pour former un total)
