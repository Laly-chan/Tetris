#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<fstream>

#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27
#define enter 13

using namespace std;

class Bloque{
	private:
		int tipo, x, y;
		int tamanio[3][3], xpos, ypos;
		int barra[4][4];
	public:
		Bloque(int);
		~Bloque();
		void llenar();
		void posicion();
		void caer();
		void mover();
		void girar();
		void establecer();
		void parar();
		void siguiente();
		bool comperder();
};

Bloque::Bloque(int _tipo){
	tipo = _tipo;
}

Bloque::~Bloque(){}

void gotoxy(int, int);
void apretartecla();
void menu();
void selectmode();
void selectlevel();
void hiscoremenu();

void bordes();
void drawtetris();
void drawtexto();
void drawactual();
void drawscoremenu();

void llenarnivelvacio();
void mostrarnivel();

void borrarfila(int);
void comprobarfila();
void aniborrar(int);
void levelup();

void perder();
void aniperder();
void ganar();
void pausar();

void insertarnombre();
void mostrarseleccion(int, int, int);

void savescore(string);
void loadscore();
void creartabla();
void llenartabla();

int random(long);
void sumarseed();

void okuu();
bool compeasteregg();
void easteregg();
void leerokuu();
void imprimirokuu();

int i, j;
long seed = 0;
int nivel[26][25];
char tecla;
int falltime;
int contb, tipbl, nxtipbl;
char modgam;
int lvl, lines, combo;
int cantbl[7];
int opc;
int sumfall;
long scr;
char hiscr[14] = {'0','1','0','0','0','0','*','R','e','i','m','u',' '};
char shiscr[14] = {'0','0','7','5','0','0','*','M','a','r','i','s','a'};
char thiscr[14] = {'0','0','5','0','0','0','*','S','a','k','u','y','a'};
char tablacaracteres[4][19];
char newnombre[7] = {'_','_','_','_','_','_'};
char lwrnewnombre[6];
string compload = "1";
int asd, asda, asdas;
char dibujo[30][80];

int main(){
	system("mode con: cols=80 lines=25");
	Bloque block[7] = {Bloque(1), Bloque(2), Bloque(3), Bloque(4), Bloque(5), Bloque(6), Bloque(7)};
	creartabla();
	llenartabla();
	
	do {
		lvl = 0, falltime = 0, nxtipbl = rand()%7, contb = 0, tecla = left, lines = 0, scr = 0, sumfall = 0, combo = 1;
		for (i = 0; i < 7; i++){
			cantbl[i] = 0;
		}
		bordes();
		loadscore();
		
		menu();
		
		if (opc == 1){
			
			tecla = left;
			
			while (tecla != enter){
				selectmode();
				if (tecla != esc){
					selectlevel();
				} else {
					break;
				}
			}
			
			if (tecla != esc){
				drawtetris();
				drawtexto();
				llenarnivelvacio();
				if (modgam == 'B'){
					lines = 25;
				}
			}
			gotoxy(0,0);
			while (opc != 4 && tecla != esc){
				if (contb == 1){
					block[tipbl].caer();
				} else {
					combo = 1;
					mostrarnivel();
					tipbl = nxtipbl;
					block[tipbl].llenar();
					block[tipbl].establecer();
					contb = 1;
					nxtipbl = random(seed);
					block[nxtipbl].llenar();
					block[nxtipbl].siguiente();
					drawactual();
				}
				
				mostrarnivel();
				levelup();
				
				tecla = up;
				apretartecla();
				
				pausar();
				
				block[tipbl].mover();
				block[tipbl].girar();
				
				if (block[tipbl].comperder()){
					Sleep(1000);
					aniperder();
					tecla = 'r';
					Sleep(2000);
					perder();
					tecla = 'r';
					break;
				}
				if (lines == 0 && modgam == 'B'){
					Sleep(1000);
					tecla = 'r';
					ganar();
					tecla = 'r';
					break;
				}
				sumarseed();
			}
		}
		if (opc == 2){
			hiscoremenu();
		}
		system("cls");
		for (i = 0; i < 6; i++){
			newnombre[i] = '_';
			lwrnewnombre[i] = '_';
		}
	} while (opc != 3);
	
	return 0;
}

int random(long _seed){
	int ret;
	ret = (rand() * _seed + rand())%14;
	if (ret >= 7){
		ret -= 7;
	}
	return ret;
}

