#include <SFML/Graphics.hpp>

#include<vector>
#include<random>

auto spawnNew(std::vector<std::vector<int>>& grid)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 4);
    int randomx = dist6(rng);
    int randomy = dist6(rng);

    grid[randomx][randomy] = 1;
}

auto moveBoardLeft(std::vector<std::vector<int>>& grid) -> void
{
    for (int i = 0; i < grid.size(); i++)
    {
        int position = 0;
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] != 0)
            {
                grid[i][position] = grid[i][j];
                if (position != j)
                    grid[i][j] = 0;
                position++;
            }
        }

        for (int j = 0; j < grid[i].size() - 1; j++)
        {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j + 1])
            {
                grid[i][j] *= 2;
                grid[i][j + 1] = 0;
                j++;
            }
        }

        position = 0;
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] != 0)
            {
                grid[i][position] = grid[i][j];
                if (position != j)
                    grid[i][j] = 0;
                position++;
            }
        }
    }

    spawnNew(grid);
}

auto moveBoardDown(std::vector<std::vector<int>>& grid) -> void
{
    for (int j = 0; j < grid[0].size(); j++)
    {
        int position = grid.size() - 1;
        for (int i = grid.size() - 1; i >= 0; i--)
        {
            if (grid[i][j] != 0)
            {
                grid[position][j] = grid[i][j];
                if (position != i)
                    grid[i][j] = 0;
                position--;
            }
        }

        for (int i = grid.size() - 1; i > 0; i--)
        {
            if (grid[i][j] != 0 && grid[i][j] == grid[i - 1][j])
            {
                grid[i][j] *= 2;
                grid[i - 1][j] = 0;
                i--;
            }
        }

        position = grid.size() - 1;
        for (int i = grid.size() - 1; i >= 0; i--)
        {
            if (grid[i][j] != 0)
            {
                grid[position][j] = grid[i][j];
                if (position != i)
                    grid[i][j] = 0;
                position--;
            }
        }
    }

    spawnNew(grid);
}

auto moveBoardRight(std::vector<std::vector<int>>& grid) -> void
{
    for (int i = 0; i < grid.size(); i++)
    {
        int position = grid[i].size() - 1;
        for (int j = grid[i].size() - 1; j >= 0; j--)
        {
            if (grid[i][j] != 0)
            {
                grid[i][position] = grid[i][j];
                if (position != j)
                    grid[i][j] = 0;
                position--;
            }
        }

        for (int j = grid[i].size() - 1; j > 0; j--)
        {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j - 1])
            {
                grid[i][j] *= 2;
                grid[i][j - 1] = 0;
                j--;
            }
        }

        position = grid[i].size() - 1;
        for (int j = grid[i].size() - 1; j >= 0; j--)
        {
            if (grid[i][j] != 0)
            {
                grid[i][position] = grid[i][j];
                if (position != j)
                    grid[i][j] = 0;
                position--;
            }
        }
    }

    spawnNew(grid);
}

auto moveBoardUp(std::vector<std::vector<int>>& grid) -> void
{
    for (int j = 0; j < grid[0].size(); j++)
    {
        int position = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            if (grid[i][j] != 0)
            {
                grid[position][j] = grid[i][j];
                if (position != i)
                    grid[i][j] = 0;
                position++;
            }
        }

        for (int i = 0; i < grid.size() - 1; i++)
        {
            if (grid[i][j] != 0 && grid[i][j] == grid[i + 1][j])
            {
                grid[i][j] *= 2;
                grid[i + 1][j] = 0;
            }
        }

        position = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            if (grid[i][j] != 0)
            {
                grid[position][j] = grid[i][j];
                if (position != i)
                    grid[i][j] = 0;
                position++;
            }
        }
    }

    spawnNew(grid);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

    // if 0 nothing there, otherwise number is the value on the square. 5 x 5 grid
    std::vector<std::vector<int>> grid{
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // first we need to have a random position for the first 1 to spawn.
    spawnNew(grid);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                {
                    moveBoardLeft(grid);
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    moveBoardDown(grid);
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    moveBoardRight(grid);
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    moveBoardUp(grid);
                }
            }
        }

        window.clear();

        /*
0 is white.
1 is red.
2 is orange.
4 is blue
8 is green
16 is black
32 is pink
64 is brown
128 is yellow
*/

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                // now we need to map the i and j to x and y.
                // i is the y. every i or j is 100 px.
                sf::RectangleShape r(sf::Vector2f(100, 100));
                switch (grid[i][j])
                {
                case 0:
                    r.setFillColor(sf::Color::White);
                    break;
                case 1:
                    r.setFillColor(sf::Color::Red);
                    break;
                case 2:
                    r.setFillColor(sf::Color::Red);
                    break;
                case 4:
                    r.setFillColor(sf::Color::Blue);
                    break;
                case 8:
                    r.setFillColor(sf::Color::Green);
                    break;
                case 16:
                    r.setFillColor(sf::Color::Black);
                    break;
                case 32:
                    r.setFillColor(sf::Color(255, 192, 203));
                    break;
                case 64:
                    r.setFillColor(sf::Color(150, 75, 0));
                    break;
                case 128:
                    r.setFillColor(sf::Color::Yellow);
                    break;
                }
                r.setPosition(j * 100, i * 100);
                window.draw(r);
            }
        }

        window.display();
    }

    return 0;
}