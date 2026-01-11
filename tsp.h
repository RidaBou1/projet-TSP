/**
 *      Définitions pour l'algorithme du Voyageur de Commerce
 */
#ifndef TSP_H
#define TSP_H
#include "graph.h"
// ══════════════════════════════════════════════════════════════════
// STRUCTURES DE DONNÉES
// ══════════════════════════════════════════════════════════════════
/**
 * Structure pour stocker le résultat du TSP
 * tour       : tableau contenant l'ordre des villes à visiter
 * tourLength : nombre de villes dans le tour (inclut le retour)
 * totalDistance : distance totale du tour optimal
 */
typedef struct {
    int tour[MAX_CITIES + 1];   // +1 pour le retour à la ville de départ
    int tourLength;             // Nombre d'étapes dans le tour
    int totalDistance;          // Distance totale du tour optimal
} TSPResult;

// ══════════════════════════════════════════════════════════════════
// PROTOTYPES DES FONCTIONS
// ══════════════════════════════════════════════════════════════════

/**
 * Résout le TSP avec l'algorithme Brute Force
 * Teste toutes les permutations possibles pour trouver le tour optimal
 * @param distMatrix : matrice des distances entre toutes les paires de villes
 * @param numCities : nombre de villes
 * @param startCity : ville de départ (index)
 * @return : structure contenant le tour optimal et sa distance
 * Complexité : O(n!) - très lent pour n > 10
 */
TSPResult solveTSPBruteForce(int distMatrix[MAX_CITIES][MAX_CITIES],
                              int numCities,
                              int startCity);
/**
 * Affiche le résultat du TSP
 * @param result : résultat du TSP
 * @param graph : graphe (pour afficher les noms des villes)
 */
void displayTSPResult(TSPResult* result, Graph* graph);
/**
 * Fonction utilitaire pour échanger deux éléments
 * @param a : pointeur vers le premier élément
 * @param b : pointeur vers le second élément
 */
void swap(int* a, int* b);
/**
 * Calcule la distance totale d'un tour donné
 * @param tour : tableau des villes dans l'ordre du tour
 * @param tourLength : nombre de villes
 * @param distMatrix : matrice des distances
 * @return : distance totale du tour
 */
int calculateTourDistance(int* tour, int tourLength,
                          int distMatrix[MAX_CITIES][MAX_CITIES]);
#endif // TSP_H
