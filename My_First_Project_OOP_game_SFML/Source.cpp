#include<vector>
#include<string>
#include<map>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <list>
#include<Windows.h>
#include<iostream>
#include <vector>
using namespace sf;
using namespace std;
#include"Tank.h"

const int H = 1000;
const int W = 800;

class Bullet
{
protected:
	int direction = 0;
	float dx_bullet = 0;
	float dy_bullet = 0, x, y;
	bool life;
	Texture b;
	Sprite bb;
public:
	
	Bullet(){}	
	void sprite(float dxb, float dyb)
	{
		b.loadFromFile("C:\\Users\\linec\\Desktop\\fila\\bullets.PNG");
		bb.setTexture(b);
		bb.setTextureRect(IntRect(0, 0, 25, 25));
		bb.setScale(0.4, 0.4);
		bb.setPosition(dxb, dyb);
		dx_bullet = dxb;
		dy_bullet = dyb;
	}
	void clear(RenderWindow& window)
	{
		window.clear();
	}

	void draw(RenderWindow& window)
	{
		window.draw(bb);
	}
};
class Target
{
protected:
	float x = 0;
	float y = 0;
	Texture text;
	Sprite spr;
public:
	Target(){}
	void sprite_target(RenderWindow& window, string a, float dx, float dy)
	{
		text.loadFromFile(a);//вверх
		spr.setTexture(text);
		spr.setTextureRect(IntRect(0, 0, 50, 50));
		x = dx;
		y = dy;
		spr.setPosition(dx, dy);
		
		window.draw(spr);
	}
};
class Map
{
public:
	Map() {};
	void map1(RenderWindow& window)
	{
		RectangleShape rectangle1(Vector2f(2, 2));
		rectangle1.setFillColor(Color(115,134,120));

		rectangle1.setTextureRect(IntRect(0, 0, 2, 2));
		rectangle1.setPosition(0, 0);
		rectangle1.setSize(Vector2f(H, 10));
	

		RectangleShape rectangle2(Vector2f(2, 2));
		rectangle2.setFillColor (Color(115, 134, 120));
		rectangle2.setPosition(0, 0);
		rectangle2.setSize(Vector2f(10, W));

		RectangleShape rectangle3(Vector2f(2, 2));
		rectangle3.setFillColor(Color(115, 134, 120));
		rectangle3.setPosition(H - 10, 0);
		rectangle3.setSize(Vector2f(10, W));

		RectangleShape rectangle4(Vector2f(2, 2));
		rectangle4.setFillColor(Color(115, 134, 120));
		rectangle4.setPosition(0, W - 10);
		rectangle4.setSize(Vector2f(H, 10));
		window.draw(rectangle1);
		window.draw(rectangle2);
		window.draw(rectangle3);
		window.draw(rectangle4);

	}
};
class Tank_bot
{
protected:
	float dx_bot = 500, dy_bot = 500;
	Texture t_bot;
	Sprite s_bot;
public:
	Tank_bot() {}
	void Sprite_Tank(string a)
	{
		t_bot.loadFromFile(a);//вверх
		s_bot.setTexture(t_bot);
		s_bot.setTextureRect(IntRect(0, 0, 75, 75));
		s_bot.setPosition(dx_bot, dy_bot);
		s_bot.setScale(0.4, 0.4);
	}
	void Sprite_Tank_left(string a)
	{
		t_bot.loadFromFile(a);//вверх
		s_bot.setTexture(t_bot);
		s_bot.setTextureRect(IntRect(0 + 77, 0, -77, 75));
		s_bot.setPosition(dx_bot, dy_bot);
		s_bot.setScale(0.4, 0.4);
	}
	void Sprite_Tank_Down(string a)
	{
		t_bot.loadFromFile(a);//вверх
		s_bot.setTexture(t_bot);
		s_bot.setTextureRect(IntRect(0, 0 + 75, 75, -75));
		s_bot.setPosition(dx_bot, dy_bot);
		s_bot.setScale(0.4, 0.4);
	}
	void draw(RenderWindow& window)
	{
		window.draw(s_bot);
	}
	void animation(float x, float y, float height, float weight)
	{
		s_bot.setTextureRect(IntRect(x, y, height, weight));
	}
};

class Header_class_tank_player: public Tank, public Bullet, public Map, public Tank_bot
{
private:
	string up;
	float dyd_tank;
	float dxd_tank;
	float dxd_tank_bot;
	float dyd_tank_bot;
	float timer;
	int dlinapyli;
	int Sprite_tank_lenght;
	string right;
	float speedTank;
	float speedTank_bot;
	float speedBullet;
	int cnt;
	int cnt_bot1;
	int cnt_bot2;

