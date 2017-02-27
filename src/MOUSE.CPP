/*
Mouse routines
*/
#include "mouse.h"

void SetMouseCordinates( int X, int Y )
{
  asm mov ax, 4
  asm int 33h
  asm mov cx, [X]
  asm mov dx, [Y]
}
int InitMouse( void )
{
  int stat;
  asm mov ax,0
  asm int 33h
  asm mov [stat], ax

  if( stat == 0000 )
    return(0);

  SetMouseCordinates( 0 , 0 );
  return(1);
}
void ShowMouseCursor( void )
{
  asm mov ax , 01
  asm int 33h
}
void HideMouseCursor( void )
{
  asm mov ax , 02
  asm int 33h
}
void GetMouseStatus( void )
{
  int buttons_state;

  mouse_lb = 0;
  mouse_mb = 0;
  mouse_rb = 0;

  asm mov ax, 03
  asm int 33h
  asm mov [mouse_x], cx
  asm mov [mouse_y], dx
  asm mov [buttons_state], bx

  if( buttons_state == 1 )
    mouse_lb = 1;

  if( buttons_state == 2 )
    mouse_rb = 1;

  if( buttons_state == 3 )
  {
    mouse_lb = 1;
    mouse_rb = 1;
  }

  if( buttons_state == 4 )
    mouse_mb = 1;
}

void SetMouseLimits( int min_x, int min_y, int max_x, int max_y )
{
  asm mov ax, 7
  asm mov cx, [min_x]
  asm mov dx, [max_x]
  asm int 33h
  asm mov ax, 8
  asm mov cx, [min_y]
  asm mov dx, [max_y]
  asm int 33h
}