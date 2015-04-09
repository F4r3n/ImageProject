#include "window.h"
#include <QApplication>

/*! \mainpage Image Project
 *
 * \section intro_sec Introduction
 *
 * Ce logiciel a pour but d'implémenter des algorithmes sur une vidéo découpée en image.
 * Deux Algorithms sont utilisés qui seront appelé algorithme 1 et algorithme 2.
 *
 *\subsection step1 Algorithme 1
 * Cet Algorithm fait la moyenne d'un canal dans une frame donnée puis ce ci se fait sur toutes les frames de la vidéo, il doit être enclenché en appuyant sur le radio bouton.
 *
 * \subsection step2 Algorithme 2
 * Cet algorithme découpe une image en carré de taille variable, puis amplifie les données pour chaque carré et fait une moyenne totale. Cet algorithme est lancé automatiquement.
 *
 *
 * \section util_sec Utilisation
 *
 * \subsection  s Conversion vidéo en images
 * Dans un premier temps, avant de lancer une analyse vous devez transformer une vidéo en images
 *Ceci se fait en allant dans le menu "fichier" puis dans "create images".
 *Les images peuvent être créé depuis une webcam en appuyant sur le bouton webcam se situant en bas.
 *
 * \subsection  s2 Chargement des images
 * Après la conversion des images, leur chargement dans l'application est possible via le menu "fichier", puis "load".
 *Les images seront alors chargées dans l'application si il n'y a aucun problème.
 *
 *\subsection step3 Choix de l'espace de couleur
 * L'espace de couleur peut être choisi en allant sur la combo box puis en validant notre sélection.
 * Le mode RGB est automatiquement enclenché.
 *
 * \subsection step4 Rectangle
 * Un carré doit être dessiné, les coordonnées de celui-ci donnera la partie de l'image à analyser.
 * Un carré est automatiquement dessiné si l'option auto rect n'est pas cochée.
 *
 * \subsection step5 Lancer l'analyse
 * L'analyse se lance en appuyant sur le bouton analyze.
 *
 */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.show();
    return a.exec();
}
