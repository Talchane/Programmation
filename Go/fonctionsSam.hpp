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

#endif