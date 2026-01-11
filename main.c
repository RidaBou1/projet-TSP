/**
 *    Algorithmes : Dijkstra + Brute Force
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "tsp.h"
// ══════════════════════════════════════════════════════════════════
// CRÉATION DU GRAPHE DE TEST
// ══════════════════════════════════════════════════════════════════
/**
 * Crée un graphe de test avec 10 villes marocaines
 * et des distances réalistes entre elles (en km)
 */
Graph* createTestGraph() {
    Graph* graph = createGraph(10);
    if (graph == NULL) return NULL;
    // Définir les noms des villes
    setCityName(graph, 0, "Casablanca");
    setCityName(graph, 1, "Rabat");
    setCityName(graph, 2, "Marrakech");
    setCityName(graph, 3, "Fes");
    setCityName(graph, 4, "Tanger");
    setCityName(graph, 5, "Agadir");
    setCityName(graph, 6, "Meknes");
    setCityName(graph, 7, "Oujda");
    setCityName(graph, 8, "Tetouan");
    setCityName(graph, 9, "El Jadida");
    // Ajouter les routes (distances en km)
    // Routes depuis Casablanca (0)
    addEdge(graph, 0, 1, 87);    // Casablanca - Rabat
    addEdge(graph, 0, 2, 243);   // Casablanca - Marrakech
    addEdge(graph, 0, 9, 96);    // Casablanca - El Jadida
    addEdge(graph, 0, 3, 295);   // Casablanca - Fes
    // Routes depuis Rabat (1)
    addEdge(graph, 1, 4, 250);   // Rabat - Tanger
    addEdge(graph, 1, 3, 207);   // Rabat - Fes
    addEdge(graph, 1, 6, 138);   // Rabat - Meknes
    // Routes depuis Marrakech (2)
    addEdge(graph, 2, 5, 258);   // Marrakech - Agadir
    addEdge(graph, 2, 9, 200);   // Marrakech - El Jadida
    // Routes depuis Fes (3)
    addEdge(graph, 3, 6, 60);    // Fes - Meknes
    addEdge(graph, 3, 7, 332);   // Fes - Oujda
    addEdge(graph, 3, 4, 303);   // Fes - Tanger
    // Routes depuis Tanger (4)
    addEdge(graph, 4, 8, 60);    // Tanger - Tetouan
    // Routes depuis Agadir (5)
    addEdge(graph, 5, 9, 296);   // Agadir - El Jadida
    return graph;
}
// ══════════════════════════════════════════════════════════════════
// FONCTIONS DE TEST
// ══════════════════════════════════════════════════════════════════
/**
 * Test de l'algorithme de Dijkstra
 */
void testDijkstra(Graph* graph) {
    printf("\n");
    printf("+========================================+\n");
    printf("|     TEST DE L'ALGORITHME DIJKSTRA      |\n");
    printf("+========================================+\n\n");
    int path[MAX_CITIES];
    int pathLength;
    // Test 1 : Casablanca vers Oujda
    printf("Test 1 : Casablanca -> Oujda\n");
    printf("----------------------------\n");
    int dist = dijkstra(graph, 0, 7, path, &pathLength);
    if (dist == INF) {
        printf("Pas de chemin trouve!\n");
    } else {
        printf("Distance minimale : %d km\n", dist);
        printf("Chemin : ");
        for (int i = 0; i < pathLength; i++) {
            printf("%s", graph->cityNames[path[i]]);
            if (i < pathLength - 1) printf(" -> ");
        }
        printf("\n");
    }
    // Test 2 : Agadir vers Tetouan
    printf("\nTest 2 : Agadir -> Tetouan\n");
    printf("--------------------------\n");
    dist = dijkstra(graph, 5, 8, path, &pathLength);
    if (dist == INF) {
        printf("Pas de chemin trouve!\n");
    } else {
        printf("Distance minimale : %d km\n", dist);
        printf("Chemin : ");
        for (int i = 0; i < pathLength; i++) {
            printf("%s", graph->cityNames[path[i]]);
            if (i < pathLength - 1) printf(" -> ");
        }
        printf("\n");
    }
    printf("\n");
}
/**
 * Test de l'algorithme TSP Brute Force
 */