void gotoxy(int x1, int y1){
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.Y = y1;
	dwPos.X = x1;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

void bordes(){
	for(int i = 16; i < 66; i++){
		if (i != 50 && i != 28){
			gotoxy(i,0); printf("%c",205);
			gotoxy(i,24); printf("%c",205);
			
			if (i > 51 && i < 65){
				gotoxy(i,1); printf("%c",205);
				gotoxy(i,12); printf("%c",205);
				if (i > 55 && i < 61){
					gotoxy(i,3); printf("%c",205);
				}
			}
		}
		if (i < 28){
			gotoxy(i,3); printf("%c",205);
		}
	}
	for (int i = 1; i < 24; i++){
		if (i != 3){
			gotoxy(28,i); printf("%c",186);
			gotoxy(15,i); printf("%c",186);
		}
		gotoxy(66,i); printf("%c",186);
		gotoxy(50,i); printf("%c",186);
		
		if (i == 2){
			gotoxy(55,i); printf("%c",186);
			gotoxy(61,i); printf("%c",186);
		}
		
		if(i > 1 && i < 12){
			gotoxy(51,i); printf("%c",186);
			gotoxy(65,i); printf("%c",186);
		}
	}
	gotoxy(15,0); printf("%c",201);
	gotoxy(15,24); printf("%c",200);
	gotoxy(66,0); printf("%c",187);
	gotoxy(66,24); printf("%c",188);
	
	gotoxy(28,24); printf("%c",202);
	gotoxy(50,0); printf("%c",203);
	gotoxy(50,24); printf("%c",202);
	gotoxy(28,0); printf("%c",203);
	gotoxy(15,3); printf("%c",204);
	gotoxy(28,3); printf("%c",185);
	
	gotoxy(19,3); printf("%c",202);
	gotoxy(20,3); printf("%c",202);
	gotoxy(23,3); printf("%c",202);
	gotoxy(24,3); printf("%c",202);
	gotoxy(19,2); printf("%C",201);
	gotoxy(20,2); printf("%C",187);
	gotoxy(23,2); printf("%C",201);
	gotoxy(24,2); printf("%C",187);
	
	gotoxy(51,1); printf("%c",201);
	gotoxy(65,1); printf("%c",187);
	gotoxy(51,12); printf("%c",200);
	gotoxy(65,12); printf("%c",188);
	
	gotoxy(55,1); printf("%c",203);
	gotoxy(61,1); printf("%c",203);
	gotoxy(55,3); printf("%c",200);
	gotoxy(61,3); printf("%c",188);
}

void drawtetris(){
	gotoxy(17,5); printf("%c",35);
	gotoxy(18,5); printf("%c",35);
	gotoxy(18,6); printf("%c",35);
	gotoxy(19,6); printf("%c",35);
	
	gotoxy(17,9); printf("%c",35);
	gotoxy(18,8); printf("%c",35);
	gotoxy(18,9); printf("%c",35);
	gotoxy(19,8); printf("%c",35);
	
	gotoxy(17,11); printf("%c",35);
	gotoxy(17,12); printf("%c",35);
	gotoxy(18,12); printf("%c",35);
	gotoxy(19,12); printf("%c",35);
	
	gotoxy(17,15); printf("%c",35);
	gotoxy(18,15); printf("%c",35);
	gotoxy(19,14); printf("%c",35);
	gotoxy(19,15); printf("%c",35);
	
	gotoxy(17,18); printf("%c",35);
	gotoxy(18,17); printf("%c",35);
	gotoxy(18,18); printf("%c",35);
	gotoxy(19,18); printf("%c",35);
	
	gotoxy(18,20); printf("%c",35);
	gotoxy(19,20); printf("%c",35);
	gotoxy(18,21); printf("%c",35);
	gotoxy(19,21); printf("%c",35);
	
	gotoxy(17,23); printf("%c",35);
	gotoxy(18,23); printf("%c",35);
	gotoxy(19,23); printf("%c",35);
	gotoxy(20,23); printf("%c",35);
}

void drawtexto(){
	gotoxy(19,1); cout<<"Type "<<modgam;
	gotoxy(56,2); cout<<"Next:";
	gotoxy(52,14); cout<<"Score:";
	gotoxy(53,16); cout<<"Hi: ";
	for (i = 0; i < 6; i++){
		cout<<hiscr[i];
	}
	gotoxy(53,18); cout<<"Lines:";
	gotoxy(54,20); cout<<"Level";
	for (i = 5; i <= 23; i+=3){
		gotoxy(21,i); printf("x");
	}
}

void llenarnivelvacio(){
	for (i = 3; i < 24; i++){
		for (j = 1; j < 24; j++){
			nivel[i][j] = 0;
		}
	}
	for (i = 1; i < 24; i++){
		nivel[i][24] = -2;
	}
	for (i = 1; i < 24; i++){
		nivel[i][0] = 3;
	}
	for (i = 0; i < 25; i++){
		nivel[0][i] = 3;
		nivel[25][i] = 3;
	}
	for (i = 0; i < 25; i++){
		nivel[1][i] = 4;
		nivel[2][i] = 4;
		nivel[24][i] = 4;
	}
}

void mostrarnivel(){
	for (i = 0; i < 25; i++){
		for (j = 0; j < 26; j++){
			switch(nivel[j][i]){
				case 0:
					gotoxy(26+j,i);
					printf(" ");
					nivel[j][i] = -1;
					break;
				case 1:
					gotoxy(26+j,i);
					printf("%c",35);
					nivel[j][i] = -1;
					break;
				case 2:
					gotoxy(26+j,i);
					printf("%c",35);
					nivel[j][i] = -2;
					comprobarfila();
					break;
			}
		}
	}
}

void apretartecla(){
	if (kbhit()){
		tecla = getch();
	}
}

void Bloque::caer(){
	if (falltime >= 7000-(lvl*350)){
		y++;
		falltime = 0;
		Bloque::parar();
		Bloque::posicion();
		drawactual();
	}
	if (tecla == down){
		sumfall++;
		falltime += 7000;
	}
	falltime++;
}
void Bloque::llenar(){
	if (tipo != 7){
		for (i = 0; i < 3; i++){
			for (j = 0; j < 3; j++){
				tamanio[i][j] = 0;
			}
		}
	}
	switch (tipo){
		case 1:
			tamanio[0][1] = 1;
			tamanio[1][1] = 1;
			tamanio[1][2] = 1;
			tamanio[2][2] = 1;
			break;
		case 2:
			tamanio[0][2] = 1;
			tamanio[1][1] = 1;
			tamanio[1][2] = 1;
			tamanio[2][1] = 1;
			break;
		case 3:
			tamanio[0][1] = 1;
			tamanio[1][1] = 1;
			tamanio[2][1] = 1;
			tamanio[2][0] = 1;
			break;
		case 4:
			tamanio[0][1] = 1;
			tamanio[1][1] = 1;
			tamanio[2][1] = 1;
			tamanio[0][0] = 1;
			break;
		case 5:
			tamanio[0][2] = 1;
			tamanio[1][1] = 1;
			tamanio[1][2] = 1;
			tamanio[2][2] = 1;
			break;
		case 6:
			tamanio[1][2] = 1;
			tamanio[1][1] = 1;
			tamanio[2][1] = 1;
			tamanio[2][2] = 1;
			break;
		case 7:
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					barra[i][j] = 0;
					if (i == 2){
						barra[i][j] = 1;
					}
				}
			}
			break;
	}
}

