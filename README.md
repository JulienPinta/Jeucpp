Leo Le mangeur de nuage

2017 - 2017 Pinta Julien, Daugan Valentin  ALL RIGHTS RESERVED

/Bibliothèque			Contient toutes les fonctions .cpp et .h utiles pour le lancement du jeu
/JeuVersion0			Coquille vide à partir duquel on lance le jeu
/pugixml				Utile pour utiliser du xml
/UnitTests				Contient des tests unitaires


Le jeu à besoin de SFML-2.4.2 ainsi que photon pour fonctionner.
Télécharger les bibliothèques en ligne. (lien pour la bibliothèque Photon : https://www.photonengine.com/sdks#realtimewindows)

Nous supposons ici que les bibliothèques se situent (une fois désarchivées) dans C:/Software, on a donc :
C:/Software/SFML-2.4.2 et C:/Photon-Windows-Sdk_v4-1-6-0 


à importer : 
Projet Bibliothèque, Propriétés, C/C++ , autres répertoires includes : 
C:\Software\Photon-Windows-Sdk_v4-1-6-0;C:\Software\SFML-2.4.2\include;C:\Software\Photon-Windows-Sdk_v4-1-6-0;C:\Software\Photon-Windows-Sdk_v4-1-6-0\LoadBalancing-cpp\inc;C:\Software\Photon-Windows-Sdk_v4-1-6-0\Common-cpp\inc;C:\Software\Photon-Windows-Sdk_v4-1-6-0\Photon-cpp\inc;

Projet JeuVersion0, Propriétés, C/C++, autres répertoires includes :
C:\Software\SFML-2.4.2\include;C:\Software\Photon-Windows-Sdk_v4-1-6-0;

Projet JeuVersion0, Propriétés, Editeur de liens, général , Répertoire de bibliothèques supplémentaires :
C:\Software\SFML-2.4.2\lib;C:\Software\Photon-Windows-Sdk_v4-1-6-0\Common-cpp;C:\Software\Photon-Windows-Sdk_v4-1-6-0\Common-cpp\lib;C:\Software\Photon-Windows-Sdk_v4-1-6-0\LoadBalancing-cpp;C:\Software\Photon-Windows-Sdk_v4-1-6-0\LoadBalancing-cpp\lib;C:\Software\Photon-Windows-Sdk_v4-1-6-0\Photon-cpp;C:\Software\Photon-Windows-Sdk_v4-1-6-0\Photon-cpp\lib;

Projet JeuVersion0, Propriétés, Editeur de liens, entrée, dépendances supplémentaires :
sfml-audio-d.lib;sfml-graphics-d.lib;sfml-network-d.lib;sfml-system-d.lib;sfml-window-d.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;Common-cpp_vc14_debug_windows_md_Win32.lib;Photon-cpp_vc14_debug_windows_md_Win32.lib;LoadBalancing-cpp_vc14_debug_windows_md_Win32.lib

Référence de JeuVersion0 vers Bibliothèque.

Pour executer les tests unitaires : référence de UnitTests vers Bibliothèque et GoogleTestAvecMain (projet à ajouter dans la solution).

Définir JeuVersion0 comme projet de démarrage.



Jeu :
Une fois le jeu lancer, suivre les indications de la console (appuyez sur h afin de obtenir de nouveau les fonctionnalités possibles).

Une fois la partie lancer (dans une room) :
Utilisez les touches directionnelles du clavier une fois le jeu lancer pour déplacer la montgolfière.
Le but est de manger un maximum de nuages (qui rapportent un point) et d'éviter les noisettes(qui enlèvent 10 points).