void testTSP(Graph* graph) {
    printf("\n");
    printf("+========================================+\n");
    printf("|     TEST DU TSP (BRUTE FORCE)          |\n");
    printf("+========================================+\n\n");
    // Calculer les distances minimales
    int distMatrix[MAX_CITIES][MAX_CITIES];
    computeAllPairsShortestPaths(graph, distMatrix);
    // Afficher la matrice
    printf("Matrice des distances minimales :\n");
    printf("(calculees avec Dijkstra)\n\n");
    printf("%12s", "");
    for (int i = 0; i < graph->numCities; i++) {
        printf("%6d", i);
    }
    printf("\n");
    for (int i = 0; i < graph->numCities; i++) {
        printf("%10s: ", graph->cityNames[i]);
        for (int j = 0; j < graph->numCities; j++) {
            if (distMatrix[i][j] == INF) {
                printf("%6s", "INF");
            } else {
                printf("%6d", distMatrix[i][j]);
            }
        }
        printf("\n");
    }
    // Résoudre le TSP
    printf("\n");
    TSPResult result = solveTSPBruteForce(distMatrix, graph->numCities, 0);
    displayTSPResult(&result, graph); // Afficher le résultat
}
/**
 * Menu interactif
 */
void interactiveMenu(Graph* graph) {
    int choice;
    int distMatrix[MAX_CITIES][MAX_CITIES];
    int distMatrixComputed = 0;
    do {
        printf("\n");
        printf("+========================================+\n");
        printf("|           MENU PRINCIPAL               |\n");
        printf("+========================================+\n");
        printf("|  1. Afficher le graphe                 |\n");
        printf("|  2. Trouver le plus court chemin       |\n");
        printf("|     (Dijkstra)                         |\n");
        printf("|  3. Resoudre le TSP                    |\n");
        printf("|  4. Ajouter une route                  |\n");
        printf("|  5. Quitter                            |\n");
        printf("+========================================+\n");
        printf("\nVotre choix : ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }
        switch (choice) {
            case 1:
                displayGraph(graph);
                break;
            case 2: {
                int src, dest;
                printf("\nVille de depart (0-%d) : ", graph->numCities - 1);
                scanf("%d", &src);
                printf("Ville d'arrivee (0-%d) : ", graph->numCities - 1);
                scanf("%d", &dest);
                int path[MAX_CITIES];
                int pathLength;
                int dist = dijkstra(graph, src, dest, path, &pathLength);
                printf("\n--- Resultat ---\n");
                if (dist == INF) {
                    printf("Aucun chemin trouve!\n");
                } else {
                    printf("Distance : %d km\n", dist);
                    printf("Chemin : ");
                    for (int i = 0; i < pathLength; i++) {
                        printf("%s", graph->cityNames[path[i]]);
                        if (i < pathLength - 1) printf(" -> ");
                    }
                    printf("\n");
                }
                break;
            }
            case 3: {
                int startCity;
                printf("\nVille de depart pour le tour (0-%d) : ",
                       graph->numCities - 1);
                scanf("%d", &startCity);

                if (!distMatrixComputed) {
                    computeAllPairsShortestPaths(graph, distMatrix);
                    distMatrixComputed = 1;
                }
                TSPResult result = solveTSPBruteForce(distMatrix,
                                                       graph->numCities,
                                                       startCity);
                displayTSPResult(&result, graph);
                break;
            }
            case 4: {
                int src, dest, weight;
                printf("\nVille source (0-%d) : ", graph->numCities - 1);
                scanf("%d", &src);
                printf("Ville destination (0-%d) : ", graph->numCities - 1);
                scanf("%d", &dest);
                printf("Distance (km) : ");
                scanf("%d", &weight);
                addEdge(graph, src, dest, weight);
                distMatrixComputed = 0;
                printf("Route ajoutee!\n");
                break;
            }
            case 5:
                printf("\nAu revoir!\n");
                break;
            default:
                printf("\nChoix invalide.\n");
        }
    } while (choice != 5);
}
// ══════════════════════════════════════════════════════════════════
// PROGRAMME PRINCIPAL
// ══════════════════════════════════════════════════════════════════
int main() {
    printf("\n");
    printf("+=========================================================+\n");
    printf("|   PROJET TSP - PROBLEME DU VOYAGEUR DE COMMERCE         |\n");
    printf("|   Algorithmes : Dijkstra + Brute Force                  |\n");
    printf("+=========================================================+\n\n");
    // Créer le graphe de test
    printf("Creation du graphe avec 10 villes marocaines...\n");
    Graph* graph = createTestGraph();
    if (graph == NULL) {
        printf("Erreur lors de la creation du graphe!\n");
        return 1;
    }
    printf("Graphe cree avec succes!\n");
    displayGraph(graph);    // Afficher le graphe
    testDijkstra(graph);     // Tester Dijkstra
    testTSP(graph);     // Tester TSP
    // Menu interactif (décommenter pour activer)
    // interactiveMenu(graph);
    freeGraph(graph); // Libérer la mémoire
    printf("\nProgramme termine avec succes!\n");
    return 0;
}
