# Projet Personnel : Lumière arrière de vélo 

C'est un projet qui me tient particulièrement à coeur et que je réalise sur mon temps libre. En effet habitant dans une ville où le vélo étant mon moyen de transport principal, il me faut un moyen d'éclairage de nuit fiable et efficace.
Suite à au dysfonctionnement de mon ancienne lumière arrière j'ai décidé de me lancer dans le projet d'en faire une moi-même en réalisant à la fois le hardware et le software.

Les caractéristiques que la lumière doit avoir : 
- Puissance d'éclairage convenable afin d'être vu
- Les doivent être addressable afin de pouvoir faire varier la couleur ainsi que l'intensité
- Autonomie dépassant aux 4 heures d'autonomie en utilisation normale
- Etre rechargeable en USB-C
- Esthétisme convenable
- Pouvoir résister aux éclaboussures/ la pluie
- Pouvoir résister au soleil


Hardware : 
- Boitier imprimé en 3D avec du filament ABS Sunlu noir
- 2 batteries 18650
- TP4056 USB-C
- Buck Converter lm2596
- Ring 5v ws2812b 12 LED
- Câble récuperé d'une alimentation d'ordinateur

Pour la partie software, je programme esp8266 en utilisant Arduino IDE. L'objectif est de pouvoir contrôler la lumière par Wi-Fi. Pour l'instant la seul fonctionnalité est le contrôle de l'intensité lumineuse de la lumière.
Mais par la suite je pense rajouter une fonctionnalité de clignotant, ainsi que de suivi de vitesse.

Pour la partie impression 3D, j'utilise comme un logiciel de conception 3D soit Shapr3D qui est disponible sur l'Ipad et que je recommande pour sa simplicité d'utilisation et sa fluidité, soit Fusion360 mais que j'utilise de moins en moins.
Comme imprimante 3D j'utilise la Voron 2.4, une imprimante 3D OpenSource très fiable et rapide mais à fabriquer soi-même. Ce que je recommande fortement si vous avez du temps pour la fabriquer (20h-60h) ainsi que les moyens de vous l'offrir (800€ - 1500€), à savoir que cette imprimante est uniquement vendue sous kit.

J'utilise pour ce projet du filament ABS Sunlu noir 1.75 mm, je l'ai choisi pour sa résistance à la chaleur, sa résistance, mais surtout pour sa capacité à être lissé à l'acétone pour l'aspect esthétique. En alternative je recommanderai l'utilisation de PETG.

Si j'ai le temps je mettrai en ligne un schéma du câblage. Ainsi que mes options de slicer.

---
# 06/10/22

Cela fait maintenant 2 semaines que j'utilise la lumière je n'ai pas de problème particulier avec. Le plus gros problème rencontré à été lors de l'assemblage est que mon boitier est très compact, en effet avec les câbles de récupération qui sont peu flexibles, il faut câbler à la bonne longueur tous les composants pour les faire rentrer.
Mon premier test d'autonomie, donne environ 10 heures d'éclairage en utilisation normale.
- Test consommation : 1.3A -> consommation max avec led RGB MAX
- Test consommation : 0.36A -> consommation led R 240
- Test consommation : 0.16A -> consommation led R 20