void Bloque::establecer(){
	x = 12;
	y = 0;
	for (i = 0; i < 7; i++){
		if (i == tipo-1){
			cantbl[i]++;
			break;
		}
	}
	Bloque::posicion();
}

void Bloque::posicion(){
	if (tipo != 7){
		for (i = 0; i < 3; i++){
			for (j = 0; j < 3; j++){
				if (nivel [x+i][y+j] != -2 && nivel [x+i][y+j] != 3 && nivel [x+i][y+j] != 4){
					nivel[x+i][y+j] = tamanio[i][j];
				}
			}
		}
	} else {
		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				if (nivel [x+i][y+j] != -2 && nivel [x+i][y+j] != 3 && nivel [x+i][y+j] != 4){
					nivel[x+i][y+j] = barra[i][j];
					if (nivel [x+4][y+2] != -2 && nivel [x+4][y+2] != 3 && nivel [x+4][y+2]  != 4)
					nivel[x+4][y+2] = 0;
				}
			}
		}
	}
	for (i = -1; i < 4; i++){
		for (j = -1; j < 4; j++){
			if (x+i > 1 && nivel[x+i][y+j] == -1){
				nivel[x+i][y+j] = 0;
			}
		}
	}
}

void Bloque::parar(){
	if (tipo != 7){
		if (contb == 1){
			for (i = 0; i < 3; i++){
				for (j = 0; j < 3; j++){
					if (nivel[x+i][y+j] == -2 && tamanio[i][j] == 1){
						scr += sumfall;
						scr += cantbl[tipbl];
						contb = 0;
						y--;
						Bloque::parar();
						sumfall = 0;
					}
				}
			}
		} else {
			for (i = 0; i < 3; i++){
				for (j = 0; j < 3; j++){
					if (tamanio[i][j] == 1){
						tamanio[i][j] = 2;
					}
				}
			}
		}
	} else {
		if (contb == 1){
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					if (nivel[x+i][y+j+1] == -2 && barra[i][j] == 1){
						scr += falltime;
						scr += cantbl[tipbl];
						contb = 0;
						Bloque::parar();
					}
				}
			}
		} else {
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					if (barra[i][j] == 1){
						barra[i][j] = 2;
					}
				}
			}
		}
	}
}

void Bloque::mover(){
	if (tecla == left){
		x--;
		if (tipo != 7){
			for (i = 0; i < 3; i++){
				if (tamanio[0][i] == 1 && (nivel[x-2][y+i] == 3 || nivel[x][y+i] == -2)){
					x++;
					break;
				}
				if (tamanio[1][i] == 1 && (nivel[x-1][y+i] == 3 || nivel[x+1][y+i] == -2)){
					for (j = 0; j < 3; j++){
						if (tamanio[0][j] != 1){
							x++;
							break;
						}
					}
				}
			}
		} else {
			if (barra[2][0] == 1 && nivel[x][y] == 3){
				x++;
			} else if (barra[0][2] == 1 && nivel[x-2][y+2] == 3){
				x++;
			}
			for (i = 0; i < 4; i++){
				if (barra[2][i] == 1 && nivel[x+2][y+i] == -2){
					x++;
					break;
				} else if (barra[0][2] == 1 && nivel[x][y+2] == -2){
					x++;
					break;
				}
			}
		}
		
		Bloque::parar();
		Bloque::posicion();
	} else if (tecla == right){
		x++;
		if (tipo != 7){
			for (i = 0; i < 3; i++){
				if (tamanio[2][i] == 1 && (nivel[x+3][y+i] == 3 || nivel[x+2][y+i] == -2)){
					x--;
					break;
				}
				if (tamanio[1][i] == 1 && (nivel[x+2][y+i] == 3 || nivel[x+1][y+i] == -2)){
					for (j = 0; j < 3; j++){
						if (tamanio[2][j] != 1){
							x--;
							break;
						}
					}
				}
			}
		} else {
			if (barra[2][0] == 1 && nivel[x+3][y] == 3){
				x--;
			} else if (barra[3][2] == 1 && nivel[x+4][y+2] == 3){
				x--;
			}
			for (i = 0; i < 4; i++){
				if (barra[2][0] == 1 && nivel[x+2][y+i] == -2){
					x--;
					break;
				} else if (barra[0][2] == 1 && nivel[x+3][y+2] == -2){
					x--;
					break;
				}
			}
		}
		
		Bloque::parar();
		Bloque::posicion();
	}
}

