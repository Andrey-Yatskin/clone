#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(600, 800), "SFML Works!");

	
	bool flag = false;

	bool move = true;


	float Y = 250;

	float H = 300;

	while (window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed)
				
				window.close();
		
			if (event.type == sf::Event::KeyPressed) {
				
				if (event.key.code == sf::Keyboard::Z)
					
					flag = true;
				
				if (event.key.code == sf::Keyboard::X)
					
					flag = false;
			}
		}
		
	
		if (flag) {

		
			if (Y < 100)
				
				move = false;
			
			if (Y > 250)
				
				move = true;

			
			if (move) {
				
				Y -= 0.25;
			
				H += 0.5;
			}
	
			else {
			
				Y += 0.25;
			
				H -= 0.5;
			}
		}

		// Очищаем окно
		window.clear();

		// Создаем прямоугольник размером 200хH
		RectangleShape rectangle(Vector2f(200.f, H));

		// Перемещаем его в (200, Y)
		rectangle.move(200, Y);

		// Устанавливаем ему цвет
		rectangle.setFillColor(Color::Red);

		// Отрисовка прямоугольника
		window.draw(rectangle);

		// Отрисовка окна	
		window.display();
	}

	// Завершить программу
	return 0;
}