	int rand_move;
	bool move_in_shoot;
	float acceleration;
public:
	Header_class_tank_player()
	{
		timer = 0;
		up= "C:\\Users\\linec\\Desktop\\fila\\up.png";
		right= "C:\\Users\\linec\\Desktop\\fila\\right.png";
		dyd_tank = 100;
		dxd_tank = 100;
		dxd_tank_bot = 500;
		dyd_tank_bot = 500;
		Tank::Sprite_Tank(up);
		Tank_bot::Sprite_Tank(up);
		rand_move = 0;
		dlinapyli = 4000;
		Sprite_tank_lenght = 44;
		speedTank = 0.1;
		speedTank_bot = 0.05;
		acceleration = 0.05;
		speedBullet = 0.6;
		move_in_shoot = false;
		cnt = 0;
		cnt_bot1 = 0;
		cnt_bot2 = 0;
	}
	void hit_the_wal()
	{
		if ((int)dy == W - Sprite_tank_lenght)
		{
			dy = W - Sprite_tank_lenght;
			dyd_tank = -((W - Sprite_tank_lenght) - 200);
		}
		if ((int)dx == H - Sprite_tank_lenght)
		{
			dx = H - 44;
			dxd_tank = -((H - Sprite_tank_lenght) - 200);
		}
		if ((int)dxd_tank == 188)
		{
			dx = 12;
			dxd_tank = 188;
		}
		if ((int)dyd_tank == 185)
		{
			dy = 13;
			dyd_tank = 185;
		}
		//cout << dyd_tank << endl;
	}
	void hit_the_wal_bot()
	{
		if ((int)dy_bot == W - Sprite_tank_lenght)
		{
			dy_bot = W - Sprite_tank_lenght;
			dyd_tank = -((W - Sprite_tank_lenght) - 200);
		}
		if ((int)dx_bot == H - Sprite_tank_lenght)
		{
			dx_bot = H - 44;
			dxd_tank_bot = -((H - Sprite_tank_lenght) - 200);
		}
		if ((int)dxd_tank_bot == 988)
		{
			dx_bot = 12;
			dxd_tank_bot = 988;

		}
		if ((int)dyd_tank_bot == 986)
		{
			dy_bot = 13;
			dyd_tank_bot = 986;
		}
		//cout << dyd_tank_bot << endl;

	}
	void Right(float speedTank_, bool move_in_shot_)
	{
		Tank::Sprite_Tank(right);
		dx += speedTank_;
		if (move_in_shot_ == true)
			cnt = 1;
		dxd_tank -= speedTank_;
	}
	void Left(float speedTank_, bool move_in_shot_)
	{
		Tank::Sprite_Tank_left(right);
		dx -= speedTank_;
		if (move_in_shot_ == true)
			cnt = 2;
		dxd_tank += speedTank_;
	}
	void Up(float speedTank_, bool move_in_shot_)
	{
		Tank::Sprite_Tank(up);
		dy -= speedTank_;
		if (move_in_shot_ == true)
			cnt = 3;
		dyd_tank += speedTank_;
	}
	void Down(float speedTank_, bool move_in_shot_)
	{
		Tank::Sprite_Tank_Down(up);
		dy += speedTank_;
		if (move_in_shot_ == true)
			cnt = 4;
		dyd_tank -= speedTank_;
	
	}
	void Shoot(RenderWindow & window)
	{
		switch (cnt)
		{
		case 1:	sprite(dx + 30, dy + 10); break;
		case 2: sprite(dx - 10, dy + 10); break;
		case 3: sprite(dx + 10, dy - 10);  break;
		case 4:sprite(dx + 10, dy + 30); break;
		default:
			break;
		}
		for (size_t i = 0; i < dlinapyli; i++)
		{
			switch (cnt)
			{
			case 1:bb.move(speedBullet, 0);
				dx_bullet += speedBullet;
				if (Keyboard::isKeyPressed(Keyboard::Right)) Right(speedTank+ acceleration,true);
				else if (Keyboard::isKeyPressed(Keyboard::Left)) Left(speedTank+ acceleration, false);
				else if (Keyboard::isKeyPressed(Keyboard::Up)) Up(speedTank+ acceleration, false);
				else if (Keyboard::isKeyPressed(Keyboard::Down)) Down(speedTank+ acceleration, false);
				break;
			case 2:bb.move(-speedBullet, 0); dx_bullet -= speedBullet;
				if (Keyboard::isKeyPressed(Keyboard::Left)) Left(speedTank+ acceleration, true);
				else if (Keyboard::isKeyPressed(Keyboard::Right)) Right(speedTank+ acceleration, false);
				else if (Keyboard::isKeyPressed(Keyboard::Up)) Up(speedTank + acceleration, false);
				else if (Keyboard::isKeyPressed(Keyboard::Down)) Down(speedTank + acceleration, false);
				break;
			case 3:bb.move(0, -speedBullet); dy_bullet -= speedBullet;
				if (Keyboard::isKeyPressed(Keyboard::Up)) Up(speedTank + acceleration,true);
				else if (Keyboard::isKeyPressed(Keyboard::Right)) Right(speedTank + acceleration, false);
				else if (Keyboard::isKeyPressed(Keyboard::Left)) Left(speedTank+ acceleration, false);
				else if (Keyboard::isKeyPressed(Keyboard::Down)) Down(speedTank + acceleration, false);
				break;
			case 4:bb.move(0, speedBullet); dy_bullet += speedBullet;
				if (Keyboard::isKeyPressed(Keyboard::Down)) Down(speedTank + acceleration,true);
				else if (Keyboard::isKeyPressed(Keyboard::Right)) Right(speedTank+ acceleration, false);
				else if (Keyboard::isKeyPressed(Keyboard::Left)) Left(speedTank+ acceleration, false);
				else if (Keyboard::isKeyPressed(Keyboard::Up)) Up(speedTank + acceleration, false);
				break;
			default:
				break;
			}
			hit_the_wal();
			if ((int)dy_bullet == W - 20+6)
				break;
			if ((int)dx_bullet == H - 20+6)
				break;
			if ((int)dx_bullet == 15-15)
				break;
			if ((int)dy_bullet == 15-15)
				break;
			move_bot1(window);

			window.clear();
			
			map1(window);
			Tank::draw(window);
			Tank_bot::draw(window);
			window.draw(bb);
			window.display(); 
		}
	}
	void movePlayer(RenderWindow& window)
	{
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			Right(speedTank+acceleration, true);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			Left(speedTank+acceleration, true);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			Up(speedTank+acceleration, true);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			Down(speedTank+acceleration,true);
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			Shoot(window);
		}
		hit_the_wal();
	}
	
	void shoot_bot()
	{
		switch (cnt_bot2)
		{
		case 1:	sprite(dx_bot + 30, dy_bot + 10); break;
		case 2: sprite(dx_bot - 10, dy_bot + 10); break;
		case 3: sprite(dx_bot + 10, dy_bot - 10);  break;
		case 4: sprite(dx_bot + 10, dy_bot + 30); break;
		default:
			break;
		}
	}
	void bot_eyes()
	{
		switch (cnt_bot1)
		{
		case 1: if ((int)dy == (int)dy_bot && (int)dx > (int)dx_bot) shoot_bot(); break;
		case 2: if ((int)dy == (int)dy_bot && (int)dx < (int)dx_bot) shoot_bot(); break;
		case 3: if ((int)dx == (int)dx_bot && (int)dy < (int)dy_bot) shoot_bot(); break;
		case 4: if ((int)dx == (int)dx_bot && (int)dy > (int)dy_bot) shoot_bot(); break;
		default:
			break;
		}
	}
	void move_bot1(RenderWindow& window)
	{
		if (timer == 750)
		{
			rand_move =2 ;//rand() % 5;
			timer = 0;
		}
		if (rand_move == 1)
		{
			Tank_bot::Sprite_Tank_Down(up);
			dy_bot += speedTank_bot;
			cnt_bot1 = 4;
			dyd_tank_bot -= speedTank_bot;
			cnt_bot2 = 4;
		}
		else if (rand_move == 2)
		{
			Tank_bot::Sprite_Tank(up);
			dy_bot -= speedTank_bot;
			cnt_bot1 = 3;
			dyd_tank_bot += speedTank_bot;
			cnt_bot2 = 3;
		}
		else if (rand_move == 3)
		{
			Tank_bot::Sprite_Tank_left(right);
			dx_bot -= speedTank_bot;
			cnt_bot1 = 2;
			dxd_tank_bot += speedTank_bot;
			cnt_bot2 = 2;
		}
		else if (rand_move == 4)
		{
			Tank_bot::Sprite_Tank(right);
			dx_bot += speedTank_bot;
			cnt_bot1 = 1;
			dxd_tank_bot -= speedTank_bot;
			cnt_bot2 = 1;
		}
		hit_the_wal_bot();
		bot_eyes();
		timer++;
	}
	void man_Up(RenderWindow& window)
	{
		srand(time(NULL));
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			movePlayer(window);
			move_bot1(window);
			window.clear();
			map1(window);
			
			//Bullet::draw(window);
			Tank::draw(window);
			Tank_bot::draw(window);
			
			window.display();
		}
	}
};


int main()
{
	RenderWindow window(VideoMode(H , W), "Myfirstrealproject");
	Header_class_tank_player h;
	h.man_Up(window);
}
