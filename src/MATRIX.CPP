/*
CMatrix class
for Starcan

(c)Alex Dainiak
*/

#include "d:\bc\src\starcan\matrix.h"

CMatrix::CMatrix( void )
{
  pMatrix = NULL;
}

void CMatrix::Create( int rows, int cols )
{
  Destroy();

  SCols = cols;
  SRows = rows;
  STotal = rows * cols;

  pMatrix = new char[ STotal ];
}

void CMatrix::Destroy( void )
{
  if( pMatrix != NULL )
    delete pMatrix;
}

char CMatrix::GetElement( int row, int col )
{
  return pMatrix[ row * SCols + col ];
}

void CMatrix::SetElement( int row, int col, char value )
{
  pMatrix[ row * SCols + col ] = value;
}

CMatrix::~CMatrix( void )
{
  Destroy();
}

void CMatrix::Save( FILE* file )
{
  fwrite( pMatrix, sizeof( char ), STotal, file );
}

void CMatrix::Load( FILE* file )
{
  fread( pMatrix, sizeof( char ), STotal, file );
}

void CMatrix::MirrorHor( void )
{
  char ch;

  for( int j, i = 0; i < SRows; i++ )
    for( j = 0; j < SCols; j++ )
    {
      ch = pMatrix[ i * SCols + j ];
      pMatrix[ i * SCols + j ] = pMatrix[ ( i + 1 ) * SCols - j - 1 ];
      pMatrix[ ( i + 1 ) * SCols - j - 1 ] = ch;
    }
}

void CMatrix::MirrorVert( void )
{
  char ch;

  for( int j, i = 0; i < SRows; i++ )
    for( j = 0; j < SCols; j++ )
    {
      ch = pMatrix[ i * SCols + j ];
      pMatrix[ i * SCols + j ] = pMatrix[ ( SRows - i - 1 ) * SCols + j ];
      pMatrix[ ( SRows - i - 1 ) * SCols + j ] = ch;
    }
}
int CMatrix::CalcElements( void )
{
  int s, i;
  s = 0;
  for( i = 0; i < STotal; i++ )
    if( pMatrix[i] )
      s++;
  return s;
}