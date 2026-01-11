/**
* Implémentation de l'algorithme TSP Brute Force
 */
#include "tsp.h"
#include <string.h>
// ══════════════════════════════════════════════════════════════════
// VARIABLES GLOBALES POUR L'ALGORITHME BRUTE FORCE
// ══════════════════════════════════════════════════════════════════
static int bestDistance;                    // Meilleure distance trouvée
static int bestTour[MAX_CITIES + 1];        // Meilleur tour trouvé
static int (*globalDistMatrix)[MAX_CITIES]; // Pointeur vers la matrice
static int globalNumCities;                 // Nombre de villes
// ══════════════════════════════════════════════════════════════════
// FONCTIONS UTILITAIRES
// ══════════════════════════════════════════════════════════════════
/**
 * Échange deux valeurs entières
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
/**
 * Calcule la distance totale d'un tour
 */
int calculateTourDistance(int* tour, int tourLength, int distMatrix[MAX_CITIES][MAX_CITIES]) {
    int totalDistance = 0;
    // Additionner les distances entre villes consécutives
    for (int i = 0; i < tourLength - 1; i++) {
        int from = tour[i];
        int to = tour[i + 1];

        if (distMatrix[from][to] == INF) {
            return INF;
        }
        totalDistance += distMatrix[from][to];
    }
    // Ajouter le retour à la ville de départ
    int lastCity = tour[tourLength - 1];
    int firstCity = tour[0];
    if (distMatrix[lastCity][firstCity] == INF) {
        return INF;
    }
    totalDistance += distMatrix[lastCity][firstCity];
    return totalDistance;
}
// ══════════════════════════════════════════════════════════════════
// ALGORITHME DE PERMUTATION (RÉCURSIF)
// ══════════════════════════════════════════════════════════════════
static void permute(int* cities, int start, int end) {
    // CAS DE BASE : permutation complète
    if (start == end) {
        int distance = calculateTourDistance(cities, globalNumCities, globalDistMatrix);
        if (distance < bestDistance) {
            bestDistance = distance;
            for (int i = 0; i < globalNumCities; i++) {
                bestTour[i] = cities[i];
            }
            bestTour[globalNumCities] = cities[0];
        }
    } else {
        // CAS RÉCURSIF : générer les permutations
        for (int i = start; i <= end; i++) {
            swap(&cities[start], &cities[i]);
            permute(cities, start + 1, end);
            swap(&cities[start], &cities[i]);  // Backtrack
        }
    }
}
// ══════════════════════════════════════════════════════════════════
// FONCTION PRINCIPALE TSP
// ══════════════════════════════════════════════════════════════════
TSPResult solveTSPBruteForce(int distMatrix[MAX_CITIES][MAX_CITIES],
                              int numCities,
                              int startCity) {
    TSPResult result;
    // Vérifications
    if (numCities <= 0 || numCities > MAX_CITIES ||
        startCity < 0 || startCity >= numCities) {
        result.totalDistance = INF;
        result.tourLength = 0;
        return result;
    }
    // Cas trivial : une seule ville
    if (numCities == 1) {
        result.tour[0] = startCity;
        result.tour[1] = startCity;
        result.tourLength = 2;
        result.totalDistance = 0;
        return result;
    }
    // Initialisation
    bestDistance = INF;
    globalDistMatrix = distMatrix;
    globalNumCities = numCities;
    // Créer le tableau avec startCity en premier
    int cities[MAX_CITIES];
    cities[0] = startCity;
    int idx = 1;
    for (int i = 0; i < numCities; i++) {
        if (i != startCity) {
            cities[idx++] = i;
        }
    }
    // Afficher les informations
    printf("Resolution du TSP par Brute Force...\n");
    printf("Nombre de villes : %d\n", numCities);
    printf("Ville de depart : %d\n", startCity);
    printf("Nombre de permutations a tester : ");
    // Calculer (n-1)!
    long long factorial = 1;
    for (int i = 2; i < numCities; i++) {
        factorial *= i;
    }
    printf("%lld\n\n", factorial);
    // Lancer la recherche (permuter positions 1 à n-1)
    permute(cities, 1, numCities - 1);
    // Copier le résultat
    result.totalDistance = bestDistance;
    result.tourLength = numCities + 1;
    for (int i = 0; i <= numCities; i++) {
        result.tour[i] = bestTour[i];
    }
    return result;
}
/**
 * Affiche le résultat du TSP
 */
void displayTSPResult(TSPResult* result, Graph* graph) {
    if (result == NULL) {
        printf("Resultat NULL\n");
        return;
    }
    printf("\n===== RESULTAT DU TSP =====\n\n");
    if (result->totalDistance == INF) {
        printf("Aucun tour valide trouve!\n");
        printf("(Certaines villes ne sont pas connectees)\n");
        return;
    }
    printf("Distance totale minimale : %d\n\n", result->totalDistance);
    printf("Tour optimal :\n");
    for (int i = 0; i < result->tourLength; i++) {
        int cityIndex = result->tour[i];
        if (graph != NULL) {
            printf("  %d. %s (ville %d)", i + 1,
                   graph->cityNames[cityIndex], cityIndex);
        } else {
            printf("  %d. Ville %d", i + 1, cityIndex);
        }
        if (i < result->tourLength - 1) {
            printf(" ---> ");
        }
        printf("\n");
    }
    printf("\n");
}
