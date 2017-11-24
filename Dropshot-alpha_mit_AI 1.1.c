#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
int R=42;
int Mi[5][11],HP[5][11];

//Problema as unidades erradas se movimentam
//Problema na linha 1 da matriz
//Aumentar tempo RIPs
//Colocar comandos de mouse

const int SCREEN_WIDTH = 1332;
const int SCREEN_HEIGHT = 678;
const int SCREEN_BPP = 32;

SDL_Surface *tela = NULL;
SDL_Surface *menu_imagem = NULL;
SDL_Surface *menu_conquistas = NULL;
SDL_Surface *menu_instrucoes = NULL;
SDL_Surface *fundo = NULL;
SDL_Surface *mapa = NULL;
SDL_Surface *botao1 = NULL;
SDL_Surface *botao1_p = NULL;
SDL_Surface *botao2 = NULL;
SDL_Surface *botao2_p = NULL;
SDL_Surface *botao3 = NULL;
SDL_Surface *botao3_p = NULL;
SDL_Surface *botao4 = NULL;
SDL_Surface *botao4_p = NULL;
SDL_Surface *cursor_americano = NULL;
SDL_Surface *palito_anda1 = NULL;
SDL_Surface *palito_anda2 = NULL;
SDL_Surface *palito_anda3 = NULL;
SDL_Surface *palito_anda4 = NULL;
SDL_Surface *americano_atira3 = NULL;
SDL_Surface *americano_atira4 = NULL;
SDL_Surface *cursor_americano2 = NULL;
SDL_Surface *AmericanoA = NULL;
SDL_Surface *AmericanoA_anda = NULL;
SDL_Surface *AmericanoA_atira1 = NULL;
SDL_Surface *AmericanoA_atira2 = NULL;
SDL_Surface *AmericanoA_atira3 = NULL;
SDL_Surface *AmericanoA_atirafinal = NULL;
SDL_Surface *cursor_americano3 = NULL;
SDL_Surface *AmericanoM = NULL;
SDL_Surface *AmericanoM_anda = NULL;
SDL_Surface *AmericanoM_atira1 = NULL;
SDL_Surface *AmericanoM_atira2 = NULL;
SDL_Surface *AmericanoM_atira3 = NULL;
SDL_Surface *AmericanoM_atirafinal = NULL;
SDL_Surface *cursor_sovietico = NULL;
SDL_Surface *sovietico = NULL;
SDL_Surface *sovietico_anda = NULL;
SDL_Surface *sovietico_atira = NULL;
SDL_Surface *SovieticoF_atira2 = NULL;
SDL_Surface *SovieticoF_atira3 = NULL;
SDL_Surface *SovieticoF_atirafinal = NULL;
SDL_Surface *SovieticoA = NULL;
SDL_Surface *SovieticoA_anda = NULL;
SDL_Surface *SovieticoA_atira = NULL;
SDL_Surface *SovieticoA_atira2 = NULL;
SDL_Surface *SovieticoA_atira3 = NULL;
SDL_Surface *SovieticoA_atirafinal = NULL;
SDL_Surface *SovieticoM = NULL;
SDL_Surface *SovieticoM_anda = NULL;
SDL_Surface *SovieticoM_atira = NULL;
SDL_Surface *SovieticoM_atira2 = NULL;
SDL_Surface *SovieticoM_atira3 = NULL;
SDL_Surface *SovieticoM_atirafinal = NULL;
SDL_Surface *teste = NULL;
SDL_Surface *base1_teste = NULL;
SDL_Surface *base2_teste = NULL;
SDL_Surface *vida1_a = NULL;
SDL_Surface *vida1_b = NULL;
SDL_Surface *vida = NULL;
SDL_Surface *vida2_a = NULL;
SDL_Surface *vida2_b = NULL;
SDL_Surface *RIP = NULL;
SDL_Surface *Conquistas = NULL;
SDL_Surface *Custer = NULL;
SDL_Surface *Kill1 = NULL;
SDL_Surface *Moscow = NULL;
SDL_Surface *Tokensx0 = NULL;
SDL_Surface *Tokensx1 = NULL;
SDL_Surface *Tokensx2 = NULL;
SDL_Surface *Tokensx3 = NULL;
SDL_Surface *Tokensx4 = NULL;
SDL_Surface *Tokensx5 = NULL;

SDL_Event evento;

Mix_Music *mus_menu = NULL;
Mix_Music *musica = NULL;
Mix_Chunk *tiro = NULL;
Mix_Chunk *tiro_2 = NULL;
Mix_Chunk *tiro_3 = NULL;
Mix_Chunk *entrada1 = NULL;
Mix_Chunk *entrada2 = NULL;

typedef struct timer
{
    float t1, t2, aux;
}timer;

typedef struct movel
{
    int x ,y, x_a, y_a;
    int velx, vely;
    int altura, largura;
    int status, status2, status3, status4, status5;
    timer tempo;
    SDL_Surface *sprite[6], *icone;

}movel;

typedef struct fase
{
    //usos codigo
    int i, j,turno,Dollar,Rublo,e,auxU,auxH,stance,act;
    //usos SDL
    SDL_Surface *mapa_f;
    int base1, base2, col;
    timer tempo;
}fase;

typedef struct map_fase
{
    int tipo, status, posicao; //tipo verifica se é checkpoint, status se é warzone, posição indica local no mapa
    int posse, unidade[4], unidade_s[4], HP[4];
    movel soldado[4];
}map_fase;

SDL_Surface *carregar_imagem( char nomearquivo[] ){

    //Declaração de superfícies
    SDL_Surface *imagem_carregada = NULL;
    SDL_Surface *imagem_otimizada = NULL;

    //Carrega imagem e a coloca numa superfície
    imagem_carregada = IMG_Load( nomearquivo );

    //Otimiza a imagem numa nova superfície e deleta a superfície antiga
    if (imagem_carregada != NULL){

        imagem_otimizada = SDL_DisplayFormat( imagem_carregada );
        SDL_FreeSurface( imagem_carregada );
    }

    return imagem_otimizada;
}

void aplicar_superficie (int x, int y, SDL_Surface *aplicar, SDL_Surface *local, SDL_Rect* sep){

    //Cria um retangulo para aplicar as superfícies
    SDL_Rect objeto;

    //Coordenadas objeto
    objeto.x = x;
    objeto.y = y;

    //Aplica a superfície
    SDL_BlitSurface( aplicar, sep, local, &objeto);
}

int iniciar() {
    //Inicializa SDL por completo
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return -1;
    }

    tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( tela == NULL )
    {
        return -1;
    }

    if( TTF_Init() == -1 )
    {
        return -1;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return -1;
    }

    SDL_WM_SetCaption( "Dropshot Alpha 1.1", NULL );

    return 1;
}

