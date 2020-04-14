---
author:
- Nicolas Vadkerti
title: TP APPIDO
---

<https://github.com/SlaynPool/CR_APPIDO/>

Sujet
=====

Développer un objet connecté d'aide au stationnement dans les parkings
de Montpellier

Décrire le fonctionnement global du dispositif
==============================================

Notre objectif dans ce projet va etre "simple". Nous allons devoir
dévelloper un objet qui devra indiquer aux Montpelliérains qui
l'utiliserons où ils peuvent se stationner. L'objet devra donc
communiquer avec du coté utilisateur, pour pouvoir lui indiquer le
parking le plus proche, mais il devra aussi communiquer avec des
serveurs qui auront pour but de lui indiquer les places disponibles.
Pour l'utilisateur, on peut imaginer un ecran LCD ainsi qu'un joystick 5
boutons pour interagir avec le système et ainsi, definir les preferences
de recherche de l'utilisateur, et evidement lancer la recherche du
parking le plus approprié.\
L'objet devra aussi interagir avec differentes infrastructures
informatiques afin d'etre capable de ce repérer dans la ville, ainsi que
de connaitre les capacités des parkings. Pour le premier élément, nous
utiliserons une puce gps, qui sont devenue largement grand public et peu
chère. Pour le second, nous utiliserons les data disponibles via
<https://data.montpellier3m.fr/>. Il nous faudra donc une puce 3G/4G
pour faire des requetes sur le site de la ville via internet.\
On pourrai imaginer l'interface utilisateur comme ceci :\

![Interface utilisateur](UI.jpg){#fig:universe width="90%"}

Déterminer l'aspect matériel du dispositif
==========================================

Pour un tel objet, nous pouvons facilement imaginer que nous allons
l'utiliser dans notre voiture, et donc qu'un alume-cigare voir un port
USB pourra faire office d'alimentation. Comme nous allons utiliser un
ESP32 pour notre microcontroleur, nous nous efforcerons de trouvé des
modules GPS, ainsi que des modules 4G avec des bibliothèques existantes.
Le GPS que nous utiliserons sera le REYAX RY8253F qui s'utilise
facilement via un port serie. Pour la puce 4G, des shields pour arduino
existe donc supposera que nous pourrons utilser la connectivité de la
meme maniere que pour la puce Wifi de l'ESP32.\
Pour la partie Interface utilisateur, nous utiliserons un ecran LCD 16x2
et 5 boutons pour faire notre "joystick" Le montage resemblerait à celui
ci :\

![Montage](2.jpg){#fig:universe width="90%"}

\
Pour ce qui est du joystick, on pourrait utilisé un montage comme celui
ci, pour avoir : droite gauche, haut bas et le clique:\

![joystick](3.jpg){#fig:universe width="50%"}
