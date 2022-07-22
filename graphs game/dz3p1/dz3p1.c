#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define safeMalloc(var, size)\
var = malloc(size * sizeof(*var));\
if (!var) {\
	printf("Dogodila se greska u memoriji.\n");\
	exit(1);\
}

#define safeRealloc(var, size)\
var = realloc(var, (size+1) * sizeof(*var));\
if (!var) {\
	printf("Dogodila se greska u memoriji.\n");\
	exit(1);\
}

#define safeCalloc(var, size)\
var = calloc(size, sizeof(*var));\
if (!var) {\
	printf("Dogodila se greska u memoriji.\n");\
	exit(1);\
}

enum { Maja, Sanja };

/*
// obilazak po sirini
BFS(G,v):
	INIT-QUEUE(Q,n)
	for (i=1 to n) do
		visit[i] = false
	end_for
	visit[v] = true
	P(v)
	INSERT(Q,v)
	while (not QUEUE-EMPTY(Q)) do
		v = DELETE(Q)
		for {u: (v,u) in E} do
			if (not visit[u]) then
				visit[u] = true
				P(u)
				INSERT(Q,u)
			end_if
		end_for
	end_while

// obilazak po dubini
DFS-VISIT-R(v):
	visit[v] = true
	P(v)
	lu[v] = time++
	for {u: (v,u) in E} do
		if (not visit[u]) then
			DFS-VISIT-R(u)
		end_if
	end_for
	fu[v] = time++

DFS-VISIT-I(v):
	INIT-STACK(S,n)
	PUSH(S,v)
	while (not STACK-EMPTY(S)) do
		v = POP(S)
		if (not visit[v]) then
			visit[v] = true
			P(v)
			for {u: (v,u) in E} do
				if (not visit[u]) then
					PUSH(S,u)
				end_if
			end_for
		end_if
	end_while

DFS(G,v):
	for (i=1 to n) do
		visit[i] = false
	end_for
	DFS-VISIT(v)

// pronalazenje povezanih komponenti
CONN-COMP(G):
	n_cc = 0
	for (i=1 to n) do
		visit[i] = 0
	end_for
	for (i=1 to n) do
		if (not visit[i]) then
			n_cc++
			DFS-VISIT(i) -> CC(n_cc)
		end_if
	end_for

// formiranje minimalnog obuhvatnog stabla
PRIM(G,s):
	U = {s}
	E' = emptySet
	while (U != V) do
		find(u,v) => min {w(u,v): (u in U) and v in (V-U)}
		U += {v}
		E' += {(u,v)}
	end_while
	MST = (U,E')
	return MST

KRUSKAL(G):
	INIT-QUEUE(PQ,n)
	E' = emptySet
	for (each (u,v) in E) do
		PQ-INSERT(PQ, w(u,v))
	end_for
	num = 0
	while (num < n-1) do
		w(u,v) = PQ-MIN-DELETE(PQ)
		if ((u in Ti) and (v in Tj) and (i!=j)) then
			E' += {(u,v)}
			Tk = Ti + Tj
			num++
		end_if
	end_while
	MST = (V,E')
	return MST

// formiranje matrice puta
WARSHALL(A):
	P = A
	for (k=1 to n) do
		for (i=1 to n) do
			if (p[i,k] = 1) then
				for (j=1 to n) do
					p[i,j] = p[i,j] or p[k,j]
				end_for
			end_if
		end_for
	end_for

// formiranje najkracih puteva izmedju svih parova cvorova
FLOYD(W):
	D = W
	for (k=1 to n) do
		for (i=1 to n) do
			for (j=1 to n) do
				if (d[i,j] > d[i,k] + d[k,j]) then
					t[i,j] = t[k,j]
					d[i,j] = d[i,k] + d[k,j]
				end_if
			end_for
		end_for
	end_for

// ispisivanje najkraceg puta izmedju dva cvora
PATH(i,j):
	if (i = j) then
		PRINT(i)
		return
	else
		if (t[i,j] = 0) then
			PRINT("Nema puta izmedju i i j")
		else
			PATH(i, t[i,j])
			PRINT(j)
		end_if
	end_if

// formiranje najkracih puteva od jednog cvora do svih ostalih
DIJKSTRA(W):
	S = {1}
	for (i=2 to n) do
		d[i] = w[1,j]
		if (w[1,j] != inf) then
			t[i] = 1
		else
			t[i] = 0
		end_if
	end_for
	for (k=1 to n-1) do
		find min {d[i]: i in (V-S)}
		S += {i}
		for (each j in (V-S)) do
			if (d[i] + w[i,j] < d[j]) then
				t[j] = i
				d[j] = d[i] + w[i,j]
			end_if
		end_for
	end_for

DIJKSTRA(W, x):
	S = {x}
	for (i=1 to n) do
		d[i] = w[x,i]
		if (w[x,i] != inf) then
			t[i] = x
		else
			t[i] = 0
		end_if
	end_for
	for (k=1 to n-1) do
		find min {d[i]: i in (V-S)}
		if (d[i] = inf) then
			break
		end_if
		S = S + {i}
		foreach (j in (V-S)) do
			if (d[i] + w[i,j] < d[j]) then
				d[j] = d[i] + w[i,j]
				t[j] = i
			end_if
		end_for
	end_for

// maksimizacija protoka u grafu
FORD-FULKERSON(G):
	for (each (u,v) in E) do
		f(u,v) = 0
		f(v,u) = 0
	end_for
	while (exists p(S,T) in Gf) do
		cf(p) = min {cf(u,v): (u,v) in p}
		for (each (u,v) in p) do
			f(u,v) = f(u,v) + cf(p)
			f(v,u) = -f(u,v)
		end_for
	end_while

// topolosko sortiranje
TOP-SORT(G)
	A = V
	B = E
	for (i=1 to n) do
		find u in A: din(u)=0
		T[i] = u
		A -= {u}
		for {v: (u,v) in B} do
			B -= {(u,v)}
		end_for
	end_for

// kriticni put
CRITICAL-PATH(G)
	TOP-SORT(G)
	EST[1] = 0
	for (u=2 to n) do
		i = T[u]
		foreach j in P(i) do
			EST[i] = max {EST[j] + w(j,i)}
		end_for
	end_for
	LST[n] = EST[n]
	for (u=n-1 to 1) do
		i = T[u]
		foreach j in S(i) do
			LST[i] = min{LST[j] - w(j,i)}
		end_for
	end_for
	for (i=1 to n) do
		L[i] = LST[i] - EST[i]
	end_for
*/

