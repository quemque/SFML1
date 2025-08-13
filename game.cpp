#include <SFML/Graphics.hpp>
#include <cmath>

const int W = 602;
const int H = 602;

int main()
{
    // SFML 3.0 requires Vector2u for VideoMode
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(W), static_cast<unsigned int>(H)}), "Function Graph");

    int x0 = W / 2;
    int y0 = H / 2;

    sf::CircleShape point(2.f);
    point.setFillColor(sf::Color::Blue);

    int o1 = -10;
    int o2 = 10;
    float c = 100;
    int mass = ((o1) * (-1) + o2) * c + 1;
    int sc = 30;

    sf::RectangleShape line[40];
    for (int i = 0; i < 40; i++) {
        line[i].setSize(sf::Vector2f(1, 20));
        line[i].setFillColor(sf::Color::Black);

        if (i < 20) {
            if (i < 10)
                line[i].setPosition(sf::Vector2f(x0 - (i + 1) * sc, y0 - 10));
            else
                line[i].setPosition(sf::Vector2f(x0 + (i - 9) * sc, y0 - 10));
        }
        else {
            // SFML 3.0 uses sf::degrees for angles
            line[i].setRotation(sf::degrees(90.f));
            if (i < 30)
                line[i].setPosition(sf::Vector2f(x0 + 10, y0 + (i - 30) * sc));
            else
                line[i].setPosition(sf::Vector2f(x0 + 10, y0 + (i - 29) * sc));
        }
    }

    sf::RectangleShape OsX(sf::Vector2f(W, 1));
    OsX.setFillColor(sf::Color::Black);
    OsX.setPosition(sf::Vector2f(0.f, y0));

    sf::RectangleShape OsY(sf::Vector2f(1, H));
    OsY.setFillColor(sf::Color::Black);
    OsY.setPosition(sf::Vector2f(x0, 0.f));

    sf::RectangleShape strel[4];
    for (int i = 0; i < 4; i++) {
        strel[i].setSize(sf::Vector2f(1, 25));
        strel[i].setFillColor(sf::Color::Black);

        if (i < 2)
            strel[i].setPosition(sf::Vector2f(x0, 0.f));
        else
            strel[i].setPosition(sf::Vector2f(W, y0));
    }
    // SFML 3.0 angle specifications
    strel[0].setRotation(sf::degrees(25.f));
    strel[1].setRotation(sf::degrees(-25.f));
    strel[2].setRotation(sf::degrees(60.f));
    strel[3].setRotation(sf::degrees(-250.f));

    int anim = 0;

    while (window.isOpen())
    {
        // SFML 3.0 event handling
        while (std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (anim < mass)
            anim += 5;

        window.clear(sf::Color::White);
        window.draw(OsX);
        window.draw(OsY);
        for (int i = 0; i < 4; i++)
            window.draw(strel[i]);
        for (int i = 0; i < 40; i++)
            if (i != 19 && i != 20)
                window.draw(line[i]);
        for (int i = 0; i < anim; i++) {
            float x = o1 + i / c;
            float y = (x + 5) / (x * x + 1);

            float x1 = x0 + x * sc;
            float y1 = y0 - y * sc;

            point.setPosition(sf::Vector2f(x1, y1));
            window.draw(point);
        }
        window.display();
    }

    return 0;
}