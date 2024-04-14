#ifndef MOVING_IMG_H
#define MOVING_IMG_H
#include <iostream>
#include "basics.h"
#include <stack>
#include <utility>

using namespace std;

// Clase que representa una imagen como una colección de 3 matrices siguiendo el
// esquema de colores RGB

class moving_image {
private:
  unsigned char **red_layer; // Capa de tonalidades rojas, es un doble puntero pues es una matriz de nxm
  unsigned char **green_layer; // Capa de tonalidades verdes
  unsigned char **blue_layer; // Capa de tonalidades azules

  stack<pair<string,int>> historial;

public:
  // Constructor de la imagen. Se crea una imagen por defecto. Estamos creando la matriz de 1000x1000
  moving_image() {
    // Reserva de memoria para las 3 matrices RGB
    red_layer = new unsigned char*[H_IMG];
    green_layer = new unsigned char*[H_IMG];
    blue_layer = new unsigned char*[H_IMG];
    
    for(int i=0; i < H_IMG; i++) {
      red_layer[i] = new unsigned char[W_IMG];
      green_layer[i] = new unsigned char[W_IMG];
      blue_layer[i] = new unsigned char[W_IMG];
    }

    // Llenamos la imagen con su color de fondo
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++) {
      	red_layer[i][j] = DEFAULT_R;
      	green_layer[i][j] = DEFAULT_G;
      	blue_layer[i][j] = DEFAULT_B;
      }

