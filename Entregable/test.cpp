/* Grupo formado por: Angie Ramírez y Walter Zárate
 *
 * Compilación: g++ -o ejecutable test.cpp
 * Ejecución: ./ejecutable
 */

#include "moving_image.h"
#include <windows.h> // Para utilizar sleep(). Usar unistd.h para Linux y windows.h para Windows

int main() {
  moving_image im;

  /* 
  im.move_right(00);
  im.move_left(00);
  im.move_up(00);
  im.move_down(00);
  im.rotate();

  im.undo();
  im.redo();
  im.repeat();
  */

  im.repeat_all();

  /* NOTA 1: Si usan el mismo nombre para las imágenes, entonces cada llamada al
  método draw() sobreescribirá a la imagen */

  /* NOTA 2: Si usan un ciclo while(1) y usan el mismo nombre de imagen,
  entonces se puede generar un efecto de desplazamiento continuo (algo así como
  un video =D ) */
  return 0;
}