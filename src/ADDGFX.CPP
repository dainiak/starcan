/*
Additional graphics effects
for Starcan

(c)Alex Dainiak
*/

void drawblock( int x1, int y1, int x2, int y2 )
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

void removeblock( int x1, int y1, int x2, int y2, int fill )
{
  setfillstyle( SOLID_FILL, 0 );
  bar( x1, y1, x2, y2 );

  for( int i = 0; i < fill; i++ )
    drawstar( x1 + 1 + random( x2 - x1 - 1 ),
                                y1 + 1 + random( y2 - y1 - 1 ), 0 );
}

void drawboard( int x, int y, int length, int frame )
{
  switch( frame )
  {
    case 0: setcolor( 11 ); break;
    case 1: setcolor( 3 ); break;
    case 2: setcolor( 9 ); break;
  }

  line( x, y + 2, x + length, y + 2 );

  switch( frame )
  {
    case 0: setcolor( 3 ); break;
    case 1: setcolor( 9 ); break;
    case 2: setcolor( 11 ); break;
  }

  line( x, y + 1, x + length, y + 1 );
  line( x, y + 3, x + length, y + 3 );

  switch( frame )
  {
    case 0: setcolor( 9 ); break;
    case 1: setcolor( 11 ); break;
    case 2: setcolor( 3 ); break;
  }

  line( x, y, x + length, y );
  line( x, y + 4, x + length, y + 4 );
  setfillstyle( SOLID_FILL, 0 );

  if( x > 5 )
    bar( 4, y, x - 1, y + 4 );

  if( x + length < 635 )
    bar( x + length + 1, y, 635, y + 4 );
}

void drawball( int x, int y, int rad, int fill )
{
  int dx, dy;
  int k;

  for( int i = 0; i < fill; i++ )
  {
    dx = random( 2 * rad + 1 );
    dx -= rad;
    k = sqrt( rad * rad - dx * dx );
    dy = random( 2 * k + 1 );
    dy -= k;
    drawstar( x + dx, y + dy, 0 );
  }
}

void addbrevent( int row, int col )
{
  CGRemoveBlock* NEvent;
  NEvent = new CGRemoveBlock;
  NEvent->x = 5 + 16 * col;
  NEvent->y = 5 + 8 * row;
  MainGQ.AddEvent( (CGEvent*) ((void*) NEvent) );
  LevelMatrix.SetElement( row, col, 0 );
  isscorechanged = 1;
  curscore++;
}

int ceili( double d )
{
  if( d == int( d ) )
    return int( d );
  else
    return int( d ) + d;
}

int floori( double d )
{
  return int( d );
}

double dabs( double d )
{
  return ( d < 0  ? -d : d );
}

int getblock( int x, int y )
{
  int k;

  if( ( y - 4 ) / 8 > 35 || ( x - 4 ) / 16 > 38 )
    return 0;

  k = LevelMatrix.GetElement( ( y - 4 ) / 8, ( x - 4 ) / 16 );

  if( k )
    addbrevent( ( y - 4 ) / 8, ( x - 4 ) / 16 );

  return k;
}

void moveball( void )
{
  pr_ball_x = ball_x;
  pr_ball_y = ball_y;
  ball_x += ball_a;
  ball_y += ball_b;

  if( ball_y > 436 )
  {
    if( ball_x > mouse_x - 4 && ball_x < mouse_x + board_length + 4 )
    {
      ball_a = 2 * ( ball_x - mouse_x - board_length / 2 ) / board_length;
      ball_b = -ball_vel * sqrt( 1 - ball_b * ball_b );
      ball_a *= ball_vel;
    }
    else
    {
      ballsleft--;
      isballlost = 1;
    }
  }

  if( ball_y < 9 )
  {
    ball_b = dabs( ball_b );
    ball_y++;
  }

  if( ball_x < 9 )
  {
    ball_a = dabs( ball_a );
    ball_x++;
  }

  if( ball_x > 631 )
  {
    ball_a = -dabs( ball_a );
    ball_x--;
  }

  if( getblock( ball_x - 4, ball_y ) )
  {
    ball_a = dabs( ball_a );
    ball_x += 1;
  }

  if( getblock( ball_x + 4, ball_y ) )
  {
    ball_a = - dabs( ball_a );
    ball_x -= 1;
  }

  if( getblock( ball_x, ball_y - 4 ) )
  {
    ball_b = dabs( ball_b );
    ball_y += 1;
  }

  if( getblock( ball_x, ball_y + 4 ) )
  {
    ball_b = - dabs( ball_b );
    ball_y -= 1;
  }

  setcolor( 0 );
  putpixel( pr_ball_x, pr_ball_y, 0 );
  circle( pr_ball_x, pr_ball_y, 1 );
  circle( pr_ball_x, pr_ball_y, 2 );
  circle( pr_ball_x, pr_ball_y, 3 );
  circle( pr_ball_x, pr_ball_y, 4 );
  drawball( ball_x, ball_y, 3, 1 );
}