#include <iostream>
#include <Windows.h>
#include <time.h>
int main() 
{
	int scale = 20;
	float speed = 0.5;
	int target_fps = 1000;
	int speed_over_time = 0.5;

	int i;
	int ii;
	int v_res = (1*scale)*1;
	int h_res = (2*scale)*2;
	bool run = true;
	float d_speed =0;
	float ms = 0;
	float y = 7;
	float y1 = 7;
	clock_t start = 0;
	clock_t end = 0;
	bool empty = true;
	float wall_height1 = 5;
	float ball_x = h_res/2;
	float ball_y = v_res / 2;
	bool collision = true;
	float ball_speed_x =-0.5;
	float ball_speed_y= -0.5;
	float val_x = 0;
	float val_y = 0;
	float ball_speed = 25;
	int timer = 0;
	int score_left = 0;
	int score_right = 0;

	int rounds =0;
	std::cout << "how many rounds?\n(-1)=inf: ";
	std::cin >> rounds;
	

	std::cout << "ball speed over time?\ndefault(0): ";
	std::cin >> speed_over_time;

	if (speed_over_time <= 0) 
	{
		speed_over_time = 0.5;
	}
	while (run)
	{
		start = clock();
		if (score_left == rounds || score_right == rounds)
		{
			if (score_left > score_right)
			{
				system("cls");
				std::cout << "PLAYER (LEFT) WON!" << std::endl;
				_Thrd_sleep_for(1000);
				return 0;
				
			}

			if (score_left < score_right)
			{
				system("cls");
				std::cout << "PLAYER (RIGHT) WON!" << std::endl;
				_Thrd_sleep_for(1000);
				return 0;
			}
		}
		
		std::cout << "\x1b[H";
		std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
		//render
		for (ii = 0; ii < v_res; ii++)
		{
			for (i = 0; i < h_res; i++)
			{
				empty = true;
				if ((i == 0 && (ii >= y && ii < y + wall_height1)) || (i == h_res-1 && (ii >= y1 && ii < y1 + wall_height1)))
				{
					std::cout << "#";
					empty = false;
				}
				if ((i == static_cast<int>(round(ball_x)) && ii== static_cast<int>(round(ball_y))) && (static_cast<int>(round(ball_x)) > 0 && static_cast<int>(round(ball_x)) != h_res-1))
				{
					std::cout << "*";
					empty = false;
				}
				if(empty )
				{
					std::cout << " ";
				}
			}
			std::cout << "\n";
		}
		ball_x = ball_x + (ball_speed_x*d_speed);
		ball_y = ball_y + (ball_speed_y/2.0 * d_speed);
		if ((ball_x <= 1.0 && (ball_y >= y &&  ball_y < y+wall_height1) ||
            ball_x > h_res-2.0 && (ball_y >= y1 && ball_y < y1 + wall_height1)) && collision)
		{
			srand(time(0));
			val_x = (rand() % 50) + ball_speed;
			val_x = val_x / 100;
			if (ball_speed_x < 0.0)
			{
				ball_speed_x = val_x;
			}
			else
			{
				ball_speed_x = -val_x;
			}
			ball_speed = ball_speed + speed_over_time;
			collision = false;
		}
		if (collision==false) 
		{
			timer++;
			if (timer == 3) 
			{
				collision = true;
				timer = 0;
			}
		}
		if ((ball_y <= 0.0 ||
			ball_y > v_res - 1.0)&&collision )
		{
			srand(time(0));
			val_y = (rand() % 50) + ball_speed;
			val_y = val_y / 100;
			if (ball_speed_y < 0)
			{
				ball_speed_y = val_y;
			}
			else 
			{
				ball_speed_y = -val_y;
			}
			ball_speed = ball_speed + speed_over_time;
			collision = false;
		}

		if (ball_x >= h_res)
		{
			system("cls");
			score_left++;
			ball_x = h_res / 2;
			ball_y = v_res / 2;
			y = 7;
			y1 = 7;
			ball_speed_x = -0.5;
			ball_speed_y = -0.5;
			val_x = 0;
			val_y = 0;
			ball_speed = 25;
		}

		if (ball_x < -1.0) 
		{
			system("cls");
			score_right++;
			ball_x = h_res / 2;
			ball_y = v_res / 2;
			y = 7;
			y1 = 7;
			ball_speed_x = -0.5;
			ball_speed_y = -0.5;
			val_x = 0;
			val_y = 0;
			ball_speed = 25;
		}

		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{run = false;}
		if (GetKeyState('L') & 0x8000)
		{y1 = y1 + (0.5 * (speed * d_speed));}
		if (GetKeyState('O') & 0x8000)
		{y1= y1 - (0.5 * (speed * d_speed));}
		if (GetKeyState('W') & 0x8000)
		{y = y - (0.5* (speed * d_speed));}
		if (GetKeyState('S') & 0x8000)
		{y = y + (0.5 * (speed * d_speed));}
		if (GetKeyState(VK_SPACE) & 0x8000)
		{system("cls");}

		std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
		std::cout<<"                                      " << score_left << "-" << score_right << std::endl; //
		std::cout << "\n";
		//walls border-stop
		if (y+ wall_height1 > v_res)
		{y = (v_res - wall_height1);}
		if (y < 0.0)
		{y = 0;}
		if (y1 + wall_height1 > v_res)
		{y1 = (v_res - wall_height1);}
		if (y1 < 0.0)
		{y1 = 0;}
		d_speed = ms/20;

		

		_Thrd_sleep_for(1000/ target_fps);
		end = clock();
		ms = (float)(end - start);
	}
	return 0;
}
