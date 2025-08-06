#include <SFML/Graphics.hpp>
#include <cmath>
#include <optional> // Для std::optional

const int W = 800;
const int H = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode({W, H}), "Heart Graph");
    
    int x0 = W / 2;
    int y0 = H / 2;
    float scale = 20.0f;

    // Создаем вершины для сердечка
    sf::VertexArray heart(sf::PrimitiveType::LineStrip);
    
    const int points = 1000;
    for (int i = 0; i <= points; i++) {
        float t = 2 * M_PI * i / points;
        
        // Параметрические уравнения сердца
        float x = 16 * pow(sin(t), 3);
        float y = 13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t);
        
        // Создаем вершину
        sf::Vertex vertex;
        vertex.position = {x0 + x * scale, y0 - y * scale};
        vertex.color = sf::Color::Red;
        heart.append(vertex);
    }

    while (window.isOpen())
    {
        // Обработка событий (корректный способ для SFML 3.0)
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event && event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        
        // Рисуем оси координат
        sf::VertexArray axes(sf::PrimitiveType::Lines);
        
        // X ось
        axes.append({{0.f, static_cast<float>(y0)}, sf::Color::Black});
        axes.append({{static_cast<float>(W), static_cast<float>(y0)}, sf::Color::Black});
        
        // Y ось
        axes.append({{static_cast<float>(x0), 0.f}, sf::Color::Black});
        axes.append({{static_cast<float>(x0), static_cast<float>(H)}, sf::Color::Black});
        
        window.draw(axes);
        window.draw(heart);
        window.display();
    }

    return 0;
}