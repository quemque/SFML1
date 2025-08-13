#include <SFML/Graphics.hpp>
#include <deque>
#include <random>
#include <optional>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int CELL_SIZE = 20;
constexpr int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
constexpr int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

enum Direction { Up, Down, Left, Right };

struct Segment {
    int x = 0, y = 0; // default constructor needed by some containers
    Segment(int x_, int y_) : x(x_), y(y_) {}
    Segment() = default; // explicit default constructor
};

class Game {
private:
    sf::RenderWindow window;
    std::deque<Segment> kitten; // snake body segments
    Direction dir;
    Segment fish;
    bool fishEaten;
    sf::RectangleShape kittenShape;
    sf::RectangleShape fishShape;

    std::mt19937 rng;

public:
    Game()
    : window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Kitten Fish Collector"),
      dir(Right), fishEaten(false), rng(std::random_device{}()) {

        window.setFramerateLimit(10);

        kitten.emplace_back(GRID_WIDTH / 2, GRID_HEIGHT / 2);
        kitten.emplace_back(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2);
        kitten.emplace_back(GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2);

        kittenShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        kittenShape.setFillColor(sf::Color::Yellow);

        fishShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        fishShape.setFillColor(sf::Color::Cyan);

        spawnFish();
    }

    void spawnFish() {
        std::uniform_int_distribution<int> distX(0, GRID_WIDTH - 1);
        std::uniform_int_distribution<int> distY(0, GRID_HEIGHT - 1);

        while (true) {
            int fx = distX(rng);
            int fy = distY(rng);

            bool conflict = false;
            for (auto& seg : kitten) {
                if (seg.x == fx && seg.y == fy) {
                    conflict = true;
                    break;
                }
            }
            if (!conflict) {
                fish = Segment(fx, fy);
                break;
            }
        }
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

    void handleEvents() {
        std::optional<sf::Event> event;
        while ((event = window.pollEvent())) {
            if (event->type == sf::Event::Closed)
                window.close();

            if (event->type == sf::Event::KeyPressed) {
                auto code = event->key.code;
                if (code == sf::Keyboard::Up && dir != Down) dir = Up;
                else if (code == sf::Keyboard::Down && dir != Up) dir = Down;
                else if (code == sf::Keyboard::Left && dir != Right) dir = Left;
                else if (code == sf::Keyboard::Right && dir != Left) dir = Right;
            }
        }
    }

    void update() {
        Segment newHead = kitten.front();
        switch (dir) {
            case Up: newHead.y -= 1; break;
            case Down: newHead.y += 1; break;
            case Left: newHead.x -= 1; break;
            case Right: newHead.x += 1; break;
        }

        if (newHead.x < 0 || newHead.x >= GRID_WIDTH || newHead.y < 0 || newHead.y >= GRID_HEIGHT) {
            resetGame();
            return;
        }

        for (auto& seg : kitten) {
            if (seg.x == newHead.x && seg.y == newHead.y) {
                resetGame();
                return;
            }
        }

        kitten.push_front(newHead);

        if (newHead.x == fish.x && newHead.y == fish.y) {
            fishEaten = true;
            spawnFish();
        }

        if (!fishEaten) {
            kitten.pop_back();
        } else {
            fishEaten = false;
        }
    }

    void render() {
        window.clear(sf::Color::Black);

        fishShape.setPosition(sf::Vector2f(fish.x * CELL_SIZE, fish.y * CELL_SIZE));
        window.draw(fishShape);

        for (auto& seg : kitten) {
            kittenShape.setPosition(sf::Vector2f(seg.x * CELL_SIZE, seg.y * CELL_SIZE));
            window.draw(kittenShape);
        }

        window.display();
    }

    void resetGame() {
        kitten.clear();
        dir = Right;
        kitten.emplace_back(GRID_WIDTH / 2, GRID_HEIGHT / 2);
        kitten.emplace_back(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2);
        kitten.emplace_back(GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2);
        spawnFish();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