typedef struct Vertex {
	char id;
	struct Vertex *next;
} vertex;

typedef struct Header {
	vertex *first;
	struct Header *next;
} header;

typedef struct Graph {
	int num;
	header *arr;
} graph;

typedef struct Stek {
	int level;
	char id;
	int ind;
	struct Stek *next;
} stek;

graph *loadGraph(graph *G) {
	if (!G) {
		safeMalloc(G, 1);
		G->num = 0;
		G->arr = NULL;
		printf("Uspesno ste ucitali graf.\n\n");
	}
	else
		printf("Vec ste ucitali graf.\n\n");
	return G;
}

graph *deleteGraph(graph *G, int ind) {
	if (G) {
		header *curr = G->arr, *prev = NULL;
		while (curr) {
			prev = curr;
			curr = curr->next;
			vertex *vCurr = prev->first, *vPrev = NULL;
			while (vCurr) {
				vPrev = vCurr;
				vCurr = vCurr->next;
				free(vPrev);
			}
			free(prev);
		}
		free(G);
		if (ind) printf("Uspesno ste izbrisali graf.\n\n");
	}
	else {
		if (ind) printf("Vas graf je vec prazan.\n\n");
	}
	return NULL;
}

void printGraphRepresentation(graph *G) {
	if (!G || G->num == 0)
		printf("Vas graf je prazan.\n\n");
	else {
		printf("Broj cvorova: %d\n", G->num);
		header *curr = G->arr;
		while (curr) {
			printf("Cvor %c: ", curr->first->id);
			vertex *vCurr = curr->first->next;
			while (vCurr) {
				printf("->|%c|", vCurr->id);
				vCurr = vCurr->next;
			}
			puts("");
			curr = curr->next;
		}
		puts("");
	}
}

