#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define radCircles 22

class Plateau :public Drawable
{
public:
	Plateau(const Vector2i& dims) : tour('N'), blancasComidas(0), negrasComidas(0), posInit(60, 60), ghostCircle(radCircles)
	{
		for (int i = 0; i < dims.x; ++i)
		{
			grilleVerticale.emplace_back(Vector2f(3, (radCircles + 2) * 2 * (dims.y-1)));
			grilleVerticale.back().setPosition(posInit + Vector2f((radCircles + 2) * 2 * i, 0) + Vector2f(radCircles - 1, radCircles - 1));
			grilleVerticale.back().setFillColor(Color(0, 0, 0));
		}
		for (int i = 0; i < dims.y; ++i)
		{
			terrain.emplace_back();
			terrainAvant.emplace_back();
			cercles.emplace_back();
			
			grilleHorizontale.emplace_back(Vector2f((radCircles + 2) * 2 * (dims.x-1), 3));
			grilleHorizontale.back().setPosition(posInit + Vector2f(0, (radCircles + 2) * 2 * i) + Vector2f(radCircles - 1, radCircles - 1));
			grilleHorizontale.back().setFillColor(Color(0, 0, 0));

			for (int j = 0; j < dims.x; ++j)
			{
				terrain[i].push_back('X');
				terrainAvant[i].push_back('X');
				cercles[i].emplace_back(radCircles);
				cercles[i][j].setPosition(posInit + Vector2f(i * (radCircles+2) * 2, j * (radCircles+2) * 2));
				cercles[i][j].setFillColor(Color::Transparent);
				cercles[i][j].setOutlineThickness(-2);
				cercles[i][j].setOutlineColor(Color::Transparent);
			}
		}
		ghostCircle.setFillColor(Color(50, 50, 50, 180));
	}

	void jouer(const Vector2i& pos)
	{
        if (pos.x < 0 || pos.y < 0 || pos.x >= size(terrain) || pos.y >= size(terrain[0]))
        {
        	cerr << "Coup hors terrain" << endl;
            return;
        }

		else if (terrain[pos.x][pos.y] == 'K')	// KO
		{
			cerr << "Coup impossible : KO" << endl;
			return;
		}
		else if (terrain[pos.x][pos.y] != 'X')	// Case occupée
		{
			cerr << "Case occupée : " << terrain[pos.x][pos.y] << endl;
			return;
		}
		else
		{
			if (isSuicide(pos))	// Suicide
			{
				cerr << "Suicide" << endl;
				return;
			}
			else // Coup valide
			{
				if (tour == 'B')
				{
					terrain[pos.x][pos.y] = 'B';
					cercles[pos.x][pos.y].setFillColor(Color(255, 255, 255));
					cercles[pos.x][pos.y].setOutlineColor(Color(0, 0, 0));
					tour = 'N';
				}
				else if (tour == 'N')
				{
					terrain[pos.x][pos.y] = 'N';
					cercles[pos.x][pos.y].setFillColor(Color(50, 50, 50));
					cercles[pos.x][pos.y].setOutlineColor(Color(0, 0, 0));
					tour = 'B';
				}
			}
		}
		actu(pos);
	}

	void showGhost(const Vector2i pos)
    {
        if (pos.x < 0 || pos.y < 0 || pos.x >= size(terrain) || pos.y >= size(terrain[0]))
        {
            ghostCircle.setPosition(Vector2f(-100, -100));
            return;
        }
        if (terrain[pos.x][pos.y] != 'X')
        	return;

        if (isSuicide(pos))
        {
            ghostCircle.setFillColor(Color(255, 0, 0, 180));
        }
        else
        {
            if (tour == 'B')
                ghostCircle.setFillColor(Color(255, 255, 255, 180));
            else
                ghostCircle.setFillColor(Color(50, 50, 50, 180));
        }

        ghostCircle.setPosition(posInit + Vector2f(pos.x * (radCircles + 2) * 2, pos.y * (radCircles + 2) * 2));
    }

	vector<vector<char>> terrain;
	char tour;

	int blancasComidas;
	int negrasComidas;

private:
	vector<vector<CircleShape>>	cercles;
	vector<RectangleShape> grilleVerticale;
	vector<RectangleShape> grilleHorizontale;

	vector<vector<char>> terrainAvant;
	Vector2i coupPrecedent;

	CircleShape ghostCircle;
	Vector2f posInit;

	#include "actu.hpp"

	virtual void draw(RenderTarget &target, RenderStates states) const
	{
		for (int i = 0; i < size(grilleVerticale); ++i)
			target.draw(grilleVerticale[i]);
		for (int i = 0; i < size(grilleHorizontale); ++i)
			target.draw(grilleHorizontale[i]);

		target.draw(ghostCircle);

		for (int i = 0; i < size(cercles); ++i)
		{
			for (int j = 0; j < size(cercles[i]); ++j)
			{
				target.draw(cercles[i][j]);
			}
		}
	}
};

int main()
{
	RenderWindow window(VideoMode(1024, 768), "Go");
	Event event;

	Plateau goban(Vector2i(13, 13));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			Vector2i pos((Mouse::getPosition(window) - (Vector2i)Vector2f(60, 60)) / ((radCircles + 2) * 2));
			
			if (event.type == Event::Closed)
				window.close();
			
			if (event.type == Event::MouseMoved)
			{
				goban.showGhost(pos);
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					goban.jouer(pos);
				}
			}
		}

		window.clear(Color(200, 200, 255));
		window.draw(goban);
		window.display();
	}

	return (0);
}