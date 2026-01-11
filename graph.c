/**
 *                          GRAPH.C
 *                 Algorithme de Dijkstra
 */

#include "graph.h"
#include <string.h>

// ══════════════════════════════════════════════════════════════════
// FONCTIONS DE GESTION DU GRAPHE
// ══════════════════════════════════════════════════════════════════

/**
 * Crée un nouveau graphe avec un nombre donné de villes
 *
 * Fonctionnement :
 * 1. Alloue la mémoire pour la structure Graph
 * 2. Initialise la matrice d'adjacence :
 *    - Diagonale (i,i) = 0 (distance d'une ville à elle-même)
 *    - Autres cases = INF (pas de connexion par défaut)
 * 3. Initialise les noms des villes par défaut
 */
Graph* createGraph(int numCities) {
    // Vérification du nombre de villes
    if (numCities <= 0 || numCities > MAX_CITIES) {
        printf("Erreur: nombre de villes invalide (doit etre entre 1 et %d)\n", MAX_CITIES);
        return NULL;
    }

    // Allocation mémoire pour le graphe
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        printf("Erreur: allocation memoire echouee\n");
        return NULL;
    }

    // Stocker le nombre de villes
    graph->numCities = numCities;

    // Initialisation de la matrice d'adjacence
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            if (i == j) {
                graph->adjMatrix[i][j] = 0;    // Distance à soi-même = 0
            } else {
                graph->adjMatrix[i][j] = INF;  // Pas de connexion par défaut
            }
        }
        // Nom par défaut pour chaque ville
        sprintf(graph->cityNames[i], "Ville %d", i);
    }

    return graph;
}

/**
 * Ajoute une arête (route) bidirectionnelle entre deux villes
 */
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Vérifications de sécurité
    if (graph == NULL) {
        printf("Erreur: graphe NULL\n");
        return;
    }
    if (src < 0 || src >= graph->numCities || dest < 0 || dest >= graph->numCities) {
        printf("Erreur: index de ville invalide (src=%d, dest=%d)\n", src, dest);
        return;
    }
    if (weight < 0) {
        printf("Erreur: poids negatif non supporte par Dijkstra\n");
        return;
    }

    // Ajout de l'arête dans les deux sens (graphe non orienté)
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
}

/**
 * Définit le nom d'une ville
 */
void setCityName(Graph* graph, int cityIndex, const char* name) {
    if (graph == NULL || cityIndex < 0 || cityIndex >= graph->numCities) {
        return;
    }
    strncpy(graph->cityNames[cityIndex], name, 49);
    graph->cityNames[cityIndex][49] = '\0';
}

/**
 * Affiche le graphe sous forme de matrice d'adjacence
 */
void displayGraph(Graph* graph) {
    if (graph == NULL) {
        printf("Graphe vide\n");
        return;
    }

    printf("\n===== MATRICE D'ADJACENCE =====\n");
    printf("(INF = pas de connexion directe)\n\n");

    // En-tête des colonnes
    printf("%12s", "");
    for (int i = 0; i < graph->numCities; i++) {
        printf("%8d", i);
    }
    printf("\n");

    // Ligne de séparation
    printf("%12s", "");
    for (int i = 0; i < graph->numCities; i++) {
        printf("--------");
    }
    printf("\n");

    // Contenu de la matrice
    for (int i = 0; i < graph->numCities; i++) {
        printf("%10s: ", graph->cityNames[i]);
        for (int j = 0; j < graph->numCities; j++) {
            if (graph->adjMatrix[i][j] == INF) {
                printf("%8s", "INF");
            } else {
                printf("%8d", graph->adjMatrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Libère la mémoire allouée pour le graphe
 */
void freeGraph(Graph* graph) {
    if (graph != NULL) {
        free(graph);
    }
}

// ══════════════════════════════════════════════════════════════════
// ALGORITHME DE DIJKSTRA
// ══════════════════════════════════════════════════════════════════

/**
 * Fonction auxiliaire : trouve le sommet non visité avec la distance minimale
 */
static int findMinDistance(int* dist, int* visited, int numCities) {
    int min = INF;
    int minIndex = -1;

    for (int v = 0; v < numCities; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

/**
 * Algorithme de Dijkstra - Trouve le plus court chemin entre deux villes
 *
 * PRINCIPE :
 * 1. Initialiser toutes les distances à INF, sauf la source (= 0)
 * 2. Répéter :
 *    a) Choisir le sommet non visité avec la plus petite distance
 *    b) Marquer comme visité
 *    c) Mettre à jour les distances des voisins
 * 3. Reconstruire le chemin
 *
 * Complexité : O(V²)
 */
int dijkstra(Graph* graph, int src, int dest, int* path, int* pathLength) {
    // Vérifications
    if (graph == NULL || src < 0 || src >= graph->numCities ||
        dest < 0 || dest >= graph->numCities) {
        return INF;
    }

    int numCities = graph->numCities;
    int dist[MAX_CITIES];      // Distance minimale depuis la source
    int visited[MAX_CITIES];   // Sommets déjà traités
    int parent[MAX_CITIES];    // Prédécesseur dans le chemin

    // ÉTAPE 1 : Initialisation
    for (int i = 0; i < numCities; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[src] = 0;

    // ÉTAPE 2 : Boucle principale
    for (int count = 0; count < numCities - 1; count++) {
        // Trouver le sommet non visité avec distance minimale
        int u = findMinDistance(dist, visited, numCities);

        if (u == -1) break;

        visited[u] = 1;

        // Mettre à jour les distances des voisins
        for (int v = 0; v < numCities; v++) {
            if (!visited[v] &&
                graph->adjMatrix[u][v] != INF &&
                dist[u] != INF &&
                dist[u] + graph->adjMatrix[u][v] < dist[v]) {

                dist[v] = dist[u] + graph->adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    // ÉTAPE 3 : Reconstruction du chemin
    if (path != NULL && pathLength != NULL && dist[dest] != INF) {
        int len = 0;
        int current = dest;
        while (current != -1) {
            len++;
            current = parent[current];
        }

        *pathLength = len;
        current = dest;
        for (int i = len - 1; i >= 0; i--) {
            path[i] = current;
            current = parent[current];
        }
    } else if (pathLength != NULL) {
        *pathLength = 0;
    }

    return dist[dest];
}

/**
 * Calcule les distances minimales entre toutes les paires de villes
 */
void computeAllPairsShortestPaths(Graph* graph, int distMatrix[MAX_CITIES][MAX_CITIES]) {
    if (graph == NULL) return;

    printf("Calcul des plus courts chemins entre toutes les paires...\n");

    for (int i = 0; i < graph->numCities; i++) {
        for (int j = 0; j < graph->numCities; j++) {
            if (i == j) {
                distMatrix[i][j] = 0;
            } else {
                distMatrix[i][j] = dijkstra(graph, i, j, NULL, NULL);
            }
        }
    }

    printf("Calcul termine!\n\n");
}
