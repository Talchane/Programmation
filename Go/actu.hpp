#ifndef ACTU_HPP
#define ACTU_HPP

void actu(Vector2i posAct)
{
	// Check les captures de pierres
	for (int i = 0; i < terrain.size(); ++i)
	{
		for (int j = 0; j < terrain[i].size(); ++j)
		{
			if (terrain[i][j] != 'X' && isCaptured(i, j))
			{
				vector<vector<bool>> visited(terrain.size(), vector<bool>(terrain[0].size(), false));
				removeStones(i, j, terrain[i][j], visited);
			}
		}
	}

	vector<vector<char>> tmpTerrain(terrain);
	tmpTerrain[dernierCoup.x][dernierCoup.y] = tour

	// Check les captures de pierres
	for (int i = 0; i < tmpTerrain.size(); ++i)
	{
		for (int j = 0; j < tmpTerrain[i].size(); ++j)
		{
			if (tmpTerrain[i][j] != 'X' && isCaptured(i, j))
			{
				vector<vector<bool>> visited(tmpTerrain.size(), vector<bool>(tmpTerrain[0].size(), false));
				removeStones(i, j, tmpTerrain[i][j], visited);
			}
		}
	}

	bool ko(tmpTerrain == terrainAvant);

	if (ko)
	{
		
	}
	else
	{

	}
	terrainAvant = terrain;
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
	if (terrain[x][y] == 'X')
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

void removeStones(int x, int y, char color, vector<vector<bool>>& visited)
{
	if (x < 0 || y < 0 || x >= terrain.size() || y >= terrain[0].size())
		return;

	if (terrain[x][y] != color || visited[x][y])
		return;
	if (visited[x][y])
		return;

	visited[x][y] = true;
	terrain[x][y] = 'X';
	cercles[x][y].setFillColor(Color::Transparent);

	
	// Mettre à jour le score
	if (color == 'B')
		negrasComidas++;
	else if (color == 'N')
		blancasComidas++;

	removeStones(x + 1, y, color, visited);
	removeStones(x - 1, y, color, visited);
	removeStones(x, y + 1, color, visited);
	removeStones(x, y - 1, color, visited);
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

    cout << "lib : " << hasLib << "\nmange : " << captured << endl;

    return !hasLib && !captured;
}

#endif