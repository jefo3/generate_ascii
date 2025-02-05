#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
int main() {
  const string TITLE_WINDOW = "ASCII Generator";

  sf::RenderWindow window(sf::VideoMode({800, 600}), TITLE_WINDOW);

   
  while (window.isOpen()) {
   
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
          window.close();
    }

    window.clear();
    window.display();
  }

  return 0;
}