/*
Starcan main .cpp

(c)Alex Dainiak
*/

#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "d:\bc\src\starcan\logo.cpp"
#include "d:\bc\src\starcan\matrix.cpp"
#include "d:\bc\src\starcan\intrface.cpp"
#include "d:\bc\src\starcan\cgqueue.cpp"
#include "d:\bc\src\starcan\glbvar.cpp"
#include "d:\bc\src\starcan\mouse.cpp"
#include "d:\bc\src\starcan\addgfx.cpp"

int loadlevel( int lev )
{
  FILE* fl;
  char path[80];
  itoa( lev, path, 10 );
  strcat( path, ".sld" );
  fl = fopen( path, "r");

  if( fl )
  {
    LevelMatrix.Load( fl );
    fclose( fl );
  }
  else
    return 0;

  return 1;
}

void drawinterface( int levelnumber )
{
  clearviewport();
  window( 0, 0, 639, 479 );
  divider( 4, 455, 0, 631 );
  arcansymb( 8, 460, 'S' );
  arcansymb( 27, 460, ':' );
  arcannum( 34, 460, curscore, 5 );
  arcansymb( 108, 460, 'B' );
  arcansymb( 127, 460, ':' );
  arcannum( 134, 460, ballsleft, 5 );
  arcansymb( 208, 460, 'L' );
  arcansymb( 227, 460, ':' );
  arcannum( 234, 460, levelnumber, 5 );

  for( int i = 0; i < 36; i++ )
    for( int j = 0; j < 39; j++ )
      if( LevelMatrix.GetElement( i, j ) )
        drawblock( 5 + j * 16, 5 + i * 8, j * 16 + 20, i * 8 + 12 );
}

void updatescreen( int levelnumber )
{
  if( isscorechanged )
  {
    isscorechanged = 0;
    setfillstyle( SOLID_FILL, 0 );
    bar( 32, 458, 100, 475 );
    arcannum( 34, 460, curscore, 5 );
  }

  if( isballlost )
  {
    board_length = 80;
    pr_ball_x = 15;
    pr_ball_y = 430;
    ball_x = 15;
    ball_y = 430;
    ball_a = -0.1;
    ball_b = -0.1;

    if( ballsleft >= 0 )
    {
      isballlost = 0;
      startlogo( 2 );
      drawinterface( levelnumber );
    }
  }
}

int playlevel( int levelnumber )
{
  if( !loadlevel( levelnumber ) )
    return 0;

  double frame = 0;
  int pscore;

  pscore = curscore + LevelMatrix.CalcElements();
  MainGQ.ClearQueue();
  drawinterface( levelnumber );
  board_length = 80;
  pr_ball_x = 15;
  pr_ball_y = 430;
  ball_x = 15;
  ball_y = 430;
  ball_a = -0.1;
  ball_b = -0.1;
  isballlost = 0;

  while( !mouse_mb )
  {
    GetMouseStatus();
    drawboard( mouse_x, 440, board_length, int( frame ) );
    frame+=0.015;

    if( frame > 3 )
      frame = 0.015;

    moveball();
    MainGQ.RunQueue();
    updatescreen( levelnumber );

    if( curscore == pscore )
      return 1;

    if( isballlost )
      return 0;
  }

  return 0;
}

void main( void )
{
  int gd, gm;
  int i, j;

  gd = VGA;
  gm = VGAHI;
  registerbgidriver( EGAVGA_driver );
  initgraph( &gd, &gm, "" );
  startlogo( -1 );
  LevelMatrix.Create( 36, 39 );
  InitMouse();
  SetMouseLimits( 5, 0, 555, 0 );
  SetMouseCordinates( 90, 0 );
  ballsleft = 3;
  curscore = 0;
  ball_vel = 0.1;

  for( i = 1;; i++ )
    if( !playlevel( i ) )
    {
      closegraph();
      if( i == 1 )
        printf( "Error: no level files in arcan's dir!" );
      else
        printf( "Thnx 4 playing!" );
      return;
    }
}