graph *addVertex(graph *G, char id) {
	if (!G)
		printf("Najpre morate ucitati graf.\n\n");
	else {
		header *curr = G->arr;
		while (curr) {
			if (curr->first->id == id) {
				printf("Vec ste uneli dati cvor.\n\n");
				return G;
			}
			curr = curr->next;
		}
		header *elem = NULL;
		vertex *v = NULL;
		safeMalloc(elem, 1);
		safeMalloc(v, 1);
		v->id = id;
		v->next = NULL;
		elem->first = v;
		elem->next = NULL;
		if (!G->num)
			G->arr = elem;
		else {
			header *curr = G->arr;
			while (curr->next) curr = curr->next;
			curr->next = elem;
		}
		G->num++;
		printf("Uspesno ste uneli cvor.\n\n");
	}
	return G;
}

graph *addEdge(graph *G, char first, char second) {
	if (!G) {
		printf("Najpre morate ucitati graf.\n\n");
		return NULL;
	}
	int ind = 0;
	header *curr = G->arr, *find = NULL;
	while (curr) {
		if (curr->first->id == first) {
			find = curr;
			ind++;
		}
		if (curr->first->id == second)
			ind++;
		if (ind == 2) break;
		curr = curr->next;
	}
	if (ind == 2) {
		vertex *vcurr = find->first->next;
		while (vcurr) {
			if (vcurr->id == second) {
				printf("Data grana vec postoji.\n\n");
				return G;
			}
			vcurr = vcurr->next;
		}
		vertex *v = NULL;
		safeMalloc(v, 1);
		v->id = second;
		v->next = find->first->next;
		find->first->next = v;
		printf("Uspesno ste dodali granu u graf.\n\n");
	}
	else printf("Najpre morate uneti trazene cvorove.\n\n");
	return G;
}

graph *removeVertex(graph *G, char id) {
	if (!G) {
		printf("Najpre morate ucitati graf.\n\n");
		return NULL;
	}
	int ind = 0;
	header *curr = G->arr, *prev = NULL;
	vertex *v = NULL, *vprev = NULL, *old = NULL;
	while (curr) {
		if (curr->first->id == id) {
			ind = 1;
			break;
		}
		curr = curr->next;
	}
	if (!ind) printf("Najpre morati uneti cvor.\n\n");
	else {
		curr = G->arr;
		while (curr) {
			v = curr->first->next;
			vprev = curr->first;
			while (v) {
				if (v->id == id) {
					old = v;
					vprev->next = v->next;
					v = v->next;
					free(old);
				}
				else {
					vprev = v;
					v = v->next;
				}
			}
			curr = curr->next;
		}
		curr = G->arr;
		while (curr->first->id != id) {
			prev = curr;
			curr = curr->next;
		}
		v = curr->first;
		while (v) {
			vprev = v;
			v = v->next;
			curr->first = v;
			free(vprev);
		}
		if (G->arr == curr)
			G->arr = curr->next;
		else prev->next = curr->next;
		free(curr);
		G->num--;
		printf("Uspesno ste izbrisali cvor.\n\n");
	}
	return G;
}

graph *removeEdge(graph *G, char first, char second) {
	if (!G) {
		printf("Najpre morate ucitati graf.\n\n");
		return NULL;
	}
	int ind = 0;
	header *curr = G->arr, *find = NULL;
	while (curr) {
		if (curr->first->id == first) {
			find = curr;
			ind = 1;
			break;
		}
		curr = curr->next;
	}
	if (!ind) printf("Najpre morati uneti odgovarajuci cvor.\n\n");
	else {
		ind = 0;
		vertex *v = find->first->next, *prev = find->first, *old = NULL;
		while (v) {
			if (v->id == second) {
				ind = 1;
				old = v;
				prev->next = v->next;
				free(old);
				break;
			}
			prev = v;
			v = v->next;
		}
		if (!ind) printf("Data grana ne postoji u vasem grafu.\n\n");
		else printf("Uspesno ste izbrisali granu u grafu.\n\n");
	}
	return G;
}