void Bloque::girar(){
	int tamaux[3][3], baraux[4][4];
	
	if ((tecla == 'z' || tecla == 'Z') && tipo != 6){
		if (tipo != 7){
			for (i = 0; i < 3; i++){
				for (j = 0; j < 3; j++){
					tamaux[i][j] = tamanio[i][j];
				}
			}
			for (i = 0; i < 3; i++){
				int u = 2;
				for (j = 0; j < 3; j++){
					tamanio[i][j] = tamaux[u][i];
					u--;
				}
			}
			for (i = 0; i < 3; i++){
				for (j = 0; j < 3; j++){
					if (tamanio[i][j] == 1 && (nivel[x+i][y+j] == 4 || nivel[x+i][y+j] == -2)){
						for (i = 0; i < 3; i++){
							for (j = 0; j < 3; j++){
								tamanio[i][j] = tamaux[i][j];
							}
						}
						break;
					}
				}
			}
		} else {
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					baraux[i][j] = barra[i][j];
				}
			}
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					barra[i][j] = baraux[j][i];
				}
			}
			if (barra[0][2] == 1 && (nivel[x][y] == 4 || nivel[x+3][y] == 4)){
				for (i = 0; i < 4; i++){
					for (j = 0; j < 4; j++){
						barra[i][j] = baraux[i][j];
					}
				}
			}
			for (int u = 0; u < 4; u++){
				if (barra[0][2] == 1 && (nivel[x][y+u] == -2 || nivel[x+3][y+u] == -2 || nivel[x+1][y+u] == -2)){
					for (i = 0; i < 4; i++){
						for (j = 0; j < 4; j++){
							barra[i][j] = baraux[i][j];
						}
					}
					break;
				}
			}
		}
	} else if ((tecla == 'x' || tecla == 'X') && tipo != 6){
		if (tipo != 7){
			for (i = 0; i < 3; i++){
				for (j = 0; j < 3; j++){
					tamaux[i][j] = tamanio[i][j];
				}
			}
			for (i = 0; i < 3; i++){
				int u = 2;
				for (j = 0; j < 3; j++){
					tamanio[j][i] = tamaux[i][u];
					u--;
				}
			}
			for (i = 0; i < 3; i++){
				for (j = 0; j < 3; j++){
					if (tamanio[i][j] == 1 && (nivel[x+i][y+j] == 4 || nivel[x+i][y+j] == -2)){
						for (i = 0; i < 3; i++){
							for (j = 0; j < 3; j++){
								tamanio[i][j] = tamaux[i][j];
							}
						}
						break;
					}
				}
			}
		} else {
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					baraux[i][j] = barra[i][j];
				}
			}
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					barra[i][j] = baraux[j][i];
				}
			}
			if (barra[0][2] == 1 && (nivel[x][y] == 4 || nivel[x+3][y] == 4)){
				for (i = 0; i < 4; i++){
					for (j = 0; j < 4; j++){
						barra[i][j] = baraux[i][j];
					}
				}
			}
			for (int u = 0; u < 4; u++){
				if (barra[0][2] == 1 && (nivel[x][y+u] == -2 || nivel[x+3][y+u] == -2 || nivel[x+1][y+u] == -2)){
					for (i = 0; i < 4; i++){
						for (j = 0; j < 4; j++){
							barra[i][j] = baraux[i][j];
						}
					}
					break;
				}
			}
		}
	}
}

void comprobarfila(){
	int compf;
	for (i = 1; i < 24; i++){
		compf = 0;
		for (j = 3; j < 24; j++){
			if (nivel[j][i] == -2){
				compf++;
			}
		}
		if (compf == 21){
			if (modgam == 'A'){
				lines++;
			} else if (modgam == 'B'){
				lines--;
			}
			borrarfila(i);
		}
	}
}

void borrarfila(int _fila){
	for (int e = _fila; e >= 1; e--){
		for (int h = 3; h < 24; h++){
			if (e != 1){
				nivel[h][e] = nivel[h][e-1];
			} else {
				nivel[h][e] = 0;
			}
			
		}
	}
	
	for (int e = _fila; e >= 1; e--){
		for (int h = 3; h < 24; h++){
			if (nivel[h][e] == -1){
				nivel[h][e] = 0;
			}
			if (nivel[h][e] == -2){
				nivel[h][e] = 2;
			}
		}
	}
	scr += (100*(lvl+1))*combo;
	combo += 2;
	comprobarfila();
	aniborrar(_fila);
}

void aniborrar(int _nfila){
	int xl=39,xr=39;
	while (xl >= 29 || xr <= 49){
		gotoxy(xl,_nfila); printf(" ");
		gotoxy(xr,_nfila); printf(" ");
		xl--;
		xr++;
		Sleep(100);
	}
}

void Bloque::siguiente(){
	if (tipo != 7){
		for (i = 0; i < 3; i++){
			for (j = 0; j < 3; j++){
				gotoxy(56+i,6+j);
				if (tamanio[i][j] == 1){
					printf("%c",35);
				} else {
					printf(" ");
				}
				gotoxy(55,8); printf(" ");
			}
		}
	} else {
		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				gotoxy(55+i,6+j);
				if (barra[j][i] == 1){
					printf("%c",35);
				} else {
					printf(" ");
				}
			}
		}
	}
}

bool Bloque::comperder(){
	if (tipo != 7){
		for (i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (tamanio[i][j] == 1 && nivel[x+i][y+j] == -2){
					return true;
				}
			}
		}
	} else {
		for (i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (barra[i][j] == 1 && nivel[x+i][y+j] == -2){
					return true;
				}
			}
		}
	}
	return false;
}

void aniperder(){
	for (i = 23; i >= 1; i--){
		for (j = 29; j < 50; j++){
			gotoxy(j,i); printf("%c",35);
		}
		Sleep(100);
	}
}

void perder(){
	
	getch();
	
	system("cls");
	
	if (scr > atoi(thiscr)){
		drawscoremenu();
		insertarnombre();
	}
	if (compeasteregg()){
		easteregg();
	}
	if (scr > atoi(hiscr)){
		savescore("1");
		scr = atoi(hiscr);
		for (i = 0; i < 6; i++){
			newnombre[i] = hiscr[i+7];
		}
	}
	if (scr > atoi(shiscr)){
		savescore("2");
		scr = atoi(shiscr);
		for (i = 0; i < 6; i++){
			newnombre[i] = shiscr[i+7];
		}
	}
	if (scr > atoi(thiscr)){
		savescore("3");
		scr = atoi(thiscr);
		for (i = 0; i < 6; i++){
			newnombre[i] = thiscr[i+7];
		}
	}
}