int carregar_arquivos(){

    menu_imagem = carregar_imagem ( "menu.png" );
    if (menu_imagem == NULL)
    {
        return -1;
    }
    menu_instrucoes = carregar_imagem ( "instrucoes.png" );
    if (menu_instrucoes == NULL){
        return -1;
    }
    fundo = carregar_imagem ( "fundo.png" );
    if (fundo == NULL){
        return -1;
    }
    mapa = carregar_imagem ( "mapa.png" );
    if (mapa == NULL){
        return -1;
    }
    botao1 = carregar_imagem ( "botao1.png" );
    if (botao1 == NULL){
        return -1;
    }
    botao1_p = carregar_imagem ( "botao1_p.png" );
    if (botao1_p == NULL){
        return -1;
    }
    botao2 = carregar_imagem ( "botao2.png" );
    if (botao2 == NULL){
        return -1;
    }
    botao2_p = carregar_imagem ( "botao2_p.png" );
    if (botao2_p == NULL){
        return -1;
    }
    botao3 = carregar_imagem ( "botao3.png" );
    if (botao3 == NULL){
        return -1;
    }
    botao3_p = carregar_imagem ( "botao3_p.png" );
    if (botao3_p == NULL){
        return -1;
    }
    botao4 = carregar_imagem ( "botao4.png" );
    if (botao4 == NULL){
        return -1;
    }
    botao4_p = carregar_imagem ( "botao4_p.png" );
    if (botao4_p == NULL){
        return -1;
    }
    cursor_americano = carregar_imagem ( "cursor_americano.png" );
    Uint32 colorkey = SDL_MapRGB( cursor_americano->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( cursor_americano, SDL_SRCCOLORKEY, colorkey );
    if (cursor_americano == NULL){
        return -1;
    }
    cursor_americano2 = carregar_imagem ( "cursor_americano2.bmp" );
    colorkey = SDL_MapRGB( cursor_americano2->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( cursor_americano2, SDL_SRCCOLORKEY, colorkey );
    if (cursor_americano2 == NULL){
        return -1;
    }
    cursor_americano3 = carregar_imagem ( "cursor_americano3.png" );
    colorkey = SDL_MapRGB( cursor_americano3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( cursor_americano3, SDL_SRCCOLORKEY, colorkey );
    if (cursor_americano3 == NULL){
        return -1;
    }
    palito_anda1 = carregar_imagem ( "palito_anda1.bmp" );
    colorkey = SDL_MapRGB( palito_anda1->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( palito_anda1, SDL_SRCCOLORKEY, colorkey );
    if (palito_anda1 == NULL){
        return -1;
    }
    palito_anda2 = carregar_imagem ( "palito_anda2.bmp" );
    colorkey = SDL_MapRGB( palito_anda2->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( palito_anda2, SDL_SRCCOLORKEY, colorkey );
    if (palito_anda2 == NULL){
        return -1;
    }
    palito_anda3 = carregar_imagem ( "palito_anda3.bmp" );
    colorkey = SDL_MapRGB( palito_anda3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( palito_anda3, SDL_SRCCOLORKEY, colorkey );
    if (palito_anda3 == NULL){
        return -1;
    }
    palito_anda4 = carregar_imagem ( "palito_anda4.bmp" );
    colorkey = SDL_MapRGB( palito_anda4->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( palito_anda4, SDL_SRCCOLORKEY, colorkey );
    if (palito_anda4 == NULL){
        return -1;
    }
    americano_atira3 = carregar_imagem ( "americano_atira3.bmp" );
    colorkey = SDL_MapRGB( americano_atira3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( americano_atira3, SDL_SRCCOLORKEY, colorkey );
    if (americano_atira3 == NULL){
        return -1;
    }
    americano_atira4 = carregar_imagem ( "americano_atira4.bmp" );
    colorkey = SDL_MapRGB( americano_atira4->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( americano_atira4, SDL_SRCCOLORKEY, colorkey );
    if (americano_atira4 == NULL){
        return -1;
    }
    AmericanoA = carregar_imagem ( "AmericanoA.bmp" );
    colorkey = SDL_MapRGB( AmericanoA->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoA, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoA == NULL){
        return -1;
    }
    AmericanoA_anda = carregar_imagem ( "AmericanoA_anda.bmp" );
    colorkey = SDL_MapRGB( AmericanoA_anda->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoA_anda, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoA_anda == NULL){
        return -1;
    }
    AmericanoA_atira1 = carregar_imagem ( "AmericanoA_atira1.bmp" );
    colorkey = SDL_MapRGB( AmericanoA_atira1->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoA_atira1, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoA_atira1 == NULL){
        return -1;
    }
    AmericanoA_atira2 = carregar_imagem ( "AmericanoA_atira2.bmp" );
    colorkey = SDL_MapRGB( AmericanoA_atira2->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoA_atira2, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoA_atira2 == NULL){
        return -1;
    }
    AmericanoA_atira3 = carregar_imagem ( "AmericanoA_atira3.bmp" );
    colorkey = SDL_MapRGB( AmericanoA_atira3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoA_atira3, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoA_atira3 == NULL){
        return -1;
    }
    AmericanoA_atirafinal = carregar_imagem ( "AmericanoA_atirafinal.bmp" );
    colorkey = SDL_MapRGB( AmericanoA_atirafinal->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoA_atirafinal, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoA_atirafinal == NULL){
        return -1;
    }
    AmericanoM = carregar_imagem ( "AmericanoM.png" );
    colorkey = SDL_MapRGB( AmericanoM->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoM, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoM == NULL){
        return -1;
    }
    AmericanoM_anda = carregar_imagem ( "AmericanoM_anda.png" );
    colorkey = SDL_MapRGB( AmericanoM_anda->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoM_anda, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoM_anda == NULL){
        return -1;
    }
    AmericanoM_atira1 = carregar_imagem ( "AmericanoM_atira.png" );
    colorkey = SDL_MapRGB( AmericanoM_atira1->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoM_atira1, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoM_atira1 == NULL){
        return -1;
    }
    AmericanoM_atira2 = carregar_imagem ( "AmericanoM_atira2.png" );
    colorkey = SDL_MapRGB( AmericanoM_atira2->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoM_atira2, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoM_atira2 == NULL){
        return -1;
    }
    AmericanoM_atira3 = carregar_imagem ( "AmericanoM_atira3.png" );
    colorkey = SDL_MapRGB( AmericanoM_atira3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoM_atira3, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoM_atira3 == NULL){
        return -1;
    }
    AmericanoM_atirafinal = carregar_imagem ( "AmericanoM_atirafinal.png" );
    colorkey = SDL_MapRGB( AmericanoM_atirafinal->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( AmericanoM_atirafinal, SDL_SRCCOLORKEY, colorkey );
    if (AmericanoM_atirafinal == NULL){
        return -1;
    }
    cursor_sovietico = carregar_imagem ( "cursor_sovietico.bmp" );
    colorkey = SDL_MapRGB( cursor_sovietico->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( cursor_sovietico, SDL_SRCCOLORKEY, colorkey );
    if (cursor_sovietico == NULL){
        return -1;
    }
    sovietico = carregar_imagem ( "sovietico.bmp" );
    colorkey = SDL_MapRGB( sovietico->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( sovietico, SDL_SRCCOLORKEY, colorkey );
    if (sovietico == NULL){
        return -1;
    }
    sovietico_anda = carregar_imagem ( "sovietico_anda.bmp" );
    colorkey = SDL_MapRGB( sovietico_anda->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( sovietico_anda, SDL_SRCCOLORKEY, colorkey );
    if (sovietico_anda == NULL){
        return -1;
    }
    sovietico_atira = carregar_imagem ( "sovietico_atira.bmp" );
    colorkey = SDL_MapRGB( sovietico_atira->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( sovietico_atira, SDL_SRCCOLORKEY, colorkey );
    if (sovietico_atira == NULL){
        return -1;
    }
    SovieticoF_atira2 = carregar_imagem ( "SovieticoF_atira2.bmp" );
    colorkey = SDL_MapRGB( SovieticoF_atira2->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoF_atira2, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoF_atira2 == NULL){
        return -1;
    }
    SovieticoF_atira3 = carregar_imagem ( "SovieticoF_atira3.bmp" );
    colorkey = SDL_MapRGB( SovieticoF_atira3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoF_atira3, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoF_atira3 == NULL){
        return -1;
    }
    SovieticoF_atirafinal = carregar_imagem ( "SovieticoF_atirafinal.bmp" );
    colorkey = SDL_MapRGB( SovieticoF_atirafinal->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoF_atirafinal, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoF_atirafinal == NULL){
        return -1;
    }
    SovieticoA = carregar_imagem ( "SovieticoA.png" );
    colorkey = SDL_MapRGB( SovieticoA->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoA, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoA == NULL){
        return -1;
    }
    SovieticoA_anda = carregar_imagem ( "SovieticoA_anda.png" );
    colorkey = SDL_MapRGB( SovieticoA_anda->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoA_anda, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoA_anda == NULL){
        return -1;
    }
    SovieticoA_atira = carregar_imagem ( "SovieticoA_atira.png" );
    colorkey = SDL_MapRGB( SovieticoA_atira->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoA_atira, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoA_atira == NULL){
        return -1;
    }
    SovieticoA_atira2 = carregar_imagem ( "SovieticoA_atira2.png" );
    colorkey = SDL_MapRGB( SovieticoA_atira2->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoA_atira2, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoA_atira2 == NULL){
        return -1;
    }
    SovieticoA_atira3 = carregar_imagem ( "SovieticoA_atira3.png" );
    colorkey = SDL_MapRGB( SovieticoA_atira3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoA_atira3, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoA_atira3 == NULL){
        return -1;
    }
    SovieticoA_atirafinal = carregar_imagem ( "SovieticoA_atirafinal.png" );
    colorkey = SDL_MapRGB( SovieticoA_atirafinal->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoA_atirafinal, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoA_atirafinal == NULL){
        return -1;
    }
    SovieticoM = carregar_imagem ( "SovieticoM.png" );
    colorkey = SDL_MapRGB( SovieticoM->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoM, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoM == NULL){
        return -1;
    }
    SovieticoM_anda = carregar_imagem ( "SovieticoM_anda.png" );
    colorkey = SDL_MapRGB( SovieticoM_anda->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoM_anda, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoM_anda == NULL){
        return -1;
    }
    SovieticoM_atira = carregar_imagem ( "SovieticoM_atira.png" );
    colorkey = SDL_MapRGB( SovieticoM_atira->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoM_atira, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoM_atira == NULL){
        return -1;
    }
    SovieticoM_atira2 = carregar_imagem ( "SovieticoM_atira2.png" );
    colorkey = SDL_MapRGB( SovieticoM_atira2->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoM_atira2, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoM_atira2 == NULL){
        return -1;
    }
    SovieticoM_atira3 = carregar_imagem ( "SovieticoM_atira3.png" );
    colorkey = SDL_MapRGB( SovieticoM_atira3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoM_atira3, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoM_atira3 == NULL){
        return -1;
    }
    SovieticoM_atirafinal = carregar_imagem ( "SovieticoM_atirafinal.png" );
    colorkey = SDL_MapRGB( SovieticoM_atirafinal->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( SovieticoM_atirafinal, SDL_SRCCOLORKEY, colorkey );
    if (SovieticoM_atirafinal == NULL){
        return -1;
    }
    teste = carregar_imagem ( "teste.bmp" );
    colorkey = SDL_MapRGB( teste->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( teste, SDL_SRCCOLORKEY, colorkey );
    if (teste == NULL){
        return -1;
    }
    base1_teste = carregar_imagem ( "base1_teste.bmp" );
    colorkey = SDL_MapRGB( base1_teste->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( base1_teste, SDL_SRCCOLORKEY, colorkey );
    if (base1_teste == NULL){
        return -1;
    }
    base2_teste = carregar_imagem ( "base2_teste.bmp" );
    colorkey = SDL_MapRGB( base2_teste->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( base2_teste, SDL_SRCCOLORKEY, colorkey );
    if (base2_teste == NULL){
        return -1;
    }
    vida1_a = carregar_imagem ( "vida1_a.png" );
    colorkey = SDL_MapRGB( vida1_a->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( vida1_a, SDL_SRCCOLORKEY, colorkey );
    if (vida1_a == NULL){
        return -1;
    }
    vida1_b = carregar_imagem ( "vida1_b.png" );
    colorkey = SDL_MapRGB( vida1_b->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( vida1_b, SDL_SRCCOLORKEY, colorkey );
    if (vida1_b == NULL){
        return -1;
    }
    vida = carregar_imagem ( "vida.png" );
    colorkey = SDL_MapRGB( vida->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( vida, SDL_SRCCOLORKEY, colorkey );
    if (vida == NULL){
        return -1;
    }
    vida2_a = carregar_imagem ( "vida2_a.png" );
    colorkey = SDL_MapRGB( vida2_a->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( vida2_a, SDL_SRCCOLORKEY, colorkey );
    if (vida2_a == NULL){
        return -1;
    }
    vida2_b = carregar_imagem ( "vida2_b.png" );
    colorkey = SDL_MapRGB( vida2_b->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( vida2_b, SDL_SRCCOLORKEY, colorkey );
    if (vida2_b == NULL){
        return -1;
    }
    RIP = carregar_imagem ( "RIP.png" );
    colorkey = SDL_MapRGB( RIP->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( RIP, SDL_SRCCOLORKEY, colorkey );
    if (RIP == NULL){
        return -1;
    }
    Conquistas = carregar_imagem ( "Conquistas.png" );
    colorkey = SDL_MapRGB( Conquistas->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Conquistas, SDL_SRCCOLORKEY, colorkey );
    if (Conquistas == NULL){
        return -1;
    }
    Custer = carregar_imagem ( "Custer.png" );
    colorkey = SDL_MapRGB( Custer->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Custer, SDL_SRCCOLORKEY, colorkey );
    if (Custer == NULL){
        return -1;
    }
    Kill1 = carregar_imagem ( "Kill1.png" );
    colorkey = SDL_MapRGB( Kill1->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Kill1, SDL_SRCCOLORKEY, colorkey );
    if (Kill1 == NULL){
        return -1;
    }
    Moscow = carregar_imagem ( "Moscow.png" );
    colorkey = SDL_MapRGB( Moscow->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Moscow, SDL_SRCCOLORKEY, colorkey );
    if (Moscow == NULL){
        return -1;
    }
    Tokensx0 = carregar_imagem ( "Tokensx0.png" );
    colorkey = SDL_MapRGB( Tokensx0->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Tokensx0, SDL_SRCCOLORKEY, colorkey );
    if (Tokensx0 == NULL){
        return -1;
    }
    Tokensx1 = carregar_imagem ( "Tokensx1.png" );
    colorkey = SDL_MapRGB( Tokensx1->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Tokensx1, SDL_SRCCOLORKEY, colorkey );
    if (Tokensx1 == NULL){
        return -1;
    }
    Tokensx2 = carregar_imagem ( "Tokensx2.png" );
    colorkey = SDL_MapRGB( Tokensx2->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Tokensx2, SDL_SRCCOLORKEY, colorkey );
    if (Tokensx2 == NULL){
        return -1;
    }
    Tokensx3 = carregar_imagem ( "Tokensx3.png" );
    colorkey = SDL_MapRGB( Tokensx3->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Tokensx3, SDL_SRCCOLORKEY, colorkey );
    if (Tokensx3 == NULL){
        return -1;
    }
    Tokensx4 = carregar_imagem ( "Tokensx4.png" );
    colorkey = SDL_MapRGB( Tokensx4->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Tokensx4, SDL_SRCCOLORKEY, colorkey );
    if (Tokensx4 == NULL){
        return -1;
    }
    Tokensx5 = carregar_imagem ( "Tokensx5.png" );
    colorkey = SDL_MapRGB( Tokensx5->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( Tokensx5, SDL_SRCCOLORKEY, colorkey );
    if (Tokensx5 == NULL){
        return -1;
    }

    mus_menu = Mix_LoadMUS( "mus_menu.mp3" );
    if ( mus_menu == NULL )
    {
        return -1;
    }
    musica = Mix_LoadMUS( "musica.mp3" );
    if ( musica == NULL )
    {
        return -1;
    }
    tiro = Mix_LoadWAV( "tiro.wav" );
    if ( tiro == NULL )
    {
        return -1;
    }
    tiro_2 = Mix_LoadWAV( "tiro_2.wav" );
    if ( tiro_2 == NULL )
    {
        return -1;
    }
    tiro_3 = Mix_LoadWAV( "tiro_3.wav" );
    if ( tiro_3 == NULL )
    {
        return -1;
    }
    entrada1 = Mix_LoadWAV( "entrada1.wav" );
    if ( entrada1 == NULL )
    {
        return -1;
    }
    entrada2 = Mix_LoadWAV( "entrada2.wav" );
    if ( entrada2 == NULL )
    {
        return -1;
    }

    return 1;
}

void declarar_movel(movel *obj)
{
    obj->x = 0;
    obj->y = 0;
    obj->velx = 0;
    obj->vely = 0;
    obj->status = 1;
    obj->status2 = 0;
    obj->status3 = 0;
    obj->status4 = 0;
    obj->status5 = 0;
    obj->tempo.t1 = 0;
    obj->tempo.t2 = 0;
    obj->tempo.aux = 0;
}

int eventos_botao(movel *botao)
{
    int x, y, status=0;
    if( evento.type == SDL_MOUSEMOTION )
    {
        x = evento.motion.x;
        y = evento.motion.y;
        if (x > botao->x && x < botao->x + botao->largura && y > botao->y && y < botao->y + botao->altura)
        {
            status = 1;
        }
    }
    if( evento.type == SDL_MOUSEBUTTONDOWN )
    {
        if( evento.button.button == SDL_BUTTON_LEFT )
        {
            x = evento.button.x;
            y = evento.button.y;
            if (x > botao->x && x < botao->x + botao->largura && y > botao->y && y < botao->y + botao->altura)
            {
                status = 2;
            }
        }
    }
    return status;
}

int movimento_SDL(movel *obj)
{
    if (obj->x + obj->velx < SCREEN_WIDTH - (obj->largura/2) && obj->x + obj->velx > -obj->largura/2)
    {
        obj->x = obj->x + obj->velx;
    }
    else
    {
        //obj->velx = -obj->velx;
        obj->x = obj->x - obj->velx;
    }
    if (obj->y + obj->vely < SCREEN_HEIGHT - (obj->altura/2) && obj->y + obj->vely > -obj->altura/2)
    {
        obj->y = obj->y + obj->vely;
    }
    else
    {
        //obj->vely = -obj->vely;
        obj->y = obj->y - obj->vely;
    }
    return 1;
}

void americano_anda (movel *americano)
{
    if (americano->status == 0 || americano->status == 2 || americano->status == 3 || americano->status == 4 || americano->status == 5)
    {
        americano->status = 1;
    }
    else if (americano->status == 1)
    {
        americano->status = 0;
    }
}


void sovietico_andar (movel *Sovietico)
{
    if (Sovietico->status == 3 || Sovietico->status == 1)
    {
        Sovietico->status = 0;
    }
    else if (Sovietico->status == 0)
    {
        Sovietico->status = 1;
    }
}

int americano_atirar (movel *americano, int tipo)
{
    if (americano->status == 0 || americano->status == 1)
    {
        if (tipo == 1)
        {
            Mix_Volume( 1, 22);
            if( Mix_PlayChannel( 1, tiro, 0 ) == -1 )
            {
                return -1;
            }
        }
        else if (tipo == 2)
        {
            Mix_Volume( 2, 25);
            if( Mix_PlayChannel( 2, tiro_2, 0 ) == -1 )
            {
                return -1;
            }
        }
        else if (tipo == 3)
        {
            Mix_Volume( 3, 17);
            if( Mix_PlayChannel( 3, tiro_3, 0 ) == -1 )
            {
                return -1;
            }
        }
        americano->status = 2;
    }
    else if (americano->status == 2)
    {
        americano->status = 3;
    }
    else if (americano->status == 3)
    {
        americano->status = 4;
    }
    else if (americano->status == 4)
    {
        americano->status = 5;
    }
    else if (americano->status == 5)
    {
        americano->status = 0;
    }
    return 1;
}


int sovietico_atirar (movel *Sovietico)
{
    if (Sovietico->status == 1 || Sovietico->status == 0)
    {
        Mix_Volume( 1, 22);
        if( Mix_PlayChannel( 1, tiro, 0 ) == -1 )
        {
            return -1;
        }
        Sovietico->status = 2;
    }
    else if (Sovietico->status == 2)
    {
        Sovietico->status = 3;
    }
    else if (Sovietico->status == 3)
    {
        Sovietico->status = 4;
    }
    else if (Sovietico->status == 4)
    {
        Sovietico->status = 5;
    }
    else if (Sovietico->status == 5)
    {
        Sovietico->status = 0;
    }
    return 1;
}

void limpar() {
    SDL_FreeSurface(tela);
    SDL_FreeSurface(cursor_americano);
    SDL_FreeSurface(cursor_americano2);
    SDL_FreeSurface(cursor_americano3);
    SDL_FreeSurface(AmericanoA);
    SDL_FreeSurface(AmericanoA_anda);
    SDL_FreeSurface(AmericanoA_atira1);
    SDL_FreeSurface(AmericanoA_atira2);
    SDL_FreeSurface(AmericanoA_atira3);
    SDL_FreeSurface(AmericanoA_atirafinal);
    SDL_FreeSurface(AmericanoM);
    SDL_FreeSurface(AmericanoM_anda);
    SDL_FreeSurface(AmericanoM_atira1);
    SDL_FreeSurface(AmericanoM_atira2);
    SDL_FreeSurface(AmericanoM_atira3);
    SDL_FreeSurface(AmericanoM_atirafinal);
    SDL_FreeSurface(palito_anda1);
    SDL_FreeSurface(palito_anda2);
    SDL_FreeSurface(palito_anda3);
    SDL_FreeSurface(palito_anda4);
    SDL_FreeSurface(americano_atira3);
    SDL_FreeSurface(americano_atira4);
    SDL_FreeSurface(cursor_sovietico);
    SDL_FreeSurface(sovietico);
    SDL_FreeSurface(sovietico_anda);
    SDL_FreeSurface(sovietico_atira);
    SDL_FreeSurface(SovieticoF_atira2);
    SDL_FreeSurface(SovieticoF_atira3);
    SDL_FreeSurface(SovieticoF_atirafinal);
    SDL_FreeSurface(SovieticoA);
    SDL_FreeSurface(SovieticoA_anda);
    SDL_FreeSurface(SovieticoA_atira);
    SDL_FreeSurface(SovieticoA_atira2);
    SDL_FreeSurface(SovieticoA_atira3);
    SDL_FreeSurface(SovieticoA_atirafinal);
    SDL_FreeSurface(SovieticoM);
    SDL_FreeSurface(SovieticoM_anda);
    SDL_FreeSurface(SovieticoM_atira);
    SDL_FreeSurface(SovieticoM_atira2);
    SDL_FreeSurface(SovieticoM_atira3);
    SDL_FreeSurface(SovieticoM_atirafinal);
    SDL_FreeSurface(menu_imagem);
    SDL_FreeSurface(menu_conquistas);
    SDL_FreeSurface(menu_instrucoes);
    SDL_FreeSurface(fundo);
    SDL_FreeSurface(botao1);
    SDL_FreeSurface(botao1_p);
    SDL_FreeSurface(botao2);
    SDL_FreeSurface(botao2_p);
    SDL_FreeSurface(botao3);
    SDL_FreeSurface(botao3_p);
    SDL_FreeSurface(botao4);
    SDL_FreeSurface(botao4_p);
    SDL_FreeSurface(teste);
    SDL_FreeSurface(base1_teste);
    SDL_FreeSurface(base2_teste);
    SDL_FreeSurface(vida1_a);
    SDL_FreeSurface(vida1_b);
    SDL_FreeSurface(vida);
    SDL_FreeSurface(vida2_a);
    SDL_FreeSurface(vida2_b);
    SDL_FreeSurface(RIP);
    SDL_FreeSurface(Conquistas);
    SDL_FreeSurface(Custer);
    SDL_FreeSurface(Kill1);
    SDL_FreeSurface(Moscow);
    SDL_FreeSurface(Tokensx0);
    SDL_FreeSurface(Tokensx1);
    SDL_FreeSurface(Tokensx2);
    SDL_FreeSurface(Tokensx3);
    SDL_FreeSurface(Tokensx4);
    SDL_FreeSurface(Tokensx5);

    Mix_FreeMusic( mus_menu );
    Mix_FreeMusic( musica );
    Mix_FreeChunk( tiro );
    Mix_FreeChunk( tiro_2 );
    Mix_FreeChunk( tiro_3 );
    Mix_FreeChunk( entrada1 );
    Mix_FreeChunk( entrada2 );

    Mix_CloseAudio();

    TTF_Quit();

    SDL_Quit();
}

int contador (char Arquivo[], int n){
    int c;
    FILE *f;
    f = fopen(Arquivo, "r");
    if (f == NULL) {
        printf("Nao deu certo :(");
        return -1;
    } else {

    fscanf(f,"%d", &c);
    fclose(f);
    f = fopen(Arquivo, "w");
    c=c+n;
    fprintf(f,"%d",c);
    fclose(f);
    return 0;}


}

void danora(int j){
    int d,i,aux,ap=0,I,c=0,t=2,e=3;
    srand(time(NULL)+R*R);
    aux=j;
    R=R+2;

    while(t>0){
        while(j<=aux+4 && ap!=1){
            R=R+7;
            d=4+rand()%e;
            if(Mi[0][j]==121||Mi[0][j]==120){
                if(j%10==1){c=2;}
                for(I=c;I<6;I++){
                    R=R*3;
                    i=rand()%5;
                    if(Mi[i][j]!=0 && HP[i][j]>0){HP[i][j]=HP[i][j]-d;break;}
                }ap=1;}
        j++;
    }t--;}}
void danoaa(int j){
     int d=2,i,aux,ap=0,I,c=0,t=3,e=4;
    srand(time(NULL)+R*R);
    if(j==0 || j==5 || j==10){t=2;}
    else{t=3;}
    aux=j;
    R=R+2;
    while(t>0){
    while(j<=aux+4 && ap!=1){

        if(j==0 || j==5 || j==10){e=2;}

        d=d+rand()%e;

        R=R+7;
        if(Mi[0][j]==121||Mi[0][j]==120){
            if(j%10==1){c=0;}
            for(I=c;I<6;I++){
                R=R*3;
                i=rand()%5;
                if(Mi[i][j]!=0 && HP[i][j]>0){HP[i][j]=HP[i][j]-d;break;}
            }ap=1;}
    j++;
    }t--;}}
void danoma(int j){

    int d=3,i,aux,ap=0,I,c=0,t=2,e=2;
    srand(time(NULL)+R*R);

    if(j==0 || j==5 || j==10){t=3;}
    else{t=2;}

    aux=j;
    R=R+2;
    while(t>0){
    while(j<=aux+4 && ap!=1){
        R=R+7;
        if(Mi[0][j]==121||Mi[0][j]==120){
            if(j%10==1){c=2;}

            if(j==0 || j==5 || j==10){e=4;d=4;}

            d=d+rand()%e;

            for(I=c;I<6;I++){
                    R=R*3;
            i=rand()%5;
            if(Mi[i][j]!=0 && HP[i][j]>0){HP[i][j]=HP[i][j]-d;break;}
            }ap=1;}
    j++;
    }t--;}
}


void danors(int j){
    int d,i,aux,ap=0,I,c=0,t=2,e=3;
    srand(time(NULL)+R*R);
    aux=j;
    R=R+2;

    while(t>0){
        while(j>=aux-4 && ap!=1){
            R=R+7;
            d=4+rand()%e;
            if(Mi[0][j]==111||Mi[0][j]==110){
                if(j%10==1){c=2;}
                for(I=c;I<6;I++){
                    R=R*3;
                    i=rand()%5;
                    if(Mi[i][j]!=0 && HP[i][j]>0){HP[i][j]=HP[i][j]-d;break;}
                }ap=1;}
        j--;
    }t--;}}
void danoas(int j){
     int d=2,i,aux,ap=0,I,c=0,t=3,e=4;
    srand(time(NULL)+R*R);
    if(j==0 || j==5 || j==10){t=2;}
    else{t=3;}
    aux=j;
    R=R+2;
    while(t>0){
    while(j>=aux-4 && ap!=1){

        if(j==0 || j==5 || j==10){e=2;}

        d=d+rand()%e;

        R=R+7;
        if(Mi[0][j]==111||Mi[0][j]==110){
            if(j%10==1){c=0;}
            for(I=c;I<6;I++){
                R=R*3;
                i=rand()%5;
                if(Mi[i][j]!=0 && HP[i][j]>0){HP[i][j]=HP[i][j]-d;break;}
            }ap=1;}
    j--;;
    }t--;}}
void danoms(int j){

    int d=3,i,aux,ap=0,I,c=0,t=2,e=2;
    srand(time(NULL)+R*R);

    if(j==0 || j==5 || j==10){t=3;}
    else{t=2;}

    aux=j;
    R=R+2;
    while(t>0){
    while(j>=aux-4 && ap!=1){
        R=R+7;
        if(Mi[0][j]==111||Mi[0][j]==110){
            if(j%10==1){c=2;}
            if(j==0 || j==5 || j==10){e=4;d=4;}
            d=d+rand()%e;
            for(I=c;I<6;I++){
                R=R*3;
                i=rand()%5;
                if(Mi[i][j]!=0 && HP[i][j]>0){HP[i][j]=HP[i][j]-d;break;}
            }ap=1;}
    j--;
    }t--;}
}



void warzone(){
    int j;

    for(j=0;j<11;j++){if(Mi[0][j]/100==1){Mi[0][j]=Mi[0][j]-100;}}

    for(j=0;j<11;j++){                          //declarando as Warzones.
            if ((Mi[0][j]%100==10||Mi[0][j]%100==11)&&(Mi[0][j+1]%100==20||Mi[0][j+1]%100==21)){
                    if(Mi[0][j]<100){Mi[0][j]=Mi[0][j]+100;}
                    if(Mi[0][j+1]<100){Mi[0][j+1]=Mi[0][j+1]+100;}
    }}
    for(j=0;j<11;j++){                          //declarando as Warzones.
            if ((Mi[0][j]%100==10||Mi[0][j]%100==11)&&(Mi[0][j+2]%100==20||Mi[0][j+2]%100==21)){
                    if(Mi[0][j]<100){Mi[0][j]=Mi[0][j]+100;}
                    if(Mi[0][j+2]<100){Mi[0][j+2]=Mi[0][j+2]+100;}
    }}
    for(j=0;j<11;j++){                          //declarando as Warzones.
            if ((Mi[0][j]%100==10||Mi[0][j]%100==11)&&(Mi[0][j+3]%100==20||Mi[0][j+3]%100==21)){
                    if(Mi[0][j]<100){Mi[0][j]=Mi[0][j]+100;}
                    if(Mi[0][j+3]<100){Mi[0][j+3]=Mi[0][j+3]+100;}
    }}

    for(j=0;j<11;j++){                          //declarando as Warzones.
            if ((Mi[0][j]%100==10||Mi[0][j]%100==11)&&(Mi[0][j+4]%100==20||Mi[0][j+4]%100==21)){
                    if(Mi[0][j]<100){Mi[0][j]=Mi[0][j]+100;}
                    if(Mi[0][j+4]<100){Mi[0][j+4]=Mi[0][j+4]+100;}
    }}
}

void combate(){
    int j,i;
    int ra=0,aa=0,ma=0,rs=0,as=0,ms=0;

    for(j=0;j<=10;j++){                   //combate (ou tentariva de)
            if(Mi[0][j]/100==1){
                for(i=1;i<5;i++){
                    switch (Mi[i][j]){
                        case 11: ra++;break;
                        case 12: aa++;break;
                        case 13: ma++;break;
                        case 21: rs++;break;
                        case 22: as++;break;
                        case 23: ms++;break;
                        case 111: ra++;break;
                        case 112: aa++;break;
                        case 113: ma++;break;
                        case 121: rs++;break;
                        case 122: as++;break;
                        case 123: ms++;break;
                        }}
                while(ra>0){
                    ra--;
                    danora(j);
                }
               while(aa>0){
                    aa--;
                    danoaa(j);
                }
                while(ma>0){
                    ma--;
                    danoma(j);
                }
                while(rs>0){
                    rs--;
                    danors(j);
                }

                while(as>0){
                    as--;
                    danoas(j);
                }
                while(ms>0){
                    ms--;
                    danoms(j);
                }
            }}
ra=aa=ma=rs=as=ms=0;
}

void artilharia(int j){

    srand(time(NULL)+R*R);
    int d=3,i,aux,c=0,t,aux2;
    for(t=10;t>0;t--){
        d=d+rand()%5;
        R=R+7;
        aux=rand()%3;
        R=R+1;
        aux2=j+aux-1;
        if(aux2<10 || aux2>0){
            i=rand()%5;
            R=R*3;
            HP[i][aux2]=HP[i][aux2]-d;
    }}
    printf("\n\nArtilharia lançada!\n\n");
}

void obitos(map_fase *cenario){
    int j,i;
    char arch[7];
    for(j=10;j>=0;j--){
        if(HP[0][j]<0){HP[0][j]=0;}
        for(i=4;i>0;i--){
            if(HP[i][j]<=0){
                if(Mi[i][j] != 0)
                {
                    cenario[j].soldado[i].status5 = -1;
                }

                if(Mi[i][j]==11 || Mi[i][j]==111){select_Arch(1,1);}
                else if(Mi[i][j]==21 || Mi[i][j]==121){select_Arch(2,1);}
                else if(Mi[i][j]==12 || Mi[i][j]==112){select_Arch(3,1);}
                else if(Mi[i][j]==22 || Mi[i][j]==122){select_Arch(4,1);}
                else if(Mi[i][j]==13 || Mi[i][j]==113){select_Arch(5,1);}
                else if(Mi[i][j]==23 || Mi[i][j]==123){select_Arch(6,1);}

                Mi[i][j]=0;HP[i][j]=0;

                    }
}}}

int select_Arch(int i, int n){
    char arch[7];
    switch (i)
    {
        case 1: sprintf(arch, "ORA.txt"); contador(arch,n); break;          //Fuzileiros americanos mortos em combate
        case 2: sprintf(arch, "ORS.txt"); contador(arch,n); break;          //Fuzileiros sovietes mortos em combate
        case 3: sprintf(arch, "OAA.txt"); contador(arch,n); break;          //Assaltos americanos mortos em combate
        case 4: sprintf(arch, "OAS.txt"); contador(arch,n); break;          //Assaltos sovietes mortos em combate
        case 5: sprintf(arch, "OMA.txt"); contador(arch,n); break;          //Metralhadoras americanos mortos em combate
        case 6: sprintf(arch, "OMS.txt"); contador(arch,n); break;          //Metralhadoras sovietes mortos em combate
        case 7: sprintf(arch, "VIA.txt"); contador(arch,n); break;          //Total de vitórias estadunidenses (derrotas russas)
        case 8: sprintf(arch, "VIS.txt"); contador(arch,n); break;          //Total de vitórias russas (derrotas estadunidenses)
        case 9: sprintf(arch, "WMD.txt"); contador(arch,n); break;          //Dólares arrecadados no total
        case 10: sprintf(arch, "NRA.txt"); contador(arch,n); break;          //Fuzileiros americanos treinados no total
        case 11: sprintf(arch, "NRS.txt"); contador(arch,n); break;          //Fuzileiros sovietes treinados no total
        case 12: sprintf(arch, "NAA.txt"); contador(arch,n); break;          //Assaltos americanos treinados no total
        case 13: sprintf(arch, "NAS.txt"); contador(arch,n); break;          //Assaltos sovietes treinados no total
        case 14: sprintf(arch, "NMA.txt"); contador(arch,n); break;          //Metralhadoras americanos treinados no total
        case 15: sprintf(arch, "NMS.txt"); contador(arch,n); break;          //Metralhadoras sovietes treinados no total

    }
}

void check_checkpoints(){
    int i,j;
    for(j=0;j<10;j=j+5){                   //Ocidentais
        for(i=1;i<5;i++){
            if(Mi[i][j]/100==0 && Mi[i][j]%100!=0){Mi[i][j]=Mi[i][j]+100;}
}}}

void movimento(map_fase *cenario){
    int j,i,auxU,auxH;

    check_checkpoints();

        for(i=1;i<5;i++){                   //Ocidentais
            for(j=10;j>=0;j--){
                if(Mi[i][j]/100==0 && Mi[0][j]/100==0){if(Mi[i][j]/10==1){cenario[j].soldado[i].status4=10+i;
                    if(Mi[i][j+1]==0 && Mi[0][j]/10!=1){cenario[j+1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[i][j+1]=auxU;HP[i][j+1]=auxH;auxU=auxH=0;}
                    else if(Mi[1][j+1]==0){cenario[j+1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[1][j+1]=auxU;HP[1][j+1]=auxH;auxU=auxH=0;}
                    else if(Mi[2][j+1]==0){cenario[j+1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[2][j+1]=auxU;HP[2][j+1]=auxH;auxU=auxH=0;}
                    else if(Mi[3][j+1]==0){cenario[j+1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[3][j+1]=auxU;HP[3][j+1]=auxH;auxU=auxH=0;}
                    else if(Mi[4][j+1]==0){cenario[j+1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[4][j+1]=auxU;HP[4][j+1]=auxH;auxU=auxH=0;}
                }}}}

        for(i=1;i<5;i++){                                                       //aqui é o mecanismo de movimento dos soldados, contanto que eles estejam fora de um checkpoint.
            for(j=2;j<=10;j++){                                             //Orientais
                if(Mi[i][j]/100==0 && Mi[0][j]/100==0){if(Mi[i][j]/10==2){cenario[j].soldado[i].status4=10+i;
                    if(Mi[i][j-1]==0 && Mi[0][j]/10!=1){cenario[j-1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[i][j-1]=auxU;HP[i][j-1]=auxH;auxU=auxH=0;}
                    else if(Mi[1][j-1]==0){cenario[j-1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[1][j-1]=auxU;HP[1][j-1]=auxH;auxU=auxH=0;}
                    else if(Mi[2][j-1]==0){cenario[j-1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[2][j-1]=auxU;HP[2][j-1]=auxH;auxU=auxH=0;}
                    else if(Mi[3][j-1]==0){cenario[j-1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[3][j-1]=auxU;HP[3][j-1]=auxH;auxU=auxH=0;}
                    else if(Mi[4][j-1]==0){cenario[j-1].soldado[i].status3=20;auxU=Mi[i][j];Mi[i][j]=0;auxH=HP[i][j];HP[i][j]=0;Mi[4][j-1]=auxU;HP[4][j-1]=auxH;auxU=auxH=0;}
                }}}}}

void posse(){
    int i,j,am,ru;

       for(j=1;j<10;j++){                          //declarando posse de terreno. Se uma unidade múltipla de 20 está em um terreno, ele é russo, e vice e versa.
            am=ru=0;
            for(i=1;i<5;i++){
                if(Mi[i][j]/10==1 || Mi[i][j]/10==11){am=am+1;}
                if(Mi[i][j]/10==2 || Mi[i][j]/10==12){ru=ru+1;}
            }

            if(am>0){if(Mi[0][j]==1 || Mi[0][j]==0){Mi[0][j]=Mi[0][j]+10;}}
            else if(ru>0){if(Mi[0][j]==1 || Mi[0][j]==0){Mi[0][j]=Mi[0][j]+20;}}
            else{if(Mi[0][j]%10==1){Mi[0][j]=1;}else if(Mi[0][j]%10==0){Mi[0][j]=0;}}

        }
}

int AIscan(){
    int stance=0,pridef,priatk,posi;
    int j,i;
    int ra=0,aa=0,ma=0,rs=0,as=0,ms=0;

    for(j=0;j<=10;j++){
            if(Mi[0][j]/100==1){
                for(i=1;i<5;i++){
                    switch (Mi[i][j]){
                        case 11: ra++;break;
                        case 12: aa++;break;
                        case 13: ma++;break;
                        case 21: rs++;break;
                        case 22: as++;break;
                        case 23: ms++;break;
                        }}}}

    if(Mi[0][5]/10==0){
        posi=0;
    }
    else if(Mi[0][5]/10==1 || Mi[0][6]/10==1 || Mi[0][4]/10==1){
        posi=1;
    }
    else if(Mi[0][5]/10==2){
        posi=2;
    }
    if(aa>=ma && aa>=ra && posi==1){stance=1;}            //postura 1: comprar metralhadoras e manter a base
    else if(aa>=ma && aa>=ra && posi==0){stance=2;}       //postura 2: comprar assaltos e conquistar terreno
    else if(ma>=aa && ma>=ra && posi==2){stance=3;}       //postura 3: comprar fuzileiros e invadir a base inimiga
    else if(ra>=ma && ra>=aa && posi==1){stance=4;}       //postura 4: comprar fuzileiros e tomar o checkpoint
    else if(aa>=ma && aa>=ra && posi==2){stance=5;}       //postura 5: comprar metralhadoras e manter o checkpoint
    else if(posi==2){stance=3;}                         //postura 3: (again, para ele continuar tentando)

    return stance;
}


void atualizar_dados(fase *cenario, map_fase *cenario_m)
{
    int i, j;
    for (i=0; i<11; i++)
    {
        cenario_m[i].tipo = Mi[0][i]%10;//Verifica se é checkpoint
        if (Mi[0][i] < 100)
        {
            cenario_m[i].status = 0;//Verifica se é warzone
            cenario_m[i].posse = Mi[0][i]/10;//Verifica se o terreno é de alguem
        }
        else
        {
            cenario_m[i].status = 100;//Verifica o mesmo no caso de warzone
            cenario_m[i].posse = Mi[0][i]%100;
            cenario_m[i].posse = cenario_m[i].posse/10;
        }
        for (j=0; j<4; j++)
        {
            cenario_m[i].unidade[j] = Mi[j+1][i]%10;//Verifica qual a unidade dos soldados
            cenario_m[i].HP[j] = HP[j+1][i];//Verifica o HP dos soldados
        }
    }
    cenario->base1 = HP[0][0];
    cenario->base2 = HP[0][10];
}


void fase1_preparar(fase *fase1)
{
    int i, j;
    fase1->Dollar=0;fase1->Rublo=0;fase1->act=1;
    fase1->e=0;

    srand(time(NULL)+R*R);
    for(i=0;i<=4;i++){           //partida iniciada!
        for(j=0;j<=11;j++){
            Mi[i][j]=0;HP[i][j]=0;
        }
    }
    Mi[0][0]=11;Mi[0][5]=1;Mi[0][10]=21;HP[0][0]=200;HP[0][10]=200;
    fase1->Dollar=18;fase1->Rublo=18;
    //essas são as posições que representam Checkpoints.
    fase1->col = 11;
    fase1->tempo.t1 = SDL_GetTicks();
}

void fase1_preparar2(map_fase *fase1)
{
    int i, j;

    for (i=0; i<11; i++)
    {
        fase1[i].posicao = i*SCREEN_WIDTH/12+20;
        fase1[i].posse = 0;
        fase1[i].status = 0;
        fase1[i].tipo = 0;
        if (i==0)
        {
            fase1[i].tipo = 1;
            fase1[i].posse = 1;
        }
        else if (i==5)
        {
            fase1[i].tipo = 1;
        }
        else if (i==10)
        {
            fase1[i].tipo = 1;
            fase1[i].posse = 2;
        }
        for (j=0; j<4; j++)
        {
            declarar_movel(&fase1[i].soldado[j]);
            fase1[i].HP[j] = 0;
            fase1[i].unidade[j] = 0;
            fase1[i].unidade_s[j] = 0;
            fase1[i].soldado[j].x = fase1[i].posicao + 30*j;
            fase1[i].soldado[j].y = 90 + j*30;
            fase1[i].soldado[j].x_a = fase1[i].posicao + 30*j;
            fase1[i].soldado[j].y_a = 90 + j*30;
            fase1[i].soldado[j].velx = (fase1[i].posicao-fase1[i-1].posicao)/4;
            fase1[i].soldado[j].vely = 0;
            fase1[i].soldado[j].status = 0;
            fase1[i].soldado[j].status2 = 0;
            fase1[i].soldado[j].status3 = 0;
            fase1[i].soldado[j].status4 = 0;
            fase1[i].soldado[j].tempo.t1 = SDL_GetTicks();
        }
    }
}

int aplicar_soldados (fase *Fase, map_fase *Fase_m, movel *americanos, movel *sovieticos)
{
    int i, j, k, Dollar;

//status4 > 10 se o soldado que se movimentou estava nessa posição
//status3 = 20 se o soldado se movimentou para lá
//status3 = 1 se não houve movimento
//status5 = -1 se alguem morreu

    for (i=0; i<Fase->col; i++)
    {
        for (j=0; j<4; j++)
        {
            if(Fase_m[i].posse == 1)//Para americanos
            {
                if (Fase_m[i].unidade[j] == 1 || Fase_m[i].unidade[j] == -9)
                //Ta erradooooo preciso colocar todas as unidades separadas
                {
                    Fase_m[i].soldado[j].altura = americanos[0].altura;
                    Fase_m[i].soldado[j].largura = americanos[0].largura;
                    Fase_m[i].soldado[j].velx = americanos[0].velx;
                    Fase_m[i].soldado[j].vely = 0;
                    Fase_m[i].soldado[j].icone = americanos[0].icone;
                    Fase_m[i].soldado[j].status2 = 1;
                    for (k=0; k<6; k++)
                    {
                        Fase_m[i].soldado[j].sprite[k] = americanos[0].sprite[k];
                    }
                    if (Fase_m[i].soldado[j].status3 == 20)  //Problema nas animações
                    {
                        for (k=0;k<4;k++)
                        {
                            if (Fase_m[i-1].soldado[k].status4 > 10)
                            {
                                Fase_m[i].soldado[j].y = Fase_m[i-1].soldado[k].y;
                                Fase_m[i].soldado[j].x = Fase_m[i-1].soldado[k].x;
                                Fase_m[i-1].soldado[k].status4 = 0;
                                k=10+k;
                            }
                        }
                        if (Fase_m[i].soldado[j].x < Fase_m[i].soldado[j].x_a)
                        {
                            Fase_m[i].soldado[j].x = Fase_m[i-1].posicao;
                            Fase_m[i].soldado[j].velx = (Fase_m[i].soldado[j].x_a-Fase_m[i].soldado[j].x)/4;
                        }
                        Fase_m[i].soldado[j].vely = (Fase_m[i].soldado[j].y_a-Fase_m[i-1].soldado[k-10].y)/4;
                        Fase_m[i].soldado[j].status = 0;
                        Fase_m[i].soldado[j].status3 = 1;
                    }
                    else
                    {
                        if (Fase_m[i].soldado[j].status3 == 1)
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 250 && Fase_m[i].soldado[j].status5 != -1)//americanos andam
                            {
                                americano_anda(&Fase_m[i].soldado[j]);
                                movimento_SDL(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                        else if (Fase_m[i].status != 100)//americanos parados
                        {
                            Fase_m[i].soldado[j].status = 0;
                            /*Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 500)//americanos andam parados
                            {
                                americano_anda(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }*/
                            Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                        }
                        else//americanos atiram
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 100)
                            {
                                Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                                americano_atirar(&Fase_m[i].soldado[j], 1);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                    }
                }
                else if ( Fase_m[i].unidade[j] == 2 || Fase_m[i].unidade[j] == -8 )
                {
                    Fase_m[i].soldado[j].altura = americanos[1].altura;
                    Fase_m[i].soldado[j].largura = americanos[1].largura;
                    Fase_m[i].soldado[j].velx = americanos[1].velx;
                    Fase_m[i].soldado[j].vely = 0;
                    Fase_m[i].soldado[j].icone = americanos[1].icone;
                    Fase_m[i].soldado[j].status2 = 1;
                    for (k=0; k<6; k++)
                    {
                        Fase_m[i].soldado[j].sprite[k] = americanos[1].sprite[k];
                    }
                    if (Fase_m[i].soldado[j].status3 == 20)  //Problema nas animações
                    {
                        for (k=0;k<4;k++)
                        {
                            if (Fase_m[i-1].soldado[k].status4 > 10)
                            {
                                Fase_m[i].soldado[j].y = Fase_m[i-1].soldado[k].y;
                                Fase_m[i].soldado[j].x = Fase_m[i-1].soldado[k].x;
                                Fase_m[i-1].soldado[k].status4 = 0;
                                k=10+k;
                            }
                        }
                        if (Fase_m[i].soldado[j].x < Fase_m[i].soldado[j].x_a)
                        {
                            Fase_m[i].soldado[j].x = Fase_m[i-1].posicao;
                            Fase_m[i].soldado[j].velx = (Fase_m[i].soldado[j].x_a-Fase_m[i].soldado[j].x)/4;
                        }
                        Fase_m[i].soldado[j].vely = (Fase_m[i].soldado[j].y_a-Fase_m[i-1].soldado[k-10].y)/4;
                        Fase_m[i].soldado[j].status = 0;
                        Fase_m[i].soldado[j].status3 = 1;
                    }
                    else
                    {
                        if (Fase_m[i].soldado[j].status3 == 1)
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 250 && Fase_m[i].soldado[j].status5 != -1)//americanos andam
                            {
                                americano_anda(&Fase_m[i].soldado[j]);
                                movimento_SDL(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                        else if (Fase_m[i].status != 100)//americanos parados
                        {
                            Fase_m[i].soldado[j].status = 0;
                            /*Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 500)//americanos andam parados
                            {
                                americano_anda(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }*/
                            Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                        }
                        else//americanos atiram
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 100)
                            {
                                Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                                americano_atirar(&Fase_m[i].soldado[j], 2);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                    }
                }
                else if (Fase_m[i].unidade[j] == 3|| Fase_m[i].unidade[j] == -7)
                //Ta erradooooo preciso colocar todas as unidades separadas
                {
                    Fase_m[i].soldado[j].altura = americanos[2].altura;
                    Fase_m[i].soldado[j].largura = americanos[2].largura;
                    Fase_m[i].soldado[j].velx = americanos[2].velx;
                    Fase_m[i].soldado[j].vely = 0;
                    Fase_m[i].soldado[j].icone = americanos[2].icone;
                    Fase_m[i].soldado[j].status2 = 1;
                    for (k=0; k<6; k++)
                    {
                        Fase_m[i].soldado[j].sprite[k] = americanos[2].sprite[k];
                    }
                    if (Fase_m[i].soldado[j].status3 == 20)  //Problema nas animações
                    {
                        for (k=0;k<4;k++)
                        {
                            if (Fase_m[i-1].soldado[k].status4 > 10)
                            {
                                Fase_m[i].soldado[j].y = Fase_m[i-1].soldado[k].y;
                                Fase_m[i].soldado[j].x = Fase_m[i-1].soldado[k].x;
                                Fase_m[i-1].soldado[k].status4 = 0;
                                k=10+k;
                            }
                        }
                        if (Fase_m[i].soldado[j].x < Fase_m[i].soldado[j].x_a)
                        {
                            Fase_m[i].soldado[j].x = Fase_m[i-1].posicao;
                            Fase_m[i].soldado[j].velx = (Fase_m[i].soldado[j].x_a-Fase_m[i].soldado[j].x)/4;
                        }
                        Fase_m[i].soldado[j].vely = (Fase_m[i].soldado[j].y_a-Fase_m[i-1].soldado[k-10].y)/4;
                        Fase_m[i].soldado[j].status = 0;
                        Fase_m[i].soldado[j].status3 = 1;
                    }
                    else
                    {
                        if (Fase_m[i].soldado[j].status3 == 1)
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 250 && Fase_m[i].soldado[j].status5 != -1)//americanos andam
                            {
                                americano_anda(&Fase_m[i].soldado[j]);
                                movimento_SDL(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                        else if (Fase_m[i].status != 100)//americanos parados
                        {
                            Fase_m[i].soldado[j].status = 0;
                            /*Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 500)//americanos andam parados
                            {
                                americano_anda(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }*/
                            Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                        }
                        else//americanos atiram
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 100)
                            {
                                Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                                americano_atirar(&Fase_m[i].soldado[j], 3);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                    }
                }
                else//Zera tudo caso não tenha ninguem no terreno
                {
                    Fase_m[i].soldado[j].status = 0;
                    Fase_m[i].soldado[j].status2 = 0;
                    Fase_m[i].soldado[j].status3 = 0;
                }
            }
            else if (Fase_m[i].posse == 2)//Para soviéticos
            {
                if (Fase_m[i].unidade[j] == 1|| Fase_m[i].unidade[j] == -9)
                //Ta erradooooo preciso colocar todas as unidades separadas
                {
                    Fase_m[i].soldado[j].altura = sovieticos[0].altura;
                    Fase_m[i].soldado[j].largura = sovieticos[0].largura;
                    Fase_m[i].soldado[j].velx = sovieticos[0].velx;
                    Fase_m[i].soldado[j].vely = 0;
                    Fase_m[i].soldado[j].icone = sovieticos[0].icone;
                    Fase_m[i].soldado[j].status2 = 1;
                    for (k=0; k<6; k++)
                    {
                        Fase_m[i].soldado[j].sprite[k] = sovieticos[0].sprite[k];
                    }
                    if (Fase_m[i].soldado[j].status3 == 20)  //Problema nas animações
                    {
                        for (k=0;k<4;k++)
                        {
                            if (Fase_m[i+1].soldado[k].status4 > 10)
                            {
                                Fase_m[i].soldado[j].y = Fase_m[i+1].soldado[k].y;
                                Fase_m[i].soldado[j].x = Fase_m[i+1].soldado[k].x;
                                Fase_m[i+1].soldado[k].status4 = 0;
                                k=10+k;
                            }
                        }
                        if (Fase_m[i].soldado[j].x > Fase_m[i].soldado[j].x_a)
                        {
                            Fase_m[i].soldado[j].x = Fase_m[i+1].posicao;
                            Fase_m[i].soldado[j].velx = (Fase_m[i].soldado[j].x_a-Fase_m[i].soldado[j].x)/4;
                        }
                        Fase_m[i].soldado[j].vely = (Fase_m[i].soldado[j].y_a-Fase_m[i+1].soldado[k-10].y)/4;
                        Fase_m[i].soldado[j].status = 0;
                        Fase_m[i].soldado[j].status3 = 1;
                    }
                    else
                    {
                        if (Fase_m[i].soldado[j].status3 == 1)
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 250 && Fase_m[i].soldado[j].status5 != -1)//sovieticos andam
                            {
                                sovietico_andar(&Fase_m[i].soldado[j]);
                                movimento_SDL(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                        else if (Fase_m[i].status != 100)//sovieticos parados
                        {
                            Fase_m[i].soldado[j].status = 0;
                            /*Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 500)
                            {
                                sovietico_andar(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }*/
                            Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                        }
                        else//sovieticos atiram
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 100)
                            {
                                Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                                sovietico_atirar(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                    }
                }
                else if (Fase_m[i].unidade[j] == 2 ||Fase_m[i].unidade[j] == -8)
                //Ta erradooooo preciso colocar todas as unidades separadas
                {
                    Fase_m[i].soldado[j].altura = sovieticos[1].altura;
                    Fase_m[i].soldado[j].largura = sovieticos[1].largura;
                    Fase_m[i].soldado[j].velx = sovieticos[1].velx;
                    Fase_m[i].soldado[j].vely = 0;
                    Fase_m[i].soldado[j].icone = sovieticos[1].icone;
                    Fase_m[i].soldado[j].status2 = 1;
                    for (k=0; k<6; k++)
                    {
                        Fase_m[i].soldado[j].sprite[k] = sovieticos[1].sprite[k];
                    }
                    if (Fase_m[i].soldado[j].status3 == 20)  //Problema nas animações
                    {
                        for (k=0;k<4;k++)
                        {
                            if (Fase_m[i+1].soldado[k].status4 > 10)
                            {
                                Fase_m[i].soldado[j].y = Fase_m[i+1].soldado[k].y;
                                Fase_m[i].soldado[j].x = Fase_m[i+1].soldado[k].x;
                                Fase_m[i+1].soldado[k].status4 = 0;
                                k=10+k;
                            }
                        }
                        if (Fase_m[i].soldado[j].x > Fase_m[i].soldado[j].x_a)
                        {
                            Fase_m[i].soldado[j].x = Fase_m[i+1].posicao;
                            Fase_m[i].soldado[j].velx = (Fase_m[i].soldado[j].x_a-Fase_m[i].soldado[j].x)/4;
                        }
                        Fase_m[i].soldado[j].vely = (Fase_m[i].soldado[j].y_a-Fase_m[i+1].soldado[k-10].y)/4;
                        Fase_m[i].soldado[j].status = 0;
                        Fase_m[i].soldado[j].status3 = 1;
                    }
                    else
                    {
                        if (Fase_m[i].soldado[j].status3 == 1)
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 250 && Fase_m[i].soldado[j].status5 != -1)//sovieticos andam
                            {
                                sovietico_andar(&Fase_m[i].soldado[j]);
                                movimento_SDL(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                        else if (Fase_m[i].status != 100)//sovieticos parados
                        {
                            Fase_m[i].soldado[j].status = 0;
                            /*Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 500)
                            {
                                sovietico_andar(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }*/
                            Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                        }
                        else//sovieticos atiram
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 100)
                            {
                                Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                                sovietico_atirar(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                    }
                }
                else if (Fase_m[i].unidade[j] == 3|| Fase_m[i].unidade[j] == -7)
                //Ta erradooooo preciso colocar todas as unidades separadas
                {
                    Fase_m[i].soldado[j].altura = sovieticos[2].altura;
                    Fase_m[i].soldado[j].largura = sovieticos[2].largura;
                    Fase_m[i].soldado[j].velx = sovieticos[2].velx;
                    Fase_m[i].soldado[j].vely = 0;
                    Fase_m[i].soldado[j].icone = sovieticos[2].icone;
                    Fase_m[i].soldado[j].status2 = 1;
                    for (k=0; k<6; k++)
                    {
                        Fase_m[i].soldado[j].sprite[k] = sovieticos[2].sprite[k];
                    }
                    if (Fase_m[i].soldado[j].status3 == 20)  //Problema nas animações
                    {
                        for (k=0;k<4;k++)
                        {
                            if (Fase_m[i+1].soldado[k].status4 > 10)
                            {
                                Fase_m[i].soldado[j].y = Fase_m[i+1].soldado[k].y;
                                Fase_m[i].soldado[j].x = Fase_m[i+1].soldado[k].x;
                                Fase_m[i+1].soldado[k].status4 = 0;
                                k=10+k;
                            }
                        }
                        if (Fase_m[i].soldado[j].x > Fase_m[i].soldado[j].x_a)
                        {
                            Fase_m[i].soldado[j].x = Fase_m[i+1].posicao;
                            Fase_m[i].soldado[j].velx = (Fase_m[i].soldado[j].x_a-Fase_m[i].soldado[j].x)/4;
                        }
                        Fase_m[i].soldado[j].vely = (Fase_m[i].soldado[j].y_a-Fase_m[i+1].soldado[k-10].y)/4;
                        Fase_m[i].soldado[j].status = 0;
                        Fase_m[i].soldado[j].status3 = 1;
                    }
                    else
                    {
                        if (Fase_m[i].soldado[j].status3 == 1)
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 250 && Fase_m[i].soldado[j].status5 != -1)//sovieticos andam
                            {
                                sovietico_andar(&Fase_m[i].soldado[j]);
                                movimento_SDL(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                        else if (Fase_m[i].status != 100)//sovieticos parados
                        {
                            Fase_m[i].soldado[j].status = 0;
                            /*Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 500)
                            {
                                sovietico_andar(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }*/
                            Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                        }
                        else//sovieticos atiram
                        {
                            Fase_m[i].soldado[j].tempo.t2 = SDL_GetTicks();
                            if (Fase_m[i].soldado[j].tempo.t2 - Fase_m[i].soldado[j].tempo.t1 > 100)
                            {
                                Fase_m[i].soldado[j].x = Fase_m[i].posicao + j*30;
                                sovietico_atirar(&Fase_m[i].soldado[j]);
                                Fase_m[i].soldado[j].tempo.t1 = SDL_GetTicks();
                            }
                        }
                    }
                }
                else
                {
                    Fase_m[i].soldado[j].status = 0;
                    Fase_m[i].soldado[j].status2 = 0;
                    Fase_m[i].soldado[j].status3 = 0;
                }
            }
            else
            {
                Fase_m[i].soldado[j].status = 0;
                Fase_m[i].soldado[j].status2 = 0;
                Fase_m[i].soldado[j].status3 = 0;
            }
        }
    }
    for (j=0; j<4; j++)
    {
        for(i=0; i<Fase->col; i++)
        {
            if (Fase_m[i].soldado[j].status5 == -1)
            {
                aplicar_superficie(Fase_m[i].soldado[j].x, Fase_m[i].soldado[j].y, RIP, tela, NULL);
            }
            if (Fase_m[i].posse == 1)//Para americanos
            {
                if (Fase_m[i].soldado[j].status2 == 1)
                {
                    if (Fase_m[i].soldado[j].status3 == 1)
                    {
                        aplicar_superficie(Fase_m[i].soldado[j].x+30*j, Fase_m[i].soldado[j].y, Fase_m[i].soldado[j].sprite[Fase_m[i].soldado[j].status], tela, NULL);
                        aplicar_superficie(Fase_m[i].soldado[j].x+30*j-20, Fase_m[i].soldado[j].y+30, Fase_m[i].soldado[j].icone, tela, NULL);
                        if (Fase_m[i].soldado[j].x >= Fase_m[i].posicao)
                        {
                            Fase_m[i].soldado[j].status3 = 0;
                        }
                        Fase_m[i].soldado[j].status2 = 0;
                    }
                    else if (Fase_m[i].soldado[j].status3 == 0)
                    {
                        aplicar_superficie(Fase_m[i].soldado[j].x, Fase_m[i].soldado[j].y, Fase_m[i].soldado[j].sprite[Fase_m[i].soldado[j].status], tela, NULL);
                        aplicar_superficie(Fase_m[i].soldado[j].x-20, Fase_m[i].soldado[j].y+30, Fase_m[i].soldado[j].icone, tela, NULL);
                        Fase_m[i].soldado[j].status2 = 0;
                    }
                }
            }
            else
            {
                if (Fase_m[i].soldado[j].status2 == 1)
                {
                    if (Fase_m[i].soldado[j].status3 == 1)
                    {
                        aplicar_superficie(Fase_m[i].soldado[j].x+30*j, Fase_m[i].soldado[j].y, Fase_m[i].soldado[j].sprite[Fase_m[i].soldado[j].status], tela, NULL);
                        //aplicar_superficie(Fase_m[i].soldado[j].x+30*j+Fase_m[i].soldado[j].largura, Fase_m[i].soldado[j].y+30, Fase_m[i].soldado[j].icone, tela, NULL);
                        if (Fase_m[i].soldado[j].x <= Fase_m[i].posicao)
                        {
                            Fase_m[i].soldado[j].status3 = 0;
                        }
                        Fase_m[i].soldado[j].status2 = 0;
                    }
                    else if (Fase_m[i].soldado[j].status3 == 0)
                    {
                        aplicar_superficie(Fase_m[i].soldado[j].x, Fase_m[i].soldado[j].y, Fase_m[i].soldado[j].sprite[Fase_m[i].soldado[j].status], tela, NULL);
                        //aplicar_superficie(Fase_m[i].soldado[j].x+Fase_m[i].soldado[j].largura, Fase_m[i].soldado[j].y+30, Fase_m[i].soldado[j].icone, tela, NULL);
                        Fase_m[i].soldado[j].status2 = 0;
                    }
                }
            }
        }
    }
    return 1;
}

void aplicar_interface (fase *cenario)
{
    int i, j, k, Dollar;

    /*if (cenario->base1 > 180)//apliicar vida
    {
        aplicar_superficie(4,330,vida1_a,tela,NULL);
    }
    else if (cenario->base1 > 140)//apliicar vida
    {
        aplicar_superficie(4,330,vida1_b,tela,NULL);
    }
    else if (cenario->base1 > 80)//apliicar vida
    {
        aplicar_superficie(4,330,vida1_c,tela,NULL);
    }
    else if (cenario->base1 > 40)//apliicar vida
    {
        aplicar_superficie(4,330,vida1_d,tela,NULL);
    }
    else//apliicar vida
    {
        aplicar_superficie(4,330,vida,tela,NULL);
    }*/
    aplicar_superficie(cenario->base1-143,350,vida1_b,tela,NULL);
    if (cenario->base1 > 50)
    {
        aplicar_superficie(0,330,vida1_a,tela,NULL);
    }
    else
    {
        aplicar_superficie(0,330,vida,tela,NULL);
    }
    aplicar_superficie(1265-cenario->base2,351,vida2_b,tela,NULL);
    if (cenario->base2 > 50)
    {
        aplicar_superficie(1248,330,vida2_a,tela,NULL);
    }
    else
    {
        aplicar_superficie(1248,330,vida,tela,NULL);
    }
    /*if (cenario->base2 > 180)//apliicar vida
    {
        aplicar_superficie(1000,330,vida2_a,tela,NULL);
    }
    else if (cenario->base2 > 140)//apliicar vida
    {
        aplicar_superficie(1000,330,vida2_b,tela,NULL);
    }
    else if (cenario->base2 > 80)//apliicar vida
    {
        aplicar_superficie(1000,330,vida2_c,tela,NULL);
    }
    else if (cenario->base2 > 40)//apliicar vida
    {
        aplicar_superficie(1000,330,vida2_d,tela,NULL);
    }
    else//apliicar vida
    {
        aplicar_superficie(1000,330,vida,tela,NULL);
    }*/
    for (i=0; i<5; i++)
    {
        for (j=0; j<11; j++)
        {
            k = 1000+27*j;
            if (i==0)
            {
                if (Mi[i][j]/10 == 1)
                {
                    aplicar_superficie(k,490+(20*i),base1_teste,tela,NULL);//Mostrar posição na matriz
                }
                else if (Mi[i][j]%100 == 11 || Mi[i][j]%100 == 10)
                {
                    aplicar_superficie(k,490+(20*i),base1_teste,tela,NULL);//Mostrar posição na matriz
                }
                else if (Mi[i][j]/10 == 2)
                {
                    aplicar_superficie(k,490+(20*i),base2_teste,tela,NULL);//Mostrar posição na matriz
                }
                        else if (Mi[i][j]%100 == 21 || Mi[i][j]%100 == 20)
                {
                    aplicar_superficie(k,490+(20*i),base2_teste,tela,NULL);//Mostrar posição na matriz
                }
            }
            else if (Mi[i][j] != 0)
            {
                aplicar_superficie(k,490+(20*i),teste,tela,NULL);//Mostrar posição na matriz
            }
        }
    }
    Dollar = cenario->Dollar;
    if (Dollar >= 65)
    {
        aplicar_superficie(350,360,Tokensx5,tela,NULL);//Verificar dinheiro
    }
    else if (Dollar >= 52)
    {
        aplicar_superficie(350,360,Tokensx4,tela,NULL);//Verificar dinheiro
    }
    else if (Dollar >= 39)
    {
        aplicar_superficie(350,360,Tokensx3,tela,NULL);//Verificar dinheiro
    }
    else if (Dollar >= 26)
    {
        aplicar_superficie(350,360,Tokensx2,tela,NULL);//Verificar dinheiro
    }
    else if (Dollar >= 13)
    {
        aplicar_superficie(350,360,Tokensx1,tela,NULL);//Verificar dinheiro
    }
    else
    {
        aplicar_superficie(350,360,Tokensx0,tela,NULL);
    }
}

void fase1(fase *Fase1, map_fase *Fase1_m, movel *menu){

    int i, j,turno,Dollar=0,Rublo=0,auxU,auxH,stance,act=1;
    srand(time(NULL)+R*R);

    Dollar = Fase1->Dollar;
    Rublo = Fase1->Rublo;
    act = Fase1->act;
    auxU = Fase1->auxU;
    auxH = Fase1->auxH;

    Fase1->tempo.t2 = SDL_GetTicks();
    if (Fase1->tempo.t2 - Fase1->tempo.t1 > 1000)
    {
        for (i=0; i<Fase1->col; i++)
        {
            for (j=0; j<4; j++)
            {
                //Fase1_m[i].soldado[j].status = 0;Talvez dê erro na animação
                Fase1_m[i].soldado[j].status2 = 0;
                Fase1_m[i].soldado[j].status3 = 0;
                Fase1_m[i].soldado[j].status4 = 0;
                Fase1_m[i].soldado[j].status5 = 0;
            }
        }
        warzone();

        combate();

        movimento(Fase1_m);

        obitos(Fase1_m);

        posse();



        Dollar=Dollar+3;
        select_Arch(9,3);
        Rublo=Rublo+3;

        if(Mi[0][5]/10==1 || Mi[0][6]/10==1 || Mi[0][7]/10==1 || Mi[0][8]/10==1){Dollar=Dollar-2;Rublo=Rublo+1;select_Arch(9,-1);}
        if(Mi[0][5]/10==2 || Mi[0][4]/10==2 || Mi[0][3]/10==2 || Mi[0][2]/10==2){Rublo=Rublo-2;Dollar=Dollar+1;select_Arch(9,1);}

    stance=AIscan();
        i=0;
        if (stance==1){
                printf("Stance %d\n",stance);
            while(Mi[i][10]!=0){i++;}
            if(i<5 && Rublo>=12){
        Mix_Volume( 5, 30);
        Mix_PlayChannel(5, entrada2, 0);
                    Mi[i][10]=23;HP[i][10]=20;Rublo=Rublo-12;select_Arch(15,1);}
        }
        else if(stance==0){
            printf("Stance %d\n",stance);
            while(Mi[i][10]!=0){i++;}
            if(i<5 && Rublo>=12){
        Mix_Volume( 5, 30);
        Mix_PlayChannel(5, entrada2, 0);
                    Mi[i][10]=21;HP[i][10]=20;Rublo=Rublo-12;select_Arch(11,1);}

            j=10;                       //tirando os russos de suas bases (nota-se que eles andam um espaço a mais, no total)
                            for(i=1;i<5;i++){
                                if(Mi[i][j]/100==1){
                                    Mi[i][j]=Mi[i][j]-200;
                        }}
        }
        else if(stance==2){
                printf("Stance %d\n",stance);
            while(Mi[i][10]!=0){i++;}
                if(i<5 && Rublo>=12){
        Mix_Volume( 5, 30);
        Mix_PlayChannel(5, entrada2, 0);
                        Mi[i][10]=22;HP[i][10]=20;Rublo=Rublo-12;select_Arch(13,1);}

                j=10;                       //tirando os russos de suas bases (nota-se que eles andam um espaço a mais, no total)
                            for(i=1;i<5;i++){
                                if(Mi[i][j]/100==1){
                                    Mi[i][j]=Mi[i][j]-200;
                        }}
        }
        else if(stance==3){
                printf("Stance %d\n",stance);
            while(Mi[i][10]!=0){i++;}
            if(i<5 && Rublo>=12){
        Mix_Volume( 5, 30);
        Mix_PlayChannel(5, entrada2, 0);
                    Mi[i][10]=21;HP[i][10]=20;Rublo=Rublo-12;select_Arch(11,1);}
                j=10;
                            for(i=1;i<5;i++){
                                if(Mi[i][j]/100==1){
                                    Mi[i][j]=Mi[i][j]-200;
                        }}                       //tirando os russos de suas bases (nota-se que eles andam um espaço a mais, no total)
                    j=5;
                            for(i=1;i<5;i++){
                                if(Mi[i][j]/100==1){
                                    Mi[i][j]=Mi[i][j]-200;
                        }}
        }
        else if(stance==4){
            while(Mi[i][10]!=0){i++;}
                if(i<5 && Rublo>=12){
        Mix_Volume( 5, 30);
        Mix_PlayChannel(5, entrada2, 0);
                        Mi[i][10]=21;HP[i][10]=20;Rublo=Rublo-12;select_Arch(11,1);}
                j=10;                       //tirando os russos de suas bases (nota-se que eles andam um espaço a mais, no total)
                            for(i=1;i<5;i++){
                                if(Mi[i][j]/100==1){
                                    Mi[i][j]=Mi[i][j]-200;
                        }}
        }
        else if(stance==5){
            while(Mi[i][10]!=0){i++;}
                if(i<5 && Rublo>=12){
        Mix_Volume( 5, 30);
        Mix_PlayChannel(5, entrada2, 0);
                        Mi[i][10]=23;HP[i][10]=20;Rublo=Rublo-12;select_Arch(15,1);}
                j=10;                       //tirando os russos de suas bases (nota-se que eles andam um espaço a mais, no total)
                            for(i=1;i<5;i++){
                                if(Mi[i][j]/100==1){
                                    Mi[i][j]=Mi[i][j]-200;
                        }}
        }
        Fase1->tempo.t1 = SDL_GetTicks();
    }

    atualizar_dados(Fase1,Fase1_m);
    Fase1->Dollar = Dollar;
    Fase1->Rublo = Rublo;
    Fase1->stance = stance;
    Fase1->act = act;
    Fase1->turno = turno;

    if (HP[0][0]<=0 || HP[0][10]<=0)
    {
        menu->status = 1;
        Mix_HaltMusic();
        fase1_preparar(Fase1);
        fase1_preparar2(Fase1_m);
        //Game Over
    }

    /*if(HP[0][10]<=0){
            select_Arch(7, 1);
            printf("\n\n\n Os sovietes foram derrotados!");
    }
    else if(HP[0][0]<=0){
            select_Arch(8, 1);
            printf("\n\n\n Os americanos foram derrotados!");
    }*/
}

void comando_batalha(fase *cenario,map_fase *cenario_m, movel *menu, movel comprar[])
{
    int i, j, auxU, auxH;
    i=1;
    if( evento.type == SDL_KEYDOWN ){
    if(evento.key.keysym.sym == SDLK_1)
    {
        while(Mi[i][0]!=0){i++;}
        if(i<5 && cenario->Dollar>=13)
        {
                Mix_Volume( 4, 30);
                Mix_PlayChannel( 4, entrada1, 0 );
                Mi[i][0]=11;HP[i][0]=20;cenario->Dollar=cenario->Dollar-13;select_Arch(1,10);}

    }
    if(evento.key.keysym.sym == SDLK_2){while(Mi[i][0]!=0){i++;}
        if(i<5 && cenario->Dollar>=13)
        {
                Mix_Volume( 4, 30);
                Mix_PlayChannel( 4, entrada1, 0 );
                Mi[i][0]=12;HP[i][0]=20;cenario->Dollar=cenario->Dollar-13;select_Arch(1,12);}
        }
    if(evento.key.keysym.sym == SDLK_3){while(Mi[i][0]!=0){i++;}
        if(i<5 && cenario->Dollar>=13)
        {
                Mix_Volume( 4, 30);
                Mix_PlayChannel( 4, entrada1, 0 );
                Mi[i][0]=13;HP[i][0]=20;cenario->Dollar=cenario->Dollar-13;select_Arch(1,14);}
    }
    if(evento.key.keysym.sym == SDLK_4)
    {
                        j=0;
                            for(i=1;i<5;i++){
                                if(Mi[i][j]/100==1){
                                    Mi[i][j]=Mi[i][j]-200;
                        }}
    }
    if(evento.key.keysym.sym == SDLK_5)
    {
        j=5;
                        for(i=1;i<5;i++){
                                if(Mi[i][j]/100==1){
                                    Mi[i][j]=Mi[i][j]-200;
                        }}
    }
    }

    if( evento.type == SDL_MOUSEBUTTONDOWN )
    {
        if (eventos_botao(&comprar[0]) == 2)
        {
        while(Mi[i][0]!=0){i++;}
        if(i<5 && cenario->Dollar>=13)
        {
                Mix_Volume( 4, 30);
                Mix_PlayChannel( 4, entrada1, 0 );
                Mi[i][0]=11;HP[i][0]=20;cenario->Dollar=cenario->Dollar-13;select_Arch(1,10);}
        }
        else if (eventos_botao(&comprar[1]) == 2)
        {
        while(Mi[i][0]!=0){i++;}
        if(i<5 && cenario->Dollar>=13)
        {
                Mix_Volume( 4, 30);
                Mix_PlayChannel( 4, entrada1, 0 );
                Mi[i][0]=12;HP[i][0]=20;cenario->Dollar=cenario->Dollar-13;select_Arch(1,12);}
        }
        else if (eventos_botao(&comprar[2]) == 2)
        {
        while(Mi[i][0]!=0){i++;}
        if(i<5 && cenario->Dollar>=13)
        {
                Mix_Volume( 4, 30);
                Mix_PlayChannel( 4, entrada1, 0 );
                Mi[i][0]=13;HP[i][0]=20;cenario->Dollar=cenario->Dollar-13;select_Arch(1,14);}
        }
    }

    atualizar_dados(cenario,cenario_m);
}

void inst(){printf("\n\n\n\n\n MÁ SORTE");}

int ACuster(){
    int m,aux;
    char arch[7];

    FILE *f;

    sprintf(arch, "ORA.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;

    sprintf(arch, "OAA.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;

    sprintf(arch, "OMA.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;


    if(m>100){return 0;}
    else{return 1;}
}



int AWarbonds(){
    int n;
    char arch[7];

    FILE *f;

    sprintf(arch, "WMD.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &n);
        fclose(f);
    }
    if(n>1000){return 1;}
    else{return 0;}
}


int AMoscow(){
    int n;
    char arch[7];

    sprintf(arch, "VIA.txt");
    FILE *f;

    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &n);
        fclose(f);
    }
    if(n>0){return 1;}
    else{return 0;}

}

int AFail(){
    int n;
    char arch[7];

    sprintf(arch, "VIS.txt");
    FILE *f;

    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &n);
        fclose(f);
    }
    if(n>0){return 1;}
    else{return 0;}

}

int Akill1(){
    int m,aux;
    char arch[7];

    FILE *f;

    sprintf(arch, "ORS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;

    sprintf(arch, "OAS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;

    sprintf(arch, "OMS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;


    if(m>50){return 1;}
    else{return 0;}
}
int Akill2(){
    int m,aux;
    char arch[7];

    FILE *f;

    sprintf(arch, "ORS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;

    sprintf(arch, "OAS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;

    sprintf(arch, "OMS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;


    if(m>150){return 1;}
    else{return 0;}
}
int Akill3(){
    int m,aux;
    char arch[7];

    FILE *f;

    sprintf(arch, "ORS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;

    sprintf(arch, "OAS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;

    sprintf(arch, "OMS.txt");
    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &aux);
        fclose(f);
    }
    m=m+aux;


    if(m>450){return 1;}
    else{return 0;}
}

int AMoscow2(){
    int n;
    char arch[7];

    sprintf(arch, "VIA.txt");
    FILE *f;

    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &n);
        fclose(f);
    }
    if(n>7){return 1;}
    else{return 0;}

}
int AMoscow3(){
    int n;
    char arch[7];

    sprintf(arch, "VIA.txt");
    FILE *f;

    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &n);
        fclose(f);
    }
    if(n>15){return 1;}
    else{return 0;}

}
int AMoscow4(){
    int n;
    char arch[7];

    sprintf(arch, "VIA.txt");
    FILE *f;

    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &n);
        fclose(f);
    }
    if(n>50){return 1;}
    else{return 0;}

}

int AFail2(){
    int n;
    char arch[7];

    sprintf(arch, "VIS.txt");
    FILE *f;

    f = fopen(arch, "r");
    if (f == NULL) {
        return -1;
    } else {
        fscanf(f,"%d", &n);
        fclose(f);
    }
    if(n>6){return 1;}
    else{return 0;}

}

void hall(){
    int c=0;
    printf("\n\n\n\n\n Conquistas desbloqueadas:");
    if(ACuster()==1){aplicar_superficie( 180, 400, Custer, tela, NULL );printf("\n-General Custer");c++;}

    if(Akill1()==1){aplicar_superficie( 160, 290, Kill1, tela, NULL );printf("\n-Abaixo à horda!");c++;}

    if(Akill2()==1){printf("\n-Somente mais um dia de trabalho.");c++;}

    if(Akill3()==1){printf("\n-Não gosto de vermelho.");c++;}

    if(AWarbonds()==1){printf("\n-Economia de guerra");c++;}

    if(AMoscow()==1){aplicar_superficie( 170, 200, Moscow, tela, NULL );printf("\n-Para Moscow!");c++;}

    if(AFail()==1){printf("\n-Longe do esperado...");c++;}

    if(AMoscow2()==1){printf("\n-Adeus, Stálin!");c++;}

    if(AMoscow3()==1){printf("\n-Fim da cortina de ferro.");c++;}

    if(AMoscow4()==1){printf("\n-Quando sai a próxima DLC?");c++;}

    if(AFail2()==1){printf("\n-Ok, eu ainda estava aprendendo... Todas essas 7 vezes...");c++;}


    if(c>0 && c<11){printf("\n\nvocê desbloqueou %d conquistas no total, parabéns!",c);}
    else if(c<=0){printf("\n\nvocê desbloqueou nenhuma conquista...");}
    else if(c>=11){printf("\n\nvocê desbloqueou todas as conquistas! Agora vá arranjar uma vida!");}
}

/*int main(){
    int e;
    setlocale(LC_ALL, "Portuguese");
    do{
    printf("\n\n\n");
    printf("        ---OPERAÇÃO: DROPSHOT---");
    printf("\n\n\n");
    printf("1-Jogar");
    printf("\n2-Instruções");
    printf("\n3-Conquistas");
    printf("\n0-Sair\n");
    scanf("%d",&e);
    if(e==1){fase1();}
    else if(e==2){inst();}
    else if(e==3){hall();}
    }while(e!=0);
    return 0;
}*/

int main( int argc, char* args[] ) {
    int i, j, quit = 0, aux, x=0, y=0, k=0;
    int anterior = -1;
    Uint8 *estadoteclas = SDL_GetKeyState( NULL );

    if (iniciar() == -1)
    {
        limpar();
        return -1;
    }

    if (carregar_arquivos() == -1)
    {
        limpar();
        return -1;
    }

    movel menu;
    declarar_movel(&menu);
    menu.altura = SCREEN_HEIGHT;
    menu.largura = SCREEN_WIDTH;
    menu.sprite[0] = menu_imagem;
    menu.sprite[1] = menu_instrucoes;
    menu.sprite[2] = Conquistas;

    movel botao;
    declarar_movel(&botao);
    botao.altura = 36;
    botao.largura = 207;
    botao.x = 553;
    botao.y = 350;
    botao.sprite[0] = botao1;

    movel botao_2;
    declarar_movel(&botao_2);
    botao_2.altura = 42;
    botao_2.largura = 92;
    botao_2.x = 619;
    botao_2.y = 480;
    botao_2.sprite[0] = botao2;

    movel botao_3;
    declarar_movel(&botao_3);
    botao_3.altura = 38;
    botao_3.largura = 171;
    botao_3.x = 400;
    botao_3.y = 230;
    botao_3.sprite[0] = botao3;

    movel botao_4;
    declarar_movel(&botao_4);
    botao_4.altura = 38;
    botao_4.largura = 171;
    botao_4.x = 763;
    botao_4.y = 230;
    botao_4.sprite[0] = botao4;

    movel comprar[3];
    declarar_movel(&comprar[0]);
    declarar_movel(&comprar[1]);
    declarar_movel(&comprar[2]);
    comprar[0].largura = 200;
    comprar[0].altura = 100;
    comprar[0].x = 5;
    comprar[0].y = 500;
    comprar[1].largura = 200;
    comprar[1].altura = 100;
    comprar[1].x = 215;
    comprar[1].y = 500;
    comprar[2].largura = 200;
    comprar[2].altura = 100;
    comprar[2].x = 425;
    comprar[2].y = 500;

    movel americanos[3];
    declarar_movel(&americanos[0]);
    americanos[0].largura = 85;
    americanos[0].altura = 120;
    americanos[0].velx = SCREEN_WIDTH/40;
    americanos[0].icone = cursor_americano;
    americanos[0].sprite[0] = palito_anda1;
    americanos[0].sprite[1] = palito_anda2;
    americanos[0].sprite[2] = palito_anda3;
    americanos[0].sprite[3] = palito_anda4;
    americanos[0].sprite[4] = americano_atira3;
    americanos[0].sprite[5] = americano_atira4;
    declarar_movel(&americanos[1]);
    americanos[1].largura = 85;
    americanos[1].altura = 120;
    americanos[1].velx = SCREEN_WIDTH/40;
    americanos[1].icone = cursor_americano2;
    americanos[1].sprite[0] = AmericanoA;
    americanos[1].sprite[1] = AmericanoA_anda;
    americanos[1].sprite[2] = AmericanoA_atira1;
    americanos[1].sprite[3] = AmericanoA_atira2;
    americanos[1].sprite[4] = AmericanoA_atira3;
    americanos[1].sprite[5] = AmericanoA_atirafinal;
    declarar_movel(&americanos[2]);
    americanos[2].largura = 85;
    americanos[2].altura = 120;
    americanos[2].velx = SCREEN_WIDTH/40;
    americanos[2].icone = cursor_americano3;
    americanos[2].sprite[0] = AmericanoM;
    americanos[2].sprite[1] = AmericanoM_anda;
    americanos[2].sprite[2] = AmericanoM_atira1;
    americanos[2].sprite[3] = AmericanoM_atira2;
    americanos[2].sprite[4] = AmericanoM_atira3;
    americanos[2].sprite[5] = AmericanoM_atirafinal;

    movel sovieticos[3];
    declarar_movel(&sovieticos[0]);
    sovieticos[0].largura = 85;
    sovieticos[0].altura = 120;
    sovieticos[0].velx = -SCREEN_WIDTH/40;
    sovieticos[0].icone = cursor_sovietico;
    sovieticos[0].sprite[0] = sovietico;
    sovieticos[0].sprite[1] = sovietico_anda;
    sovieticos[0].sprite[2] = sovietico_atira;
    sovieticos[0].sprite[3] = SovieticoF_atira2;
    sovieticos[0].sprite[4] = SovieticoF_atira3;
    sovieticos[0].sprite[5] = SovieticoF_atirafinal;
    declarar_movel(&sovieticos[1]);
    sovieticos[1].largura = 85;
    sovieticos[1].altura = 120;
    sovieticos[1].velx = -SCREEN_WIDTH/40;
    sovieticos[1].icone = cursor_sovietico;
    sovieticos[1].sprite[0] = SovieticoA;
    sovieticos[1].sprite[1] = SovieticoA_anda;
    sovieticos[1].sprite[2] = SovieticoA_atira;
    sovieticos[1].sprite[3] = SovieticoA_atira2;
    sovieticos[1].sprite[4] = SovieticoA_atira3;
    sovieticos[1].sprite[5] = SovieticoA_atirafinal;
    declarar_movel(&sovieticos[2]);
    sovieticos[2].largura = 85;
    sovieticos[2].altura = 120;
    sovieticos[2].velx = -SCREEN_WIDTH/40;
    sovieticos[2].icone = cursor_sovietico;
    sovieticos[2].sprite[0] = SovieticoM;
    sovieticos[2].sprite[1] = SovieticoM_anda;
    sovieticos[2].sprite[2] = SovieticoM_atira;
    sovieticos[2].sprite[3] = SovieticoM_atira2;
    sovieticos[2].sprite[4] = SovieticoM_atira3;
    sovieticos[2].sprite[5] = SovieticoM_atirafinal;

    fase Fase1;
    map_fase Fase1_m[11];
    fase1_preparar(&Fase1);
    fase1_preparar2(Fase1_m);

    while (quit == 0)
    {
        //Verificando eventos
        while( SDL_PollEvent( &evento ) )
        {
            if (menu.status == 0)
            {
                comando_batalha(&Fase1, Fase1_m, &menu, comprar);
            }
            if( evento.type == SDL_QUIT )
            {
                quit = 1;
            }
            if( evento.type == SDL_MOUSEMOTION )
            {
                x = evento.motion.x;
                y = evento.motion.y;
                if (menu.status == 1)
                {
                    if (eventos_botao(&botao) == 1)
                    {
                        botao.sprite[0] = botao1_p;
                    }
                    else
                    {
                        botao.sprite[0] = botao1;
                    }
                    if (eventos_botao(&botao_2) == 1)
                    {
                        botao_2.sprite[0] = botao2_p;
                    }
                    else
                    {
                        botao_2.sprite[0] = botao2;
                    }
                    if (eventos_botao(&botao_3) == 1)
                    {
                        botao_3.sprite[0] = botao3_p;
                    }
                    else
                    {
                        botao_3.sprite[0] = botao3;
                    }
                    if (eventos_botao(&botao_4) == 1)
                    {
                        botao_4.sprite[0] = botao4_p;
                    }
                    else
                    {
                        botao_4.sprite[0] = botao4;
                    }
                }
            }
            if( evento.type == SDL_MOUSEBUTTONDOWN )
            {
                if( evento.button.button == SDL_BUTTON_LEFT )
                {
                    x = evento.button.x;
                    y = evento.button.y;
                    if (eventos_botao(&botao) == 2 && menu.status == 1)
                    {
                        menu.status = 0;
                        botao.sprite[0] = botao1;
                        if( Mix_PlayingMusic() == 1 )
                        {
                            Mix_HaltMusic();
                        }
                        Mix_VolumeMusic( 128 );
                        if( Mix_PlayMusic( musica, -1 ) == -1 )
                        {
                            return 1;
                        }
                    }
                    if (eventos_botao(&botao_3) == 2 && menu.status == 1)//tela conquista
                    {
                        menu.status = 2;
                    }
                    if (eventos_botao(&botao_4) == 2 && menu.status == 1)//tela conquista
                    {
                        menu.status = 3;
                    }
                    else if (eventos_botao(&botao_2) == 2 && menu.status == 1)
                    {
                        quit = 1;
                    }
                }
            }
            if( evento.type == SDL_KEYDOWN )
            {
               /* if (menu.status == 0)
                {
                    comando_batalha(&Fase1, Fase1_m, &menu);
                }*/
                if (menu.status == 1)
                {
                    if (evento.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = 1;
                    }
                }
                else if (menu.status == 0)
                {
                    if (evento.key.keysym.sym == SDLK_ESCAPE)
                    {
                        menu.status = 1;
                        Mix_HaltMusic();
                        fase1_preparar(&Fase1);
                        fase1_preparar2(Fase1_m);
                    }
                }
                else if (menu.status == 2 || menu.status == 3)
                {
                    if (evento.key.keysym.sym == SDLK_ESCAPE)
                    {
                        menu.status = 1;
                    }
                }
            }
        }
        //Aplicando imagens na tela
        SDL_FillRect( tela, &tela->clip_rect, SDL_MapRGB( tela->format, 0xFF, 0xFF, 0xFF ) );
        if (menu.status == 0)
        {
            fase1(&Fase1, Fase1_m, &menu);
            aplicar_superficie(0, 0, fundo, tela, NULL);
            aplicar_superficie(0, 0, mapa, tela, NULL);
            aplicar_soldados(&Fase1, Fase1_m, americanos, sovieticos);
            aplicar_interface(&Fase1);
        }
        else if (menu.status == 1)
        {
            if( Mix_PlayingMusic() == 0 )
            {
                Mix_VolumeMusic( 128 );
                if( Mix_PlayMusic( mus_menu, -1 ) == -1 )
                {
                    return 1;
                }
            }
            aplicar_superficie( 0, 0, menu.sprite[0], tela, NULL );
            aplicar_superficie( botao.x, botao.y, botao.sprite[0], tela, NULL );
            aplicar_superficie( botao_2.x, botao_2.y, botao_2.sprite[0], tela, NULL );
            aplicar_superficie( botao_3.x, botao_3.y, botao_3.sprite[0], tela, NULL );
            aplicar_superficie( botao_4.x, botao_4.y, botao_4.sprite[0], tela, NULL );
        }
        else if (menu.status == 2)
        {
            aplicar_superficie( 0, 0, menu.sprite[1], tela, NULL );
            //tela conquistas
        }
        else if (menu.status == 3)
        {
            aplicar_superficie( 0, 0, menu.sprite[2], tela, NULL );
            hall();
            //tela instruções
        }
        if( SDL_Flip( tela ) == -1 )
        {
            limpar();
            return -1;
        }
    }
    limpar();

    return 0;
}

/*
Plano 1: Colocar os soldados para avançar pelo mouse
a) reconhecer o clique com todos os soldados, linha por linha e separar entre cliques na base e cliques no checkpoint
b) depois de verificar aonde foi o clique verificar se houve mais de um status 2, que indica que o botão foi apertado
c) se houve mais de um status 2 cancelar o que está na linha de menor numero e avançar o que está mais à frente
d) perguntar ao Lag como fazer para avançar apenas um soldado na matriz e implementar para cada situação

Plano 2: Regular os RIPs
a) Separar entre soldados americanos e soviéticos
b) Acertar o local em que os RIPs aparecem para cada caso

Plano 3: Reconhecer avanço por tipo de unidade
a) Fazer o status de avançar ser diferenciado por tipo unidade
b) Fazer a animação reconhecer apenas o status daquela unidade que avançou e não de todas
*/