int returnOrdinal(graph *G, char id) {
	int i = 0;
	header *curr = G->arr;
	while (curr->first->id != id) {
		i++;
		curr = curr->next;
	}
	return i;
}

int returnMaxIn(graph *G) {
	int max = 0, counter;
	header *currVert = G->arr;
	while (currVert) {
		counter = 0;
		char id = currVert->first->id;
		header *currEdge = G->arr;
		while (currEdge) {
			vertex *curr = currEdge->first->next;
			while (curr) {
				if (curr->id == id) counter++;
				curr = curr->next;
			}
			currEdge = currEdge->next;
		}
		if (counter > max) max = counter;
		currVert = currVert->next;
	}
	return max;
}

vertex *returnVertex(graph *G, char id) {
	header *curr = G->arr;
	while (curr->first->id != id) curr = curr->next;
	return curr->first;
}

stek *stackPush(stek *S, char id, int level, int ind) {
	if (!S) {
		safeMalloc(S, 1);
		S->level = level;
		S->id = id;
		S->ind = ind;
		S->next = NULL;
	}
	else {
		stek *node = NULL;
		safeMalloc(node, 1);
		node->id = id;
		node->level = level;
		node->ind = ind;
		node->next = S;
		S = node;
	}
	return S;
}

stek *stackPop(stek *S, char *id, int *level, int *ind) {
	if (S) {
		stek *old = S;
		S = S->next;
		*id = old->id;
		*level = old->level;
		*ind = old->ind;
		free(old);
	}
	return S;
}

int stackEmpty(stek *S) {
	if (S) return 0;
	else return 1;
}

int printPaths(graph *G, char idFirst, char idLast, int distance, int MajaSanja) {
	if (!G || !G->num) return 0;
	int *visited = NULL, isOkay = 2, maxIn = returnMaxIn(G);
	safeCalloc(visited, G->num);
	char id, currId; int level, currLevel;
	int ind, currInd; int i, j;
	stek *path = NULL, *help = NULL, *dfs = NULL;
	dfs = stackPush(dfs, idFirst, 0, -1);
	while (!stackEmpty(dfs)) {
		dfs = stackPop(dfs, &id, &level, &ind);
		if (level > distance) break;
		i = returnOrdinal(G, id);
		visited[i]++;
		if (visited[i] == 3 * maxIn && isOkay != 1) isOkay = 0;
		path = stackPush(path, id, level, ind);
		if (level == distance && ind != 2) {
			if (path->id == idLast) {
				while (!stackEmpty(path)) {
					path = stackPop(path, &currId, &currLevel, &currInd);
					help = stackPush(help, currId, currLevel, currInd);
				}
				while (!stackEmpty(help)) {
					help = stackPop(help, &currId, &currLevel, &currInd);
					if (help) printf("%c%c%c->", currInd == 2 ? '(' : 0, currId, (!currInd && (currId != idFirst)) ? ')' : 0);
					else printf("%c%c%c\n", currInd == 2 ? '(' : 0, currId, (!currInd && (currId != idFirst)) ? ')' : 0);
					path = stackPush(path, currId, currLevel, currInd);
				}
				isOkay = 1;
			}
			if (!dfs) break;
			level = dfs->level;
			while (path->level >= level)
				if (path->level == level && !dfs->ind && path->ind == 2) break;
				else path = stackPop(path, &currLevel, &currLevel, &currInd);
		}
		else {
			vertex *v = returnVertex(G, id)->next;
			while (v) {
				if (ind == 2) dfs = stackPush(dfs, v->id, level, 0);
				else if (ind == -1) {
					if (!MajaSanja) dfs = stackPush(dfs, v->id, level + 1, -1);
					else dfs = stackPush(dfs, v->id, level + 1, 1);
				}
				else dfs = stackPush(dfs, v->id, level + 1, ind + 1);
				v = v->next;
			}
		}
	}
	if (visited) {
		if (level < distance) isOkay = 0;
		free(visited);
	}
	return isOkay;
}

