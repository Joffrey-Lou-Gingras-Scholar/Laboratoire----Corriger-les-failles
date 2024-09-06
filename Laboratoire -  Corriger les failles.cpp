#define _CRT_SECURE_NO_WARNINGS // Désactive les avertissements relatifs à l'utilisation de fonctions non sécurisées
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    int pansDeCloture{ stoi(argv[1]) };  // Entrer une valeur non entière provoque un crash. // Peut perdre en précision si une valeur décimale est fournie.
    float montantAPayer{ stof(argv[2]) };  // Entrer une valeur non flottante provoque un crash.
    float coutParPan{ montantAPayer / pansDeCloture };  

    // Calcul du nombre de poteaux nécessaires pour une clôture en ligne droite.
    int poteaux{ pansDeCloture }; // Initialisation d'une variable qui semble inutile.
    montantAPayer += poteaux * 5;

    char nomFichier[10];
    strcpy(nomFichier, argv[3]); 
    // Peut causer un dépassement de tampon et permettre une injection de code malveillant.
    // Exemple : "\x31\xC0\xB0\x46\x31\xDB\x31\xC9\xCD\x80\xEB\x16\x5B\x31\xC0\x88\x43\x07\x89\x5B\x08\x89\x43\x0C\xB0\x0B\x8D\x4B\x08\x8D\x53\x0C\xCD\x80\xE8\xE5\xFF\xFF\xFF\x2F\x62\x69\x6E\x2F\x73\x68" 
    // Cela peut provoquer l'erreur "Run-Time Check Failure #2 - Stack around the variable 'nomFichier' was corrupted."
    // Utiliser `std::string` pour éviter ces problèmes :
    // string a = "Hello.";
    // string b = a;

    strcat(nomFichier, ".exe");  // Risque de dépassement de tampon avec strcat, utilisez plutôt `std::string`.

    ofstream fichier{ nomFichier };
    fichier << argv[4];

    const char* msg{ argv[4] }; 
    // Exemple problématique : "Hello World %s%s%s%s%s%s" qui pourrait pointer vers des adresses invalides.
    // Exemple : "Hello World %p %p %p %p %p %p" peut corrompre l'affichage.
    // Utiliser `cout` à la place pour éviter ces vulnérabilités.

    printf(msg, pansDeCloture, coutParPan); 
    // Risque d'exécution de commandes via des overflow format string.
    // Exemple : "Bob %x %x %x %x %x %x %x %x%n" provoque des comportements indésirables.
    // Préférez `cout` pour afficher les messages.

    const char* commande{ argv[5] };
    system(commande); 
    // Exécute des commandes dans le terminal, ce qui est dangereux.
    // Exemple : "taskmgr" ouvre le gestionnaire des tâches.
    // Évitez d'utiliser `system` avec des entrées non validées.
}