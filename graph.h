/**
 *        Définitions des structures et fonctions du graphe
 */
#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// ══════════════════════════════════════════════════════════════════
// CONSTANTES
// ══════════════════════════════════════════════════════════════════
#define MAX_CITIES 10       // Nombre maximum de villes
#define INF INT_MAX         // Valeur "infini" (pas de connexion)
// ══════════════════════════════════════════════════════════════════
// STRUCTURES DE DONNÉES
// ══════════════════════════════════════════════════════════════════
typedef struct {
    int numCities;                          // Nombre de villes
    int adjMatrix[MAX_CITIES][MAX_CITIES];  // Matrice d'adjacence
    char cityNames[MAX_CITIES][50];         // Noms des villes
} Graph;
// ══════════════════════════════════════════════════════════════════
// PROTOTYPES DES FONCTIONS
// ══════════════════════════════════════════════════════════════════
/**
 * Crée et initialise un nouveau graphe
 * @param numCities : nombre de villes
 * @return : pointeur vers le graphe créé
 */
Graph* createGraph(int numCities);
/**
 * Ajoute une arête (route) entre deux villes
 * @param graph : le graphe
 * @param src : ville source (index)
 * @param dest : ville destination (index)
 * @param weight : distance/poids de la route
 */
void addEdge(Graph* graph, int src, int dest, int weight);
/**
 * Définit le nom d'une ville
 * @param graph : le graphe
 * @param cityIndex : index de la ville
 * @param name : nom de la ville
 */
void setCityName(Graph* graph, int cityIndex, const char* name);
/**
 * Affiche le graphe (matrice d'adjacence)
 * @param graph : le graphe à afficher
 */
void displayGraph(Graph* graph);
/**
 * Libère la mémoire du graphe
 * @param graph : le graphe à libérer
 */
void freeGraph(Graph* graph);
/**
 * Algorithme de Dijkstra - trouve le plus court chemin
 * @param graph : le graphe
 * @param src : ville de départ
 * @param dest : ville d'arrivée
 * @param path : tableau pour stocker le chemin (peut être NULL)
 * @param pathLength : longueur du chemin trouvé
 * @return : distance minimale entre src et dest
 */
int dijkstra(Graph* graph, int src, int dest, int* path, int* pathLength);
/**
 * Calcule toutes les distances minimales entre toutes les paires de villes
 * @param graph : le graphe original
 * @param distMatrix : matrice pour stocker les distances minimales
 */
void computeAllPairsShortestPaths(Graph* graph, int distMatrix[MAX_CITIES][MAX_CITIES]);
#endif // GRAPH_H
