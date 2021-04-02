//Libreria para imprimir en pantalla
#include<stdio.h>
//Libreria para capturar y acceder al HANDLER
#include<windows.h>
//Libreria para capturar teclas presionadas
#include<conio.h>
//Libreria para obtener numero randomico
#include<stdlib.h>
//Libreria para trabajar con listas
#include<list>

using namespace std;

//Flechas de movimiento
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

//Limites de pantalla
#define limHorMin 2
#define limHorMax 88
#define limVerMin 2
#define limVerMax 28

//Bordes
#define BHORIZONTAL 205
#define BVERTICAL 186
#define BSUPIZQ 201
#define BSUPDER 200
#define BINFIZQ 187
#define BINFDER 188

void posicionarCursor(int X, int Y)
{
    //Identificador unico de cada objeto en pantalla que manipula el kernel
    HANDLE handleConsola;
    //Recuperar el identificador de la consola con el argumento para tomar el control de la salida
    handleConsola = GetStdHandle(STD_OUTPUT_HANDLE);

    //Estructura de datos (X, Y)
    COORD posicionCursor;
    posicionCursor.X = X;
    posicionCursor.Y = Y;

    //Funcion para darle una posicion al cursor. Parametro 1 indentificador (HANDLER). Parametro 2 Estructura de datos del objeto COORD
    SetConsoleCursorPosition(handleConsola, posicionCursor);
}

void pintar_limites(){
    for(int i=limHorMin; i<=limHorMax; i++){
        posicionarCursor(i,limVerMin); printf("%c",BHORIZONTAL);
        posicionarCursor(i,limVerMax); printf("%c",BHORIZONTAL);
    }
    for(int i=limVerMin; i<=limVerMax; i++){
        posicionarCursor(limHorMin,i); printf("%c",BVERTICAL);
        posicionarCursor(limHorMax,i); printf("%c",BVERTICAL);
    }
    posicionarCursor(limHorMin,limVerMin); printf("%c",BSUPIZQ);
    posicionarCursor(limHorMin,limVerMax); printf("%c",BSUPDER);
    posicionarCursor(limHorMax,limVerMin); printf("%c",BINFIZQ);
    posicionarCursor(limHorMax,limVerMax); printf("%c",BINFDER);
}

void ocultarCursor()
{
    HANDLE handleConsola;
    handleConsola = GetStdHandle(STD_OUTPUT_HANDLE);

    //Estructura de datos para controlar apariencia del cursor
    CONSOLE_CURSOR_INFO informacionCursor;
    informacionCursor.dwSize = 100;      //Entero de 1 a 100
    informacionCursor.bVisible = FALSE;  //Boleano

    //Funcion para controlar las caracteristicas del cursos en pantalla. Parametro 1 indentificador (HANDLER). Parametro 2 Estructura de datos del objeto CONSOLE_CURSOR_INFO
    SetConsoleCursorInfo(handleConsola, &informacionCursor);
}

class NAVE{
    //Por defecto, atributos privados, osea no puedo accederlos fuera de la estructura
    int x, y;
    int corazones;
    int vidas;

//Interfaz
public:
    //Constructor con el mismo nombre de la clase
    //x, toma el valor de _x, y toma el valor de_y
    NAVE(int _x, int _y, int _corazones, int _vidas):x(_x), y(_y), corazones(_corazones), vidas(_vidas){}
    int X(){return x;}
    int Y(){return y;}
    int VIDAS(){return vidas;}
    void choque() {corazones--;}
    void pintar();
    void borrar();
    void mover();
    void pintar_corazone();
    void morir();
};
void NAVE::pintar(){
    posicionarCursor(x,y);      printf("  %c  ", 30);
    posicionarCursor(x,y+1);    printf(" %c%c%c ", 40, 207, 41);
    posicionarCursor(x,y+2);    printf("%c%c %c%c", 30, 190, 190, 30);
}
void NAVE::borrar(){
    posicionarCursor(x,y);      printf("     ");
    posicionarCursor(x,y+1);    printf("     ");
    posicionarCursor(x,y+2);    printf("     ");

}
void NAVE::mover(){
    if(kbhit()) //Detecta si se a presionado una tecla
    {
        char tecla = getch();   //Guarda la tecla presionada
        borrar();
        if(tecla == IZQUIERDA && x>limHorMin+2) x--;
        if(tecla == DERECHA && x<limHorMax-6) x++;
        if(tecla == ARRIBA && y>limVerMin+1) y--;
        if(tecla == ABAJO && y<limVerMax-3) y++;
        if(tecla == 'x') corazones--;
        pintar_corazone();
        pintar();
    }
}
void NAVE::pintar_corazone(){
    posicionarCursor(limHorMax-35, limVerMin-1); printf("VIDAS %d", vidas);
    posicionarCursor(limHorMax-24, limVerMin-1); printf("salud");
    posicionarCursor(limHorMax-18, limVerMin-1); printf("     ");
    for (int i=0; i<corazones; i++){
        posicionarCursor(limHorMax-18+i, limVerMin-1); printf("%c", 3);
    }
}

