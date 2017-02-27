/*
Primitive level editor
for Starcan
(Designed for internal use)

(c)Alex Dainiak
*/
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
int mouse_x, mouse_y;
int mouse_lb, mouse_rb, mouse_mb;

#include "d:\bc\src\starcan\mouse.cpp"
#include "d:\bc\src\starcan\matrix.cpp"

FILE* fl;
CMatrix LevelMatrix;

void drawblock( int x1, int y1, int x2, int y2/*, int type*/ )
{
  setcolor( 1 );
  rectangle( x1, y1, x2, y2 );
  setcolor( 9 );
  rectangle( x1 + 1, y1 + 1, x2 - 1, y2 - 1 );
  setcolor( 11 );
  rectangle( x1 + 2, y1 + 2, x2 - 2, y2 - 2 );
  setfillstyle( SOLID_FILL, 3 );
  bar( x1 + 3, y1 + 3, x2 - 3, y2 - 3 );
}
void window( int x1, int y1, int x2, int y2 )
{
 setcolor( 11 );
 rectangle( x1, y1, x2, y2 );
 setcolor( 3 );
 rectangle( x1 + 1, y1 + 1, x2 - 1, y2 - 1 );
 setcolor( 9 );
 rectangle( x1 + 2, y1 + 2, x2 - 2, y2 - 2 );
 setcolor( 1 );
 rectangle( x1 + 3, y1 + 3, x2 - 3, y2 - 3 );
}
void loadfile( void )
{
  char path[80];
  clrscr();
  gets( path );
  if( !( fl = fopen( path, "r" )))
    LevelMatrix.Load( fl );
}
void savefile( void )
{
  if( fl == NULL )
  {
    char path[80];
    clrscr();
    gets( path );
    fl = fopen( path, "w" );
  }
  LevelMatrix.Save( fl );
  fclose( fl );
}
void main( void )
{
  int gd, gm;
  int p;
  fl = NULL;
  gd = VGA;
  gm = VGAHI;
  loadfile();
  registerbgidriver( EGAVGA_driver );
  initgraph( &gd, &gm, "" );
  clearviewport();
  setcolor( 7 );
  for( int i = 0; i < 36; i++ )
    for( int j = 0; j < 39; j++ )
      rectangle( 16 * j + 5, 8 * i + 5, 16 * j + 20, 8 * i + 12 );
  LevelMatrix.Create( 36, 39 );
  for( i = 0; i < 36; i++ )
    for( int j = 0; j < 39; j++ )
      LevelMatrix.SetElement( i, j, 0 );
  window( 0, 0, 639, 479 );
  InitMouse();
  SetMouseLimits( 5, 5, 623, 287 );
  SetMouseCordinates( 90, 90 );
  ShowMouseCursor();

  while( !kbhit() || getch() != 27 )
  {
    GetMouseStatus();

    if( mouse_rb && LevelMatrix.GetElement( ( mouse_y - 5 ) / 8, ( mouse_x - 5 ) / 16 ) )
    {
      HideMouseCursor();
      setfillstyle( SOLID_FILL, 0 );
      bar( ( ( mouse_x - 5 ) / 16 ) * 16 + 5, ( ( mouse_y - 5 ) / 8 ) * 8 + 5,
         ( ( mouse_x - 5 ) / 16 ) * 16 + 20, ( ( mouse_y - 5 ) / 8 ) * 8 + 12 );
      setcolor( 7 );
      rectangle( ( ( mouse_x - 5 ) / 16 ) * 16 + 5, ( ( mouse_y - 5 ) / 8 ) * 8 + 5,
         ( ( mouse_x - 5 ) / 16 ) * 16 + 20, ( ( mouse_y - 5 ) / 8 ) * 8 + 12 );
      LevelMatrix.SetElement( ( mouse_y - 5 ) / 8, ( mouse_x - 5 ) / 16, 0 );
      ShowMouseCursor();
    }

    if( mouse_lb && !LevelMatrix.GetElement( ( mouse_y - 5 ) / 8, ( mouse_x - 5 ) / 16 ) )
    {
      HideMouseCursor();
      setfillstyle( SOLID_FILL, 0 );
      bar( ( ( mouse_x - 5 ) / 16 ) * 16 + 5, ( ( mouse_y - 5 ) / 8 ) * 8 + 5,
         ( ( mouse_x - 5 ) / 16 ) * 16 + 20, ( ( mouse_y - 5 ) / 8 ) * 8 + 12 );
      drawblock( ( ( mouse_x - 5 ) / 16 ) * 16 + 5, ( ( mouse_y - 5 ) / 8 ) * 8 + 5,
         ( ( mouse_x - 5 ) / 16 ) * 16 + 20, ( ( mouse_y - 5 ) / 8 ) * 8 + 12 );
      LevelMatrix.SetElement( ( mouse_y - 5 ) / 8, ( mouse_x - 5 ) / 16, 1 );
      ShowMouseCursor();
    }
  }

  closegraph();
  savefile();
}