#ifndef ACTU_HPP
#define ACTU_HPP

void actu(Vector2i posAct)
{
	bool ko(false);
	Vector2i posKo;
	int nbCaptures(0);

	// Suppression ancien ko
	for (int i = 0; i < terrain.size(); ++i)
	{
		for (int j = 0; j < terrain[i].size(); ++j)
		{
			if (terrain[i][j] == 'K')
			{
				terrain[i][j] = 'X';
				cercles[i][j].setOutlineColor(Color::Transparent);
			}
		}
	}

	// Check les captures de pierres
	for (int i = 0; i < terrain.size(); ++i)
		for (int j = 0; j < terrain[i].size(); ++j)
			if (terrain[i][j] == tour && isCaptured(i, j))
 				nbCaptures++;

	for (int i = 0; i < terrain.size(); ++i)
	{
		for (int j = 0; j < terrain[i].size(); ++j)
		{
			if (terrain[i][j] == tour && isCaptured(i, j))
			{
				vector<vector<bool>> visited(terrain.size(), vector<bool>(terrain[0].size(), false));
				removeStones(i, j, terrain[i][j], visited);
				posKo = Vector2i(i, j);
			}
		}
	}
	scoreTexts.setString("Noir :\t" + to_string(blancasComidas) + "\nBlanc :\t" + to_string(negrasComidas));




	ko = nbCaptures == 1;	// Ko potentiellement possible ?
	
	if (!ko) 	// Ko impossible
	{
		cout << "Ko impossible" << endl;
		terrainAvant = terrain;
		return;
	}

	vector<vector<char>> bkpTerrain(terrain);
	terrain[posKo.x][posKo.y] = tour;

	// Check les captures de pierres
	for (int i = 0; i < terrain.size(); ++i)
	{
		for (int j = 0; j < terrain[i].size(); ++j)
		{
			if (terrain[i][j] == bkpTerrain[posAct.x][posAct.y] && isCaptured(i, j))
			{
				vector<vector<bool>> visited(terrain.size(), vector<bool>(terrain[0].size(), false));
				removeStones(i, j, terrain[i][j], visited, false);
			}
		}
	}

	ko = (terrain == terrainAvant);	// On regarde si on a un ko
	terrain = bkpTerrain;


	if (ko)
	{
		cout << "Ko : " << posKo.x << " | " << posKo.y << endl;
		terrain[posKo.x][posKo.y] = 'K';
		cercles[posKo.x][posKo.y].setFillColor(Color::Transparent);
		cercles[posKo.x][posKo.y].setOutlineColor(Color(0, 0, 0));
	}
	else
	{
		
	}
	terrainAvant = bkpTerrain;
}

bool isCaptured(int x, int y)
{
	char color { terrain[x][y] };
	vector<vector<bool>> visited(size(terrain), vector<bool>(size(terrain[0]), false));

	return !hasLiberty(x, y, color, visited);
}

bool hasLiberty(int x, int y, char color, vector<vector<bool>>& visited)
{
	if (x < 0 || y < 0 || x >= terrain.size() || y >= terrain[0].size())
		return false;
	if (terrain[x][y] == 'X' || terrain[x][y] == 'K')
		return true;	// La pierre a une liberté
	
	if (terrain[x][y] != color)
		return false;
	if (visited[x][y])
		return false;

	visited[x][y] = true;

	return	hasLiberty(x + 1, y, color, visited) ||
			hasLiberty(x - 1, y, color, visited) ||
			hasLiberty(x, y + 1, color, visited) ||
			hasLiberty(x, y - 1, color, visited);
}

void removeStones(int x, int y, char color, vector<vector<bool>>& visited, bool changerGraphique = true)
{
	if (x < 0 || y < 0 || x >= terrain.size() || y >= terrain[0].size())
		return;

	if (terrain[x][y] != color || visited[x][y])
		return;

	visited[x][y] = true;
	terrain[x][y] = 'X';
	if (changerGraphique)
	{
		cercles[x][y].setFillColor(Color::Transparent);
		cercles[x][y].setOutlineColor(Color::Transparent);
	}

	
	// Mettre à jour le score
	if (color == 'B')
		negrasComidas++;
	else if (color == 'N')
		blancasComidas++;

	removeStones(x + 1, y, color, visited, changerGraphique);
	removeStones(x - 1, y, color, visited, changerGraphique);
	removeStones(x, y + 1, color, visited, changerGraphique);
	removeStones(x, y - 1, color, visited, changerGraphique);
}
bool hasCapture(const Vector2i& pos)
{
    char color = tour;
    char opponentColor = (color == 'B') ? 'N' : 'B';

    vector<vector<bool>> visited(terrain.size(), vector<bool>(terrain[0].size(), false));

    if (pos.x + 1 < terrain.size() && terrain[pos.x + 1][pos.y] == opponentColor)
        if (!hasLiberty(pos.x + 1, pos.y, opponentColor, visited))
            return true;

	fill(visited.begin(), visited.end(), vector<bool>(terrain[0].size(), false));
    if (pos.x - 1 >= 0 && terrain[pos.x - 1][pos.y] == opponentColor)
        if (!hasLiberty(pos.x - 1, pos.y, opponentColor, visited))
            return true;

	fill(visited.begin(), visited.end(), vector<bool>(terrain[0].size(), false));
    if (pos.y + 1 < terrain[0].size() && terrain[pos.x][pos.y + 1] == opponentColor)
        if (!hasLiberty(pos.x, pos.y + 1, opponentColor, visited))
            return true;


	fill(visited.begin(), visited.end(), vector<bool>(terrain[0].size(), false));
    if (pos.y - 1 >= 0 && terrain[pos.x][pos.y - 1] == opponentColor)
        if (!hasLiberty(pos.x, pos.y - 1, opponentColor, visited))
            return true;

    // Aucun groupe adverse sans liberté autour de la pierre
    return false;
}

bool isSuicide(const Vector2i& pos)
{
    char color = tour;

    terrain[pos.x][pos.y] = color;

    vector<vector<bool>> visited(terrain.size(), vector<bool>(terrain[0].size(), false));
    bool hasLib = hasLiberty(pos.x, pos.y, color, visited);
    bool captured = hasCapture(pos);
    terrain[pos.x][pos.y] = 'X';

    return !hasLib && !captured;
}

#endif