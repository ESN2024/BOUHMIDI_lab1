# BOUHMIDI_lab1 : Let there be light
## Sketch de l'architecture

Pour mettre en œuvre le 'LED chaser' décrit dans le Lab1, nous aurons besoin d'un environnement de développement Nios II, comprenant un processeur Nios II, un élément de mémoire pour stocker le programme, un bus Avalon pour la communication entre les différents composants, un module JTAG pour le débogage, ainsi que deux PIO, l'un dédié aux entrées pour les boutons et les switchs, et l'autre pour les sorties, représentant les LED. Ces composants permettront la création d'un système complet capable d'implémenter le chaser de LED avec la possibilité d'ajuster la vitesse à l'aide des boutons et des switchs, comme on peut le voir dans la figure qui suit :

![image](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/bf559541-59b8-40cd-966e-a6438853dfff)
## Chenillard
![IMG_4602](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/004a02d7-7741-4a00-90f4-10ebc6e0e8db)
## Chenillard avec interruptions par bouttons poussoir et control de vitesse avec switch
### Activation du chenillard avec interruption BP
L'appuis sur le bouton poussoir KEY0 génère une interruption qui permet de lancer le chenillard avec une vitesse par défaut.
![IMG_4626](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/55f8f93f-3ccd-4e19-9a9e-b295645df32e)
### Augmentation de vitesse avec les SW
Le changement d'état des switchs SW0, SW1, SW2 et SW3 génère des interruptions permettant d'imposer la vitesse, respectivement V+, V++, V+++ et V++++ avec les quelles marchera de chenillard.
L'appuis sur le KEY1, remet toutes les LED à 0.
![IMG_4632](https://github.com/ESN2024/BOUHMIDI_lab1/assets/144927751/bcd201e0-191e-4b26-93f4-241272e5322a)





