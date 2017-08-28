#include <iostream>
#include <stdint.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

using namespace boost;

int main() {
    asio::io_service io;
    asio::serial_port port(io);

    sf::RenderWindow window( sf::VideoMode(800,800,32), "SODAR");

    port.open("/dev/ttyUSB0");
    port.set_option(asio::serial_port_base::baud_rate(115200));

    uint8_t distances[180];

    uint8_t d;
    uint8_t a;

    uint8_t cycles = 0;

    while ( window.isOpen() ) {
        sf::Event event;
        while ( window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed )
                window.close();
        }
        asio::read(port, asio::buffer(&a, sizeof(uint8_t)));
        asio::read(port, asio::buffer(&d, sizeof(uint8_t)));
        if ( a >= 180 ){
            cycles++;
            continue;
        }
        distances[a] = (cycles * distances[a] + d) / (cycles + 1);

        window.clear();

        sf::RectangleShape* rect;
        for (int i = 0; i < 180; i++) {
            rect = new sf::RectangleShape( sf::Vector2f( 1, (int)distances[i] * 4)) ;
            rect->setRotation(i);
            rect->setPosition( sf::Vector2f(400,400) );
            window.draw(*rect);
            delete rect;
        }

        window.display();
    }

    port.close();
}
