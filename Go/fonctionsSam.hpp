#ifndef FONCTIONS_SAM_HPP
#define FONCTIONS_SAM_HPP

vector<Vector2i> getCoupsPossibles(const vector<vector<char>> &grille, const char joueur)
{
	Plateau gob(Vector2i(size(grille), size(grille[0])));
	gob.terrain = grille;
	gob.tour = joueur;

	vector<Vector2i> positions;

	for (int i = 0; i < size(grille); ++i)
	{
		for (int j = 0; j < size(grille[0]); ++j)
		{
			if (grille[i][j] == 'X' && !gob.isSuicide({i, j}))
				positions.emplace_back(i, j);
		}
	}
	return positions;
}

pair<vector<vector<char>>, map<char, int>> getNewState(const vector<vector<char>> &grille, map<char, int> pierresCapturees, const Vector2i& coupAJouer, const char joueur)
{
	pair<vector<vector<char>>, map<char, int>> result;
	map<char, int> scores(pierresCapturees);

	Plateau gob(Vector2i(size(grille), size(grille[0])));
	gob.terrain = grille;
	gob.terrainAvant = grille;
	gob.negrasComidas = pierresCapturees['B'];
	gob.blancasComidas = pierresCapturees['N'];
	gob.tour = joueur;

	gob.jouer(coupAJouer);

	scores['N'] = gob.blancasComidas;
	scores['B'] = gob.negrasComidas;

	result.first = gob.terrain;
	result.second = scores;
	
	return result;
}

// Fonction CalculCoupIA pour l'intelligence artificielle (IA) du jeu
// Cette fonction prend en entrée la grille de jeu actuelle (grille), un map des scores (scores) pour les pièces capturées,
// et le joueur actuel (joueur) pour lequel l'IA doit calculer le meilleur coup possible.

// Arguments : 
// - grille : une matrice représentant l'état actuel du jeu, où chaque case est soit vide, soit occupée par une pièce.
// - scores : un map qui associe à chaque type de pièce (B pour les pièces noires, N pour les pièces blanches)
//            le nombre de pièces capturées de ce type.
// - joueur : un caractère représentant le joueur pour lequel l'IA doit jouer, 
//            ici 'B' pour les noirs ou 'N' pour les blancs.

// Retourne : un objet Vector2i représentant les coordonnées du coup choisi par l'IA, 
//            qui est une paire (x, y) sur la grille. Si aucun coup n'est disponible, la fonction peut retourner (-1, -1).

Vector2i CalculCoupIA(const vector<vector<char>>& grille, map<char, int> scores, char joueur)
{
    // On commence par récupérer le nombre de pièces capturées par chaque joueur
    int noiresCapturees = scores['B'];  // Nombre de pièces noires capturées
    int blanchesCapturees = scores['N'];  // Nombre de pièces blanches capturées

    // À ce stade, il serait pertinent d'ajouter un code pour que l'IA puisse analyser la situation du jeu
    // et décider du meilleur coup à jouer. Cela pourrait inclure des stratégies basées sur les positions des pièces,
    // le nombre de pièces capturées, etc.

    // Exemple d'approche :
    // - L'IA pourrait rechercher une position qui lui permettrait de capturer une pièce de l'adversaire.
    // - Ou bien elle pourrait se concentrer sur la protection de ses propres pièces.
    // - L'IA pourrait aussi essayer de maximiser son score en capturant des pièces tout en évitant de perdre trop de pièces.

    // Si aucun coup n'est possible ou si la fonction n'est pas encore implémentée, nous pourrions renvoyer (-1, -1)
    // pour indiquer qu'aucun coup n'a été trouvé.

    // Ajoute ton code ici pour implémenter la logique de calcul du coup

    return Vector2i(-1, -1);  // Pour l'instant, nous retournons (-1, -1) par défaut (aucun coup trouvé)
}


#endif