void menu(){
	gotoxy(34,10); printf("Start Game");
	gotoxy(34,12); printf("High Scores");
	gotoxy(34,14); printf("Exit Game");
	gotoxy(32,10); printf("%c",16);
	opc = 1;
	gotoxy(0,0);
	
	while (tecla != enter){
		if (kbhit()){
			tecla = getch();
			switch (tecla){
				case up:
					opc--;
					if (opc == 0) opc = 3;
					break;
				case down:
					opc++;
					if (opc == 4) opc = 1;
					break;
			}
			switch (opc){
				case 1:
					gotoxy(32,10); printf("%c",16);
					gotoxy(32,12); printf(" ");
					gotoxy(32,14); printf(" ");
					break;
				case 2:
					gotoxy(32,10); printf(" ");
					gotoxy(32,12); printf("%c",16);
					gotoxy(32,14); printf(" ");
					break;
				case 3:
					gotoxy(32,10); printf(" ");
					gotoxy(32,12); printf(" ");
					gotoxy(32,14); printf("%c",16);
					break;
			}
			gotoxy(0,0);
		}
		sumarseed();
	}
	gotoxy(32,10); printf("            ");
	gotoxy(32,12); printf("             ");
	gotoxy(32,14); printf("           ");
}

void selectmode(){
	gotoxy(33,10); printf("Select Mode");
	gotoxy(35,12); printf("Mode A");
	gotoxy(35,14); printf("Mode B");
	gotoxy(33,12); printf("%c",16);
	modgam = 'A';
	tecla = left;
	gotoxy(0,0);
	while (tecla != enter && tecla != esc){
		if (kbhit()){
			tecla = getch();
			switch (tecla){
				case up:
					modgam = 'A';
					gotoxy(33,12); printf("%c",16);
					gotoxy(33,14); printf(" ");
					break;
				case down:
					modgam = 'B';
					gotoxy(33,12); printf(" ");
					gotoxy(33,14); printf("%c",16);
			}
			gotoxy(0,0);
		}
		sumarseed();
	}
	gotoxy(32,10); printf("            ");
	gotoxy(32,12); printf("             ");
	gotoxy(32,14); printf("           ");
}

void sumarseed(){
	seed++;
	if (seed > 2000){
		seed = 0;
	}
}

void selectlevel(){
	tecla = left;
	gotoxy(33,6); printf("Select level");
	for (i = 0; i < 10; i+=2){
		gotoxy(36,9+i); cout<<i/2;
	}
	for (i = 0; i < 10; i+=2){
		gotoxy(40,9+i); cout<<5+i/2;
	}
	gotoxy(34,9); printf("%c",16);
	gotoxy(0,0);
	while (tecla != enter && tecla != esc){
		if (kbhit()){
			tecla = getch();
			switch(tecla){
				case left:
					lvl -= 5; break;
				case right:
					lvl += 5; break;
				case up:
					lvl--; break;
				case down:
					lvl++; break;
			}
			if (lvl < 0) lvl += 10;
			if (lvl > 9) lvl -= 10;
			int auxlvl = lvl-5;
			switch(lvl){
				case 0: gotoxy(38,17); printf(" ");
				case 1:
				case 2:
				case 3:
				case 4:
					gotoxy(38,9); printf(" ");
					gotoxy(34,9+lvl*2); printf("%c",16);
					gotoxy(34,9+(lvl-1)*2); printf(" ");
					gotoxy(34,9+(lvl+1)*2); printf(" ");
					gotoxy(38,9+lvl*2); printf(" "); break;
				case 5: gotoxy(34,17); printf(" ");
				case 6:
				case 7:
				case 8:
				case 9:
					gotoxy(34,9); printf(" ");
					gotoxy(38,9+auxlvl*2); printf("%c",16);
					gotoxy(38,9+(auxlvl-1)*2); printf(" ");
					gotoxy(38,9+(auxlvl+1)*2); printf(" ");
					gotoxy(34,9+auxlvl*2); printf(" "); break;
			}
			gotoxy(0,0);
		}
		sumarseed();
	}
	gotoxy(33,7); printf("            ");
	for (i = 0; i < 10; i+=2){
		gotoxy(36,9+i); printf(" ");
	}
	for (i = 0; i < 10; i+=2){
		gotoxy(40,9+i); printf(" ");
	}
	gotoxy(38,9+lvl*2); printf (" ");
	gotoxy(34,9+lvl*2); printf (" ");
}

void drawactual(){
	if (scr < 10){
		gotoxy(59,14); cout<<"00000"<<scr;
	} else if (scr < 100){
		gotoxy(59,14); cout<<"0000"<<scr;
	} else if (scr < 1000){
		gotoxy(59,14); cout<<"000"<<scr;
	} else if (scr < 10000){
		gotoxy(59,14); cout<<"00"<<scr;
	} else if (scr < 100000){
		gotoxy(59,14); cout<<"0"<<scr;
	} else {
		gotoxy(59,14); cout<<scr;
	}
	if (lines < 10){
		gotoxy(60,18); cout<<"00"<<lines;
	} else if (lines < 100){
		gotoxy(60,18); cout<<"0"<<lines;
	} else {
		gotoxy(60,18); cout<<lines;
	}
	if (lvl < 10){
		gotoxy(60,20); cout<<"0"<<lvl;
	} else {
		gotoxy(60,20); cout<<lvl;
	}
	for (int i = 0; i < 7; i++){
		if (cantbl[i] < 10){
			gotoxy(23,5+i*3); cout<<"00"<<cantbl[i];
		} else if (cantbl[i] < 100){
			gotoxy(23,5+i*3); cout<<"0"<<cantbl[i];
		} else {
			gotoxy(23,5+i*3); cout<<cantbl[i];
		}
	}
}

void levelup(){
	if (lines >= 10+(lvl*10)){
		lvl++;
	}
}

void savescore(string puesto){
	ofstream archivo;
	string nomarch;
	
	nomarch = "Score"+puesto+".dat";
	
	archivo.open(nomarch.c_str(),ios::out);
	if (scr < 10000){
		archivo<<"00";
	} else if (scr < 100000){
		archivo<<"0";
	}
	archivo<<scr<<"*";
	
	for (i = 0; i < 6; i++){
		archivo<<newnombre[i];
	}
	
	archivo.close();
	compload = "1";
}

