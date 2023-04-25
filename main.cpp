#include <SFML/Graphics.hpp>
#include <cmath>
//https://youtu.be/hnR8s3XUnuw
using namespace sf;

const int W = 602;
const int H = 602;

int main()
{
	RenderWindow window(VideoMode(W, H), "Function graph!");

	int x0 = W / 2;
	int y0 = H / 2;

	CircleShape point(2.f);
	point.setFillColor(Color::Blue);

	int o1 = -10;
	int o2 = 10;
	float c = 100;
	int mass = ((o1) * (-1) + o2) * c + 1;
	int sc = 30;

	RectangleShape line[40];
	for (int i = 0; i < 40; i++) {
		line[i].setSize(Vector2f(1, 20));
		line[i].setFillColor(Color::Black);

		if (i < 20) {
			if (i < 10)
				line[i].setPosition(x0 - (i + 1) * sc, y0 - 10);
			else
				line[i].setPosition(x0 + (i - 9) * sc, y0 - 10);
		}
		else {
			line[i].setRotation(90);
			if (i < 30)
				line[i].setPosition(x0 + 10, y0 + (i - 30) * sc);
			else
				line[i].setPosition(x0 + 10, y0 + (i - 29) * sc);
		}
	}

	RectangleShape OsX(Vector2f(W, 1));
	OsX.setFillColor(Color::Black);
	OsX.setPosition(0, y0);

	RectangleShape OsY(Vector2f(1, H));
	OsY.setFillColor(Color::Black);
	OsY.setPosition(x0, 0);

	RectangleShape strel[4];
	for (int i = 0; i < 4; i++) {
		strel[i].setSize(Vector2f(1, 25));
		strel[i].setFillColor(Color::Black);

		if (i < 2)
			strel[i].setPosition(x0, 0);
		else
			strel[i].setPosition(W, y0);
	}
	strel[0].setRotation(25);
	strel[1].setRotation(-25);
	strel[2].setRotation(60);
	strel[3].setRotation(-250);

	int anim = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (anim < mass)
			anim += 5;

		window.clear(Color::White);
		window.draw(OsX);
		window.draw(OsY);
		for (int i = 0; i < 4; i++)
			window.draw(strel[i]);
		for (int i = 0; i < 40; i++)
			if (i != 19 && i != 20)
				window.draw(line[i]);
		for (int i = 0; i < anim; i++) {
			float x = o1 + i / c;
			//float y = x;
			float y = (x + 5) / (x * x + 1);

			float x1 = x0 + x * sc;
			float y1 = y0 - y * sc;

			point.setPosition(x1, y1);
			window.draw(point);
		}
		window.display();
	}

	return 0;
}