    // Dibujamos el objeto en su posición inicial
    for(int i=0; i < 322; i++)
      for(int j=0; j < 256; j++) {
      	if(!s_R[i][j] && !s_G[i][j] && !s_B[i][j]) {
      	  red_layer[INIT_Y+i][INIT_X+j] = DEFAULT_R;
      	  green_layer[INIT_Y+i][INIT_X+j] = DEFAULT_G;
      	  blue_layer[INIT_Y+i][INIT_X+j] = DEFAULT_B;
      	} else {
      	  red_layer[INIT_Y+i][INIT_X+j] = s_R[i][j];
      	  green_layer[INIT_Y+i][INIT_X+j] = s_G[i][j];
      	  blue_layer[INIT_Y+i][INIT_X+j] = s_B[i][j];
      	}
      }   
  }

  // Destructor de la clase
  ~moving_image() {
    for(int i=0; i < H_IMG; i++) {
      delete red_layer[i];
      delete green_layer[i];
      delete blue_layer[i];
    }

    delete red_layer;
    delete green_layer;
    delete blue_layer;
  }

  // Función utilizada para guardar la imagen en formato .png
  void draw(const char* nb) {
    _draw(nb);
  }

  //FUNCIÓN IMPLEMENTADA: MOVE_RIGHT(D)
  void move_right(int d){
    unsigned char tmp_layer[H_IMG][W_IMG];

    // Mover la capa roja
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
       tmp_layer[i][j+d] = red_layer[i][j];      

    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=0; i < H_IMG; i++)
      for(int j=0, k=W_IMG-d; k < W_IMG; j++, k++)
        tmp_layer[i][j] = red_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
        red_layer[i][j] = tmp_layer[i][j];

      // Mover la capa verde
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
       tmp_layer[i][j+d] = green_layer[i][j];       
    
    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=0; i < H_IMG; i++)
      for(int j=0, k=W_IMG-d; k < W_IMG; j++, k++)
        tmp_layer[i][j] = green_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
        green_layer[i][j] = tmp_layer[i][j];

      // Mover la capa azul
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
       tmp_layer[i][j+d] = blue_layer[i][j];      
    
    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=0; i < H_IMG; i++)
      for(int j=0, k=W_IMG-d; k < W_IMG; j++, k++)
        tmp_layer[i][j] = blue_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
        blue_layer[i][j] = tmp_layer[i][j];

    historial.push(make_pair("move_right",d));
  }

  // Función que similar desplazar la imagen, de manera circular, d pixeles a la izquierda
  void move_left(int d) {
    unsigned char tmp_layer[H_IMG][W_IMG];

    // Mover la capa roja
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
	     tmp_layer[i][j] = red_layer[i][j+d];      
    
    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	 tmp_layer[i][j] = red_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	     red_layer[i][j] = tmp_layer[i][j];

    // Mover la capa verde
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
	       tmp_layer[i][j] = green_layer[i][j+d];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	tmp_layer[i][j] = green_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	       green_layer[i][j] = tmp_layer[i][j];

    // Mover la capa azul
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
	     tmp_layer[i][j] = blue_layer[i][j+d];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	 tmp_layer[i][j] = blue_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	       blue_layer[i][j] = tmp_layer[i][j];

    historial.push(make_pair("move_left",d));
  }

  //FUNCIÓN IMPLEMENTADA: MOVE_UP(D)
  void move_up(int d){
    unsigned char tmp_layer[H_IMG][W_IMG];

    //Movamos la capa roja
    for(int i=0; i < H_IMG-d; i++)
      for(int j=0; j < W_IMG; j++)
       tmp_layer[i][j] = red_layer[i+d][j]; 

    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=H_IMG-d, k=0; i < H_IMG; i++, k++)
      for(int j=0; j < W_IMG; j++)
        tmp_layer[i][j] = red_layer[k][j]; 

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
       red_layer[i][j] = tmp_layer[i][j];

     //Movamos la capa verde
    for(int i=0; i < H_IMG-d; i++)
      for(int j=0; j < W_IMG; j++)
       tmp_layer[i][j] = green_layer[i+d][j]; 

    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=H_IMG-d, k=0; i < H_IMG; i++, k++)
      for(int j=0; j < W_IMG; j++)
        tmp_layer[i][j] = green_layer[k][j]; 

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
       green_layer[i][j] = tmp_layer[i][j];

     //Movamos la capa azul
    for(int i=0; i < H_IMG-d; i++)
      for(int j=0; j < W_IMG; j++)
       tmp_layer[i][j] = blue_layer[i+d][j]; 

    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=H_IMG-d, k=0; i < H_IMG; i++, k++)
      for(int j=0; j < W_IMG; j++)
        tmp_layer[i][j] = blue_layer[k][j]; 

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
       blue_layer[i][j] = tmp_layer[i][j];

    historial.push(make_pair("move_up",d));
  }

  //FUNCIÓN IMPLEMENTADA: MOVE_DOWN(D)
  void move_down(int d){
    unsigned char tmp_layer[H_IMG][W_IMG];

    //Movamos la capa roja
    for(int i=0; i < H_IMG-d; i++)
      for(int j=0; j < W_IMG; j++)
       tmp_layer[i+d][j] = red_layer[i][j]; 

    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=0, k=H_IMG-d; k < H_IMG; i++, k++)
      for(int j=0; j < W_IMG; j++)
        tmp_layer[i][j] = red_layer[k][j]; 

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
       red_layer[i][j] = tmp_layer[i][j];

     //Movamos la capa verde
    for(int i=0; i < H_IMG-d; i++)
      for(int j=0; j < W_IMG; j++)
       tmp_layer[i+d][j] = green_layer[i][j]; 

    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=0, k=H_IMG-d; k < H_IMG; i++, k++)
      for(int j=0; j < W_IMG; j++)
        tmp_layer[i][j] = green_layer[k][j]; 

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
       green_layer[i][j] = tmp_layer[i][j];

     //Movamos la capa azul
    for(int i=0; i < H_IMG-d; i++)
      for(int j=0; j < W_IMG; j++)
       tmp_layer[i+d][j] = blue_layer[i][j];  

    //Cuando pasa el límite de la imagen, es direccionado al otro lado de la imagen
    for(int i=0, k=H_IMG-d; k < H_IMG; i++, k++)
      for(int j=0; j < W_IMG; j++)
        tmp_layer[i][j] = blue_layer[k][j]; 

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
       blue_layer[i][j] = tmp_layer[i][j];

    historial.push(make_pair("move_down",d));
  }

  void rotate(){
    unsigned char tmp_layer[H_IMG][W_IMG];
    //Rotar capa roja
    for(int i=0, aux_j=0; i<H_IMG ; i++, aux_j++){
      for(int j=W_IMG-1, aux_i=0; j>=0; j--, aux_i++){
        tmp_layer[aux_i][aux_j]=red_layer[i][j];
      }
    }

    for(int i=0; i < H_IMG; i++){
      for(int j=0; j < W_IMG; j++){
        red_layer[i][j] = tmp_layer[i][j];
      }
    }

    //Rotar capa verde
    for(int i=0, aux_j=0; i<H_IMG ; i++, aux_j++){
      for(int j=W_IMG-1, aux_i=0; j>=0; j--, aux_i++){
        tmp_layer[aux_i][aux_j]=green_layer[i][j];
      }
    }

    for(int i=0; i < H_IMG; i++){
      for(int j=0; j < W_IMG; j++){
        green_layer[i][j] = tmp_layer[i][j];
      }
    }

    //Rotar capa azul
    for(int i=0, aux_j=0; i<H_IMG ; i++, aux_j++){
      for(int j=W_IMG-1, aux_i=0; j>=0; j--, aux_i++){
        tmp_layer[aux_i][aux_j]=blue_layer[i][j];
      }
    }

    for(int i=0; i < H_IMG; i++){
      for(int j=0; j < W_IMG; j++){
        blue_layer[i][j] = tmp_layer[i][j];
      }
    }

    historial.push(make_pair("rotate",0));
  }

  void derotate(){
    unsigned char tmp_layer[H_IMG][W_IMG];
    //Rotar capa roja
    for(int i=H_IMG-1, aux_j=0; i>=0 ; i--, aux_j++){
      for(int j=0, aux_i= 0; j<W_IMG; j++, aux_i++){
        tmp_layer[aux_i][aux_j]=red_layer[i][j];
      }
    }

    for(int i=0; i < H_IMG; i++){
      for(int j=0; j < W_IMG; j++){
        red_layer[i][j] = tmp_layer[i][j];
      }
    }

      for(int i=H_IMG-1, aux_j=0; i>=0 ; i--, aux_j++){
      for(int j=0, aux_i= 0; j<W_IMG; j++, aux_i++){
        tmp_layer[aux_i][aux_j]=green_layer[i][j];
      }
    }

    for(int i=0; i < H_IMG; i++){
      for(int j=0; j < W_IMG; j++){
        green_layer[i][j] = tmp_layer[i][j];
      }
    }

      for(int i=H_IMG-1, aux_j=0; i>=0 ; i--, aux_j++){
      for(int j=0, aux_i= 0; j<W_IMG; j++, aux_i++){
        tmp_layer[aux_i][aux_j]=blue_layer[i][j];
      }
    }

    for(int i=0; i < H_IMG; i++){
      for(int j=0; j < W_IMG; j++){
        blue_layer[i][j] = tmp_layer[i][j];
      }
    }

    historial.push(make_pair("derotate",0));
  }  

  void undo(){
    if(historial.top().first.compare("move_right") == 0){
      move_left(historial.top().second);
    }
    else if(historial.top().first.compare("move_left") == 0){
      move_right(historial.top().second);
    }
    else if(historial.top().first.compare("move_up") == 0){
      move_down(historial.top().second);
    }
    else if(historial.top().first.compare("move_down") == 0){
      move_up(historial.top().second);
    }
    else if(historial.top().first.compare("rotate") == 0){
      derotate();
    }
    else if(historial.top().first.compare("derotate") == 0){
      rotate();
    }
    else{
      cout << "Hubo un problema con la comprobación de nombres" << endl;
    }
  }


private:
  // Función privada que guarda la imagen en formato .png
  void _draw(const char* nb) {
    unsigned char *rgb = new unsigned char[H_IMG * W_IMG * 3], *p = rgb;
    unsigned x, y;

    // La imagen resultante tendrá el nombre dado por la variable 'nb'
    FILE *fp = fopen(nb, "wb");

    // Transformamos las 3 matrices en una arreglo unidimensional
    for (y = 0; y < H_IMG; y++)
        for (x = 0; x < W_IMG; x++) {
            *p++ = red_layer[y][x];    /* R */
            *p++ = green_layer[y][x];    /* G */
            *p++ = blue_layer[y][x];    /* B */
        }
    // La función svpng() transforma las 3 matrices RGB en una imagen PNG 
    svpng(fp, W_IMG, H_IMG, rgb, 0);
    fclose(fp);
}

  
};

#endif