void loadscore(){
	ifstream archivo;
	string nombrearchivo;
	char comphi[14];
	
	nombrearchivo = "Score"+compload+".dat";
	
	archivo.open(nombrearchivo.c_str(),ios::in);
	
	
	
	if (compload == "1"){
		if (archivo.fail()){
			compload = "2";
			archivo.close();
			loadscore();
			return;
		}
		while (!archivo.eof()){
			archivo.getline(hiscr,14);
		}
	}
	
	if (compload == "2"){
		if (archivo.fail()){
			compload = "3";
			archivo.close();
			loadscore();
			return;
		}
		archivo.getline(comphi,14);
		archivo.close();
		archivo.open(nombrearchivo.c_str(),ios::in);
		archivo.getline(shiscr,14);
	}
	if (compload == "3"){
		if (archivo.fail()){
			archivo.close();
			return;
		}
		archivo.getline(comphi,14);
		archivo.close();
		archivo.open(nombrearchivo.c_str(),ios::in);
		archivo.getline(thiscr,14);
	}
	archivo.close();
	if (compload == "1"){
		compload = "2";
		loadscore();
	} else if (compload == "2"){
		compload = "3";
		loadscore();
	}
}

void drawscoremenu(){
	for (i = 16; i < 66; i++){
		gotoxy(i,0); printf("%c",205);
		gotoxy(i,24); printf("%c",205);
	}
	
	for (i = 1; i < 24; i++){
		gotoxy(15,i); printf("%c",186);
		gotoxy(66,i); printf("%c",186);
	}
	
	gotoxy(15,0); printf("%c",201);
	gotoxy(15,24); printf("%c",200);
	gotoxy(66,0); printf("%c",187);
	gotoxy(66,24); printf("%c",188);
	gotoxy(33,4); printf("New High Score!");
	gotoxy(33,6); printf("Enter Your Name:");
	
	gotoxy(22,12); cout<<"A B C D E F G H I J K L M N O P Q R S";
	gotoxy(22,14); cout<<"T U V W X Y Z a b c d e f g h i j k l";
	gotoxy(22,16); cout<<"m n o p q r s t u v w x y z 1 2 3 4 5";
	gotoxy(22,18); cout<<"6 7 8 9 0 . ? ! _                 end";
	gotoxy(40,18); printf("%c",27);
	
	gotoxy(18,22); cout<<"Z = Acept   X = Back";
}

void creartabla(){
	ofstream archivo;
	string contenido = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890.?!_*       ,,";
	
	archivo.open("Data.dat",ios::out);
	
	archivo<<contenido;
	
	archivo.close();
}

void llenartabla(){
	ifstream archivo;
	
	archivo.open("Data.dat",ios::in);
	
	for (int i = 0; i < 80; i++){
		archivo.getline(tablacaracteres[false],80);
	}
	
	archivo.close();
	tablacaracteres[0][0] = 'A';
}

void insertarnombre(){
	int npos = 0, xnpos = 0, ynpos = 0;
	char aux;
	
	for (i = 0; i < 6; i++){
		gotoxy(35+i*2,8); cout<<newnombre[i];
	}
	gotoxy(22,13); printf("%c",205);
	gotoxy(22,11); printf("%c",205);
	gotoxy(21,13); printf("%c",200);
	gotoxy(21,11); printf("%c",201);
	gotoxy(23,13); printf("%c",188);
	gotoxy(23,11); printf("%c",187);
	gotoxy(23,12); printf("%c",186);
	gotoxy(21,12); printf("%c",186);
	while (newnombre[npos-1] != ',' && newnombre[npos] != ','){
		if (kbhit()){
			tecla = getch();
			switch(tecla){
				case up: ynpos--; break;
				case down: ynpos++; break;
				case left: xnpos--; break;
				case right: xnpos++; break;
				case 'Z':
				case 'z':
					aux = newnombre[npos];
					newnombre[npos] = tablacaracteres[ynpos][xnpos];
					npos++; break;
				case 'X':
				case 'x': npos--; break;
			}
			if (newnombre[npos-1] == '*'){
				newnombre[npos-1] = ' ';
				gotoxy(35+(npos-1)*2,8); cout<<newnombre[npos-1];
				npos-=2;
				newnombre[npos] = ' ';
				gotoxy(35+(npos)*2,8); cout<<newnombre[npos];
			}
			if (ynpos < 0) ynpos = 3;
			if (ynpos > 3) ynpos = 0;
			if (xnpos < 0) xnpos = 18;
			if (xnpos > 18) xnpos = 0;
			if (xnpos > 17 && ynpos == 3 && (tecla == down || tecla == up || tecla == left)) xnpos = 17;
			if (xnpos > 17 && ynpos == 3 && tecla == right) xnpos = 0;
			mostrarseleccion(npos,xnpos,ynpos);
			if (npos > 5) npos = 5;
			if (npos < 0) npos = 0;
		}
		sumarseed();
	}
	newnombre[npos] = aux;
}