void NAVE::morir(){
    if(corazones == 0){
        borrar();
        posicionarCursor(x,y);   printf("  *  ");
        posicionarCursor(x,y+1); printf(" *** ");
        posicionarCursor(x,y+2); printf("  *  ");
        Sleep(200);

        borrar();
        posicionarCursor(x,y);   printf(" * * ");
        posicionarCursor(x,y+1); printf("*   *");
        posicionarCursor(x,y+2); printf(" * * ");
        Sleep(200);

        borrar();
        posicionarCursor(x,y);   printf("*   *");
        posicionarCursor(x,y+1); printf("     ");
        posicionarCursor(x,y+2); printf("*   *");
        Sleep(200);

        borrar();
        vidas--;
        corazones = 3;
        pintar_corazone();
        pintar();
    }
}

class ASTEROIDE{
    int x, y;
    int posX();
    int posY();

public:
    ASTEROIDE();
    void pintar();
    void mover();
    void choque(class NAVE &Nave);
    int X(){return x;}
    int Y(){return y;}
};
ASTEROIDE::ASTEROIDE(){
    x = posX();
    y = posY();
}
int ASTEROIDE::posX(){
    int posicionAsteroideX = (limHorMin+1)+rand()%((limHorMax-3)+1-(limHorMin-1));
}
int ASTEROIDE::posY(){
    int posicionAsteroideY = (limVerMin+1)+rand()%((limVerMin+7)+1-(limHorMin-1));
}
void ASTEROIDE::pintar(){
    posicionarCursor(x,y); printf("%c", 184);
}
void ASTEROIDE::mover(){
    posicionarCursor(x,y); printf(" ");
    y++;
    if(y>limVerMax-1){
        x = posX();
        y = limVerMin+1;
    }
    pintar();
}

void ASTEROIDE::choque(class NAVE &Nave){
    if(x>=Nave.X() && x<=Nave.X()+4 && y>=Nave.Y() && y<=Nave.Y()+3){
        Nave.choque();
        Nave.pintar();
        Nave.pintar_corazone();
        x = posX();
        y = limVerMin+1;
    }
}

class BALA{
    int x;
    int y;

public:
    BALA(int _x, int _y):x(_x),y(_y){};
    void mover();
    bool fuera();
    int X(){return x;}
    int Y(){return y;}
};

void BALA::mover(){
    posicionarCursor(x,y); printf(" ");
    y--;
    posicionarCursor(x,y); printf("%c", 248);
}

bool BALA::fuera(){
    if(y == limVerMin+1) return true;
    return false;
}

int main()
{
    printf("COMO JUGAR:\n");
    printf("- con las flechas del teclado te mueves \n");
    printf("- disparas con la tecla 'a' \n");
    printf("- evita chocar con los asteroides \n");
    printf("- destruye tantos asteroides como puedas \n");
    system("pause");
    system("cls");

    int cantidadDeAsteroides = 6;
    ocultarCursor();
    pintar_limites();

    NAVE Nave(limHorMax/3,limVerMax-3,3,3);
    Nave.pintar_corazone();
    Nave.pintar();

    list<ASTEROIDE*> Asteroides;
    list<ASTEROIDE*>::iterator asteroide;
    for(int i=0; i<cantidadDeAsteroides; i++){
        Asteroides.push_back(new ASTEROIDE());
    }

    //Lista de la clase BALA llamada Balas
    list<BALA*> Balas;
    //iteratos llamado ir que recorre la lista con apuntadores a BALA
    list<BALA*>::iterator bala;

    bool Game_Over = false;
    int puntos = 0;
    while(!Game_Over)
    {
        posicionarCursor(limHorMin+15,limVerMin-1); printf("puntos %d", puntos);
        if(kbhit()){
            char tecla = getch();
            if(tecla == 'a'){
                Balas.push_back(new BALA(Nave.X()+2, Nave.Y()-1));
            }
        }
        for(bala=Balas.begin(); bala!=Balas.end(); bala++){
            (*bala)->mover();
            if((*bala)->fuera()){
                posicionarCursor((*bala)->X(), (*bala)->Y()); printf(" ");
                delete(*bala);
                bala = Balas.erase(bala);
            }
        }
        for(asteroide=Asteroides.begin(); asteroide!=Asteroides.end(); asteroide++){
            (*asteroide)->mover();
            (*asteroide)->choque(Nave);
        }
        for(asteroide=Asteroides.begin(); asteroide!=Asteroides.end(); asteroide++){
            for(bala=Balas.begin(); bala!=Balas.end(); bala++){
                if((*asteroide)->X()==(*bala)->X() && ((*asteroide)->Y()+1==(*bala)->Y() || (*asteroide)->Y()==(*bala)->Y())){
                    posicionarCursor((*bala)->X(), (*bala)->Y()); printf(" ");
                    delete(*bala);
                    bala = Balas.erase(bala);
                    Asteroides.push_back(new ASTEROIDE());
                    posicionarCursor((*asteroide)->X(), (*asteroide)->Y()); printf(" ");
                    delete(*asteroide);
                    asteroide = Asteroides.erase(asteroide);
                    puntos+=5;
                }
            }
        }

        if(Nave.VIDAS() == 0) Game_Over = true;

        Nave.morir();
        Nave.mover();

        Sleep(30);
    }

    system("cls");
    printf("Gracias por jugar\ntu puntaje fue: %d \n", puntos);
    system("pause");
return 0;
}
