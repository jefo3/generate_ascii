#include <SFML/Graphics.hpp>
#include "../tinyfiledialogs.h"
#include <iostream>

using namespace std;

int main() {
  const string TITLE_WINDOW = "ASCII Generator";

  sf::RenderWindow window(sf::VideoMode({800, 600}), TITLE_WINDOW);
  sf::Texture texture(sf::Vector2u(200, 200));
  sf::Sprite sprite(texture);
  bool imageLoaded = false;
   
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (event->is<sf::Event::MouseButtonPressed>()) {
        // Abrir o diálogo de seleção de arquivos
        const char* filePath = tinyfd_openFileDialog(
            "Selecione uma imagem", // Título da janela
            "",                    // Caminho inicial
            1,                     // Número de filtros
            (const char*[]){ "*.png", "*.jpg", "*.jpeg", "*.bmp" }, // Filtros de imagem
            "Arquivos de Imagem",  // Descrição do filtro
            0                      // Permitir múltiplos arquivos
        );

        if (filePath) {
          std::cout << "Imagem selecionada: " << filePath << std::endl;

          if (texture.loadFromFile(filePath)) {
            
            sprite.setTexture(texture);

            // Ajustar escala
            float scaleX = static_cast<float>(window.getSize().x) / texture.getSize().x;
            float scaleY = static_cast<float>(window.getSize().y) / texture.getSize().y;
            
            sprite.setScale({min(scaleX, scaleY), min(scaleX, scaleY)});

            imageLoaded = true;
          } else {
            std::cout << "Erro ao carregar a imagem!" << std::endl;
            imageLoaded = false;
          }
        } else {
          std::cout << "Nenhuma imagem foi selecionada." << std::endl;
        }
      }      
    }

    window.clear(sf::Color::Black);
    if (imageLoaded) {
      window.draw(sprite);
    }
    window.display();
  }

  return 0;
}