void mostrarseleccion(int npos, int xnpos, int ynpos){
	if (ynpos != 3 || xnpos != 17){
		gotoxy(22+xnpos*2,13+ynpos*2); printf("%c",205);
		gotoxy(22+xnpos*2,13+(ynpos-1)*2); printf("%c",205);
		gotoxy(21+xnpos*2,13+ynpos*2); printf("%c",200);
		gotoxy(21+xnpos*2,13+(ynpos-1)*2); printf("%c",201);
		gotoxy(23+xnpos*2,13+ynpos*2); printf("%c",188);
		gotoxy(23+xnpos*2,13+(ynpos-1)*2); printf("%c",187);
		gotoxy(23+xnpos*2,12+ynpos*2); printf("%c",186);
		gotoxy(23+(xnpos-1)*2,12+ynpos*2); printf("%c",186);
		
		gotoxy(22+xnpos*2,13+(ynpos+1)*2); printf(" ");
		gotoxy(22+xnpos*2,13+(ynpos-2)*2); printf(" ");
		gotoxy(23+xnpos*2,12+(ynpos-1)*2); printf(" ");
		
		gotoxy(21+xnpos*2,12+(ynpos-1)*2); printf(" ");
		gotoxy(21+xnpos*2,13+(ynpos+1)*2); printf(" ");
		gotoxy(21+xnpos*2,13+(ynpos-2)*2); printf(" ");
		gotoxy(23+xnpos*2,13+(ynpos+1)*2); printf(" ");
		gotoxy(23+xnpos*2,13+(ynpos-2)*2); printf(" ");
		gotoxy(23+(xnpos-2)*2,12+ynpos*2); printf(" ");
		gotoxy(23+(xnpos+1)*2,13+ynpos*2); printf(" ");
		gotoxy(23+(xnpos-2)*2,13+ynpos*2); printf(" ");
		gotoxy(23+(xnpos+1)*2,11+ynpos*2); printf(" ");
		gotoxy(23+(xnpos-2)*2,11+ynpos*2); printf(" ");
		gotoxy(22+(xnpos+1)*2,11+ynpos*2); printf(" ");
		gotoxy(22+(xnpos-1)*2,11+ynpos*2); printf(" ");
		gotoxy(22+(xnpos+1)*2,13+ynpos*2); printf(" ");
		gotoxy(22+(xnpos-1)*2,13+ynpos*2); printf(" ");
		if (ynpos != 3 || xnpos != 16){
			gotoxy(23+(xnpos+1)*2,12+ynpos*2); printf(" ");
		} else {
			gotoxy(22+(xnpos+2)*2,11+ynpos*2); printf(" ");
			gotoxy(22+(xnpos+2)*2,13+ynpos*2); printf(" ");
			gotoxy(23+(xnpos+2)*2,11+ynpos*2); printf(" ");
			gotoxy(23+(xnpos+2)*2,12+ynpos*2); printf(" ");
			gotoxy(23+(xnpos+2)*2,13+ynpos*2); printf(" ");
		}
		if (ynpos != 2 || xnpos != 17){
			gotoxy(23+xnpos*2,12+(ynpos+1)*2); printf(" ");
		} else {
			gotoxy(23+(xnpos+1)*2,12+(ynpos+1)*2); printf(" ");
			gotoxy(23+(xnpos+1)*2,13+(ynpos+1)*2); printf(" ");
			gotoxy(22+(xnpos+1)*2,13+(ynpos+1)*2); printf(" ");
		}
		if (ynpos != 2 || xnpos != 18){
			gotoxy(21+xnpos*2,12+(ynpos+1)*2); printf(" ");
		}
		
		if (xnpos == 0){
			for (i = 0; i < 5; i++){
				gotoxy(55+i,11+ynpos*2); printf(" ");
				gotoxy(55+i,13+ynpos*2); printf(" ");
			}
			gotoxy(59,12+ynpos*2); printf(" ");
			if (ynpos != 3){
				gotoxy(57,12+ynpos*2); printf(" ");
			} else {
				gotoxy(55,12+ynpos*2); printf(" ");
			}
		} else if (xnpos == 18){
			for (i = 0; i < 3; i++){
				gotoxy(21+i,11+ynpos*2); printf(" ");
				gotoxy(21+i,13+ynpos*2); printf(" ");
			}
			gotoxy(21,12+ynpos*2); printf(" ");
			gotoxy(23,12+ynpos*2); printf(" ");
		}
		
		if (ynpos == 0){
			for (i = 0; i < 3; i++){
				if (xnpos == 17){
					gotoxy(25+xnpos*2,17+i); printf(" ");
					gotoxy(21+xnpos*2,17+i); printf(" ");
				} else if (xnpos != 18){
					gotoxy(21+xnpos*2,17+i); printf(" ");
					gotoxy(23+xnpos*2,17+i); printf(" ");
				}
			}
			gotoxy(22+xnpos*2,17); printf(" ");
			gotoxy(22+xnpos*2,19); printf(" ");
			gotoxy(22+(xnpos+1)*2,17); printf(" ");
			gotoxy(23+xnpos*2,17); printf(" ");
			gotoxy(22+(xnpos+1)*2,19); printf(" ");
			gotoxy(23+xnpos*2,19); printf(" ");
		} else if (ynpos == 3){
			for (i = 0; i < 3; i++){
				gotoxy(21+xnpos*2,11+i); printf(" ");
				gotoxy(23+xnpos*2,11+i); printf(" ");
			}
			gotoxy(22+xnpos*2,11); printf(" ");
			gotoxy(22+xnpos*2,13); printf(" ");
		}
	} else {
		for (i = 22; i < 25; i++){
			gotoxy(i+xnpos*2,13+ynpos*2); printf("%c",205);
			gotoxy(i+xnpos*2,13+(ynpos-1)*2); printf("%c",205);
		}
		gotoxy(21+xnpos*2,13+ynpos*2); printf("%c",200);
		gotoxy(21+xnpos*2,13+(ynpos-1)*2); printf("%c",201);
		gotoxy(25+xnpos*2,13+ynpos*2); printf("%c",188);
		gotoxy(25+xnpos*2,13+(ynpos-1)*2); printf("%c",187);
		gotoxy(23+(xnpos+1)*2,12+ynpos*2); printf("%c",186);
		gotoxy(23+(xnpos-1)*2,12+ynpos*2); printf("%c",186);
		
		gotoxy(23+(xnpos-2)*2,18); printf(" ");
		gotoxy(23+(xnpos-2)*2,17); printf(" ");
		gotoxy(23+(xnpos-2)*2,19); printf(" ");
		gotoxy(24+(xnpos-2)*2,17); printf(" ");
		gotoxy(24+(xnpos-2)*2,19); printf(" ");
		
		gotoxy(23+xnpos*2,16); printf(" ");
		gotoxy(23+xnpos*2,15); printf(" ");
		gotoxy(24+xnpos*2,15); printf(" ");
		gotoxy(24+(xnpos-1)*2,15); printf(" ");
		gotoxy(23+(xnpos-1)*2,16); printf(" ");
		gotoxy(23+(xnpos-1)*2,15); printf(" ");
		gotoxy(23+(xnpos+1)*2,16); printf(" ");
		gotoxy(23+(xnpos+1)*2,15); printf(" ");
		for (i = 0; i < 5; i++){
			if (i != 1 && i != 3){
				gotoxy(21+i,18); printf(" ");
				gotoxy(55+i,12); printf(" ");
			}
			gotoxy(21+i,17); printf(" ");
			gotoxy(21+i,19); printf(" ");
			gotoxy(55+i,11); printf(" ");
			gotoxy(55+i,13); printf(" ");
		}
	}
	if (npos > 0 && newnombre[npos-1] != ','){
		gotoxy(35+(npos-1)*2,8); cout<<newnombre[npos-1];
	}
	if (npos < 6 && npos > -1){
		gotoxy(37+(npos-1)*2,8);
	} else if (npos == 6){
		gotoxy(35+(npos-1)*2,8);
	} else {
		gotoxy(37+npos*2,8);
	}
}