void menu() {
	puts("1 - Kreiraj prazan graf");
	puts("2 - Dodaj cvor u graf");
	puts("3 - Ukloni cvor iz grafa");
	puts("4 - Dodaj granu u graf");
	puts("5 - Ukloni granu iz grafa");
	puts("6 - Ispisi reprezentaciju grafa");
	puts("7 - Izbrisi graf iz memorije");
	puts("8 - Simuliraj igru");
	puts("9 - Izadji iz programa");
	printf("Izbor: ");
}

int main() {
	int choice, distanceMaja, distanceSanja, ind1, ind2;
	char val, val1, val2;
	graph *G = NULL;
	while (1) {
		menu();
		scanf("%d", &choice);
		switch (choice) {
			// kreiranje praznog grafa
			case 1:
				G = loadGraph(G);
				break;
				// dodavanja cvora u graf
			case 2:
				getchar();
				printf("Unesite naziv cvora: ");
				val = getchar();
				G = addVertex(G, toupper(val));
				break;
				// uklanjanje cvora iz grafa
			case 3:
				getchar();
				printf("Unesite naziv cvora: ");
				val = getchar();
				G = removeVertex(G, toupper(val));
				break;
				// dodavanje grane grafa
			case 4:
				getchar();
				printf("Unesite naziv prvog cvora: ");
				val1 = getchar();
				getchar();
				printf("Unesite naziv drugog cvora: ");
				val2 = getchar();
				G = addEdge(G, toupper(val1), toupper(val2));
				break;
				// uklanjanje grane grafa
			case 5:
				getchar();
				printf("Unesite naziv prvog cvora: ");
				val1 = getchar();
				getchar();
				printf("Unesite naziv drugog cvora: ");
				val2 = getchar();
				G = removeEdge(G, toupper(val1), toupper(val2));
				break;
				// ispisivanje reprezentacije grafa
			case 6:
				printGraphRepresentation(G);
				break;
				// brisanje grafa iz memorije
			case 7:
				G = deleteGraph(G, 1);
				break;
				// simuliranje igre
			case 8:
				distanceMaja = 0;
				printf("Maja\n");
				while (++distanceMaja) {
					ind1 = printPaths(G, 'X', 'Y', distanceMaja, Maja);
					if (!ind1 || ind1 == 1) {
						if (!ind1) printf("Ne moze da stigne do cilja.\n");
						else printf("Broj poteza: %d\n", distanceMaja);
						break;
					}
				}
				distanceSanja = 0;
				printf("Sanja\n");
				while (++distanceSanja) {
					ind2 = printPaths(G, 'X', 'Y', distanceSanja, Sanja);
					if (!ind2 || ind2 == 1) {
						if (!ind2) printf("Ne moze da stigne do cilja.\n");
						else printf("Broj poteza: %d\n", distanceSanja);
						break;
					}
				}
				printf("-------------------------------------------------------\n");
				if (!ind1 && !ind2) printf("Nema pobednika, jer niko ne moze da stigne do cilja.\n");
				else if (ind1 && !ind2) printf("Maja je pobednik, jer Sanja ne moze da stigne do cilja.\n");
				else {
					if (distanceMaja == distanceSanja) printf("Nereseno je, jer su obe odigrale isti broj poteza.\n");
					else if (distanceMaja < distanceSanja) printf("Maja je pobednik, jer je odigrala manje poteza.\n");
					else printf("Sanja je pobednik, jer je odigrala manje poteza.\n");
				}
				puts("-------------------------------------------------------\n");
				break;
				// kraj programa
			case 9:
				G = deleteGraph(G, 0);
				printf("Uspesno ste zavrsili program.\n");
				return 0;
				break;
			default:
				printf("Los izbor, pokusajte ponovo.\n\n");
				break;
		}
	}
	return 0;
}