# BOUHMIDI_lab1 : Let there be light
## Sketch de l'architecture

![image](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/bf559541-59b8-40cd-966e-a6438853dfff)

Pour mettre en œuvre le 'LED chaser' décrit dans le Lab1, nous aurons besoin d'un environnement de développement Nios II, comprenant un processeur Nios II, un élément de mémoire pour stocker le programme, un bus Avalon pour la communication entre les différents composants, un module JTAG pour le débogage, ainsi que deux PIO, l'un dédié aux entrées pour les boutons et les switchs, et l'autre pour les sorties, représentant les LED. Ces composants permettront la création d'un système complet capable d'implémenter le chaser de LED avec la possibilité d'ajuster la vitesse à l'aide des boutons et des switchs, comme on peut le voir dans la figure qui suit :

## Architecture dans QSYS
Comme décrit précédemment, l'architecture comprend 2 PIO, un PIO d'entrée sur 6bits pour les 2 BP et les 4 SW, et un PIO de sortie pour les 8 LED : 
![image](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/add8abef-6065-4be8-86a7-4ec754b672d9)


## Chenillard

Avant de passer aux interruptions, nous implémentons le chenillard fonctionnant en permanence :

![IMG_4602](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/004a02d7-7741-4a00-90f4-10ebc6e0e8db)

## Chenillard avec interruptions par bouttons poussoir et control de vitesse avec switch
### Activation du chenillard avec interruption BP
L'appuis sur le bouton poussoir KEY0 génère une interruption qui permet de lancer le chenillard avec une vitesse par défaut, comme suit :

![IMG_4626](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/55f8f93f-3ccd-4e19-9a9e-b295645df32e)


### Augmentation de vitesse avec les SW

Le changement d'état des commutateurs SW0, SW1, SW2 et SW3 génère des interruptions qui imposent les vitesses respectives V+, V++, V+++ et V++++, avec lesquelles le chenillard fonctionnera. 
En appuyant sur KEY1, toutes les LED sont remises à zéro.

![IMG_4632](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/bcd201e0-191e-4b26-93f4-241272e5322a)


## Conclusion 

En conclusion, l'utilisation d'un unique PIO pour les boutons-poussoirs (BP) et les interrupteurs (SW) ainsi qu'une unique routine de service d'interruption (ISR) présente une limitation dans le fonctionnement. Cette configuration implique que la prise en compte d'une interruption dépend de la fin de l'exécution de la précédente. Cette contrainte temporelle peut entraîner des retards dans la gestion des interruptions, limitant ainsi la réactivité du système. 
Malgré cette limitation, le système parvient à fonctionner comme désiré. Les changements dans interrupteurs sont bien détectés, activant les différentes vitesses du chenillard en fonction des interrupteurs sélectionnés. En appuyant sur le bouton KEY1, le chenillard se met en marche avec la vitesse désirée. 
Bien que la réponse puisse être légèrement retardée, elle reste conforme aux attentes spécifiées.


