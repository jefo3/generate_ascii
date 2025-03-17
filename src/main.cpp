#include <SFML/Graphics.hpp>
#include "../tinyfiledialogs.h"
#include <iostream>

using namespace std;

uint8_t calculate_average_gray(sf::Texture &texture, uint8_t x, uint8_t y) {
  uint8_t width = texture.getSize().x;
  uint8_t height = texture.getSize().y;
  uint8_t scale = 4;


  uint8_t sum = 0;
  uint8_t count = 0;

  
  

  return sum / count;
}

void convert_to_gray_scale(sf::Texture &texture) {
  unsigned int width = texture.getSize().x;
  unsigned int height = texture.getSize().y;
  sf::Image image = texture.copyToImage();

  for (unsigned int i = 0; i < width; i++) {
    for (unsigned int j = 0; j < height; j++) {
      
      sf::Color color = image.getPixel({i, j});
      
      uint8_t gray =(uint8_t) (color.r * 0.21 + color.g * 0.72 + color.b * 0.07);
      
      image.setPixel({i, j}, {gray, gray, gray, color.a});
    }
  }
  texture.update(image);
}

void generate_ascii_art(sf::Texture &texture, const string &characters) {
  unsigned int width = texture.getSize().x;
  unsigned int height = texture.getSize().y;
  
  sf::Image image = texture.copyToImage();

  for (unsigned int j = 0; j < height; j++) {
    for (unsigned int i = 0; i < width; i++) {
      sf::Color color = image.getPixel({i, j});
      unsigned int index = (color.r * (characters.size() - 1)) / 255;
      char character = characters[index];
      std::cout << character;
    }
    std::cout << std::endl;
  }
}

int main() {
  const string TITLE_WINDOW = "ASCII Generator";
  const string CHARACTERS_ASCII = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

  sf::RenderWindow window(sf::VideoMode({1024, 1024}), TITLE_WINDOW);
  sf::Texture texture(sf::Vector2u(800, 600));
  sf::Sprite sprite(texture);
  

  
  bool imageLoaded = false;
   
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (event->is<sf::Event::MouseButtonPressed>()) {
        
        const char* filePath = tinyfd_openFileDialog(
            "Selecione uma imagem", 
            "",                    
            1,                     
            (const char*[]){ "*.png", "*.jpg", "*.jpeg", "*.bmp" }, 
            "Arquivos de Imagem",  
            0                     
        );

        if (filePath) {
          std::cout << "Imagem selecionada: " << filePath << std::endl;

          if (texture.loadFromFile(filePath)) {
            
            texture.setSmooth(true);
            sprite.setTexture(texture);
           
            convert_to_gray_scale(texture); 
        
            generate_ascii_art(texture, CHARACTERS_ASCII);

            
            // // Ajustar escala
            // float scaleX = static_cast<float>(window.getSize().x) / texture.getSize().x;
            // float scaleY = static_cast<float>(window.getSize().y) / texture.getSize().y;
            
            // sprite.setScale({min(scaleX, scaleY), min(scaleX, scaleY)});
            // sprite.setColor(sf::Color::White);
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