void ganar(){
	scr += (lvl*25);
	for (i = 35; i < 43; i++){
		gotoxy(i,11); printf("%c",205);
		gotoxy(i,13); printf("%c",205);
	}
	gotoxy(34,11); printf("%c",201);
	gotoxy(34,12); printf("%c",186);
	gotoxy(34,13); printf("%c",200);
	gotoxy(43,11); printf("%c",187);
	gotoxy(43,12); printf("%c",186);
	gotoxy(43,13); printf("%c",188);
	gotoxy(35,12); printf("You Win!");
	
	gotoxy(0,0); Sleep(2000);
	
	perder();
}

void hiscoremenu(){
	gotoxy(33,6); printf("High Scores:");
	gotoxy(32,8); printf("Name     Score");
	for (i = 7; i < 13; i++){
		gotoxy(25+i,10); cout<<hiscr[i];
		gotoxy(25+i,12); cout<<shiscr[i];
		gotoxy(25+i,14); cout<<thiscr[i];
	}
	for (i = 0; i < 6; i++){
		gotoxy(41+i,10); cout<<hiscr[i];
		gotoxy(41+i,12); cout<<shiscr[i];
		gotoxy(41+i,14); cout<<thiscr[i];
	}
	for (i = 1; i < 5; i++){
		gotoxy(30,8+i*2); cout<<i;
	}
	gotoxy(32,16); printf("Cirno    9");
	gotoxy(0,0);
	getch();
	tecla = 'r';
}

void pausar(){
	if (tecla == esc){
		gotoxy(0,0);
		tecla = 'r';
		while (tecla != enter){
			apretartecla();
			if (tecla == esc){
				opc = 4;
				break;
			}
		}
	}
}

bool compeasteregg(){
	char password[6] = {'u','t','s','u','h','o'};
	strcpy(lwrnewnombre,newnombre);
	strlwr(lwrnewnombre);
	
	if (strcmp(password,lwrnewnombre)==0){
		return true;
	} else {
		return false;
	}
}

void easteregg(){
	system("cls");
	
	system("mode con: cols=80 lines=30");
	
	tecla = up;
	
	okuu();
	
	gotoxy(0,0);
	
	while (tecla != enter){
		apretartecla();
	}
	
	system("mode con: cols=80 lines=25");
}

void okuu(){
	leerokuu();
	imprimirokuu();
	
	gotoxy(36,8); printf("%c",176);
	gotoxy(36,9); printf("%c",176);
	gotoxy(36,10); printf("%c",176);
	gotoxy(46,10); printf("%c",176);
	gotoxy(37,11); printf("%c",176);
	gotoxy(41,11); printf("%c",176);
	gotoxy(42,11); printf("%c",176);
	gotoxy(45,12); printf("%c",176);
	gotoxy(44,13); printf("%c",64);
	gotoxy(46,13); printf("%c",176);
	gotoxy(39,14); printf("%c",176);
	
	gotoxy(10,17); printf("%c",177);
	gotoxy(11,17); printf("%c",177);
	gotoxy(12,17); printf("%c",177);
	
	gotoxy(57,25); printf("%c",176);
	gotoxy(49,26); printf("%c",176);
	gotoxy(57,26); printf("%c",176);
	gotoxy(39,27); printf("%c",176);
	gotoxy(49,27); printf("%c",176);
}

void leerokuu(){
	ifstream archivo;
	
	archivo.open("Okuu.dat",ios::in);
	
	if (archivo.fail()){
		tecla = enter;
		return;
	}
	
	for(i = 0; i < 80; i++){
		archivo.getline(dibujo[false],2400);
	}
	
	archivo.close();
}

void imprimirokuu(){
	for (i = 0; i < 30; i++){
		for (j = 0; j < 80; j++){
			switch(dibujo[i][j]){
				case '0':
					gotoxy(j,i); printf(" "); break;
				case '1':
					gotoxy(j,i); printf("%c",220); break;
				case '2':
					gotoxy(j,i); printf("%c",223); break;
				case '3':
					gotoxy(j,i); printf("%c",219); break;
				case '4':
					gotoxy(j,i); printf("%c",178); break;
			}
		}
	}
}
