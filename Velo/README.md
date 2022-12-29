<p align="center">
  <img src=velo.jpg height = "400">
  <img src=velo2.jpg height = "400">
</p>

# Projet Personnel : Lumière arrière de vélo 

C'est un projet qui me tient particulièrement à coeur et que je réalise sur mon temps libre. En effet habitant dans une ville où le vélo étant mon moyen de transport principal, il me faut un moyen d'éclairage de nuit fiable et efficace.
Suite au dysfonctionnement de mon ancienne lumière arrière j'ai décidé de me lancer dans le projet d'en faire une moi-même en réalisant à la fois le hardware et le software.

Les caractéristiques que la lumière doit avoir : 
- Puissance d'éclairage convenable afin d'être vu
- Les doivent être addressable afin de pouvoir faire varier la couleur ainsi que l'intensité
- Autonomie dépassant 4 heures d'autonomie en utilisation normale
- Etre rechargeable en USB-C
- Esthétique convenable
- Pouvoir résister aux éclaboussures/ la pluie
- Pouvoir résister au soleil


Hardware : 
- Boitier imprimé en 3D avec du filament ABS Sunlu noir
- 2 batteries 18650
- TP4056 USB-C
- Buck Converter lm2596
- Ring 5v ws2812b 12 LED
- Câble récuperé d'une alimentation d'ordinateur
- Intérrupteur à bascule ronds

Pour la partie software, je programme esp8266 en utilisant Arduino IDE. L'objectif est de pouvoir contrôler la lumière par Wi-Fi. Pour l'instant la seul fonctionnalité est le contrôle de l'intensité lumineuse de la lumière.
Mais par la suite je pense rajouter une fonctionnalité de clignotant, un suivi de vitesse, ainsi qu'un indicateur de batterie.

J'utilise pour ce projet du filament ABS Sunlu noir 1.75 mm, je l'ai choisi pour sa résistance à la chaleur, sa résistance, mais surtout pour sa capacité à être lissé à l'acétone pour l'aspect esthétique. En alternative je recommanderai l'utilisation de PETG.

Si j'ai le temps je mettrai en ligne un schéma du câblage. Ainsi que mes options de slicer.

---
# 06/10/22

Cela fait maintenant 2 semaines que j'utilise la lumière je n'ai pas de problème particulier avec. Le plus gros problème rencontré à été lors de l'assemblage est que mon boitier est très compact, en effet avec les câbles de récupération qui sont peu flexibles, il faut câbler à la bonne longueur tous les composants pour les faire rentrer.
Mon premier test d'autonomie, donne environ 10 heures d'éclairage en utilisation normale.
- Test consommation : 1.3A -> consommation max avec led RGB MAX
- Test consommation : 0.36A -> consommation led R 240
- Test consommation : 0.16A -> consommation led R 20

---
# 15/10/22
J'ai utilisé pour la première fois la lumière sous la pluie. Je n'ai pas eu de problème et malgré l'exposition à une forte pluie et l'humidité pedant plusieurs heures, la lumière fonctionne toujours correctement.

Un premier léger problème s'est révélé, un des rings de led s'est légèrement déboité du boitier. Mais j'ai pu la remettre en place. Pour la prochaine version il faudra peut être coller le ring ou revoir la conception 3D.

Jusque-là, je n'ai pas eu besoin de recharger la lumière, je l'ai utilisé environ 4h00.

---
# 18/11/22
La lampe est tombé en panne de batterie. Comme prévu j'ai bien pu la recharger via son port USB C.
En plus d'un mois d'utilisation, je n'ai pas rencontré de soucis importants. Hormis que système de fixation n'est pas optimal.

De plus il faudrait coller les ring LED, puisqu'un c'est "déclipsé", et tenait plus qu'avec les câbles. Cela est surement dû aux vibrations lors de mon parcours en vélo.

---
# 27/11/22
Afin de régler les problèmes de fixation, j'ai décidé d'adapter la lumière au système de fixation des lumières de mon vélo. J'en ai également profité pour faire un boiter bien plus volumineux qui me permettra de rentrer plus facilement les composants à l'intérieur. Le boitier reprend principalement la même architecture que les V1 et V2.



