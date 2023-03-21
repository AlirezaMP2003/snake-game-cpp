#include<iostream>
#include<conio.h>
using namespace std;

const int mapWidth = 20;
const int mapHeight = 20;
const int mapSize = mapWidth * mapHeight;

int Level;

int map[mapSize];

int headXposition , headYposition , direction;

int food = 4;

bool running;

// declaration
void selectLevel();
void run();
void initMap();
void generateFood();
void changeDirection(char key);
void update();
void move(int dx , int dy);
void clearScreen();
void printMap();
char getMapValue(int value);

int main(){
	
	selectLevel();
	
	run();
	
	return 0;
}

void selectLevel(){
	
	cout << "\t\t\t\tSnake Game" << endl << endl;
	cout << "\tSelect the level : " << endl << endl;
	cout << "\t1_ Hard" << endl;
	cout << "\t2_ Intermediate" << endl;
	cout << "\t3_ Easy" << endl << endl;
	
	cout << "\tYour selection :    ";
	cin >> Level;
	
	clearScreen();
	
}

void run(){
	
	initMap();
	running = true;
	
	while(running){
		
		if(kbhit()){
			changeDirection(getch());
		}
		
		update();
		clearScreen();
		printMap();
		
		switch(Level){
			case 1:
				_sleep(100);break;
			case 2:
				_sleep(300);break;
			case 3:
				_sleep(600);break;
			default :
				_sleep(400);break;
		}
		
	}
	
	cout << "\t\tGame Over!" << endl << "\t\tYour score is: " << food;
    cin.ignore();
	
}

void initMap(){
	
	headXposition = mapWidth / 2;
	headYposition = mapHeight / 2;
	map[headXposition + headYposition * mapWidth] = 1;
	
	for (int i = 0; i < mapWidth; ++i) {
        map[i] = -1;
        map[i + (mapHeight - 1) * mapWidth] = -1;
    }
    
    for (int j = 0; j < mapHeight; j++) {
        map[0 + j * mapWidth] = -1;
        map[(mapWidth - 1) + j * mapWidth] = -1;
    }
    
    generateFood();
	
}

// making food for snake
void generateFood(){
	
	int x , y = 0;
	
	do{
		
		x = rand() % (mapWidth - 2) + 1;
		y = rand() % (mapHeight - 2) + 1;
		
	}while(map[x + y * mapWidth] != 0);
	
	map[x + y * mapWidth] = -2;
	
}

// 	'w'
//  'a'     'd'
// 	's'
void changeDirection(char key){
	
	switch(key){
		
		case 'w':
			if(direction != 2) direction = 0;break;
		case 'd':
			if(direction != 3) direction = 1;break;
		case 's':
			if(direction != 4) direction = 2;break;
		case 'a':
			if(direction != 5) direction = 3;break;
		
	}
	
}

void update(){
	
	switch(direction){
		
		case 0:
			move(-1 , 0);break;
		case 1:
			move(0 , 1);break;
		case 2:
			move(1 , 0);break;
		case 3:
			move(0 , -1);break;
		
	}
	
	for (int i = 0; i < mapSize; i++) {
        if (map[i] > 0) map[i]--;
    }
	
}

void move(int dx , int dy){
	
	int newX = headXposition + dx;
    int newY = headYposition + dy;
    
    if (map[newX + newY * mapWidth] == -2) {
    	
        food++;

        generateFood();
        
    }

    else if (map[newX + newY * mapWidth] != 0) {
        running = false;
    }

    headXposition = newX;
    headYposition = newY;
    map[headXposition + headYposition * mapWidth] = food + 1;
	
}

void clearScreen(){
	system("cls");
}

void printMap(){
	
	for (int i = 0; i < mapWidth; ++i) {
        for (int j = 0; j < mapHeight; ++j) {
        	
            cout << getMapValue(map[i + j * mapWidth]);
            
        }
        cout << endl;
    }
	
}

// creating wall with 'X' character and body of snake with 'O' character.
char getMapValue(int value){
	
	if (value > 0) return 'o';

    switch (value) {
        // Return wall
    	case -1: return 'X';
        // Return food
    	case -2: return 'O';
    }
	
}



