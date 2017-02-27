/*
CLevel class
for Starcan

(c)Alex Dainiak
*/

class CLevel
{
private:
  CMatrix LevMatrix;

public:
  void DrawBlocks( void );
  void UpdateBlock( int, int );
};

void CLevel::UpdateBlock( int row, int col )
{

}

void CLevel::DrawBlocks( void )
{
  for( int j, i = 0; i < LevMatrix.SRows; i++ )
    for( j = 0; j < LevMatrix.SCols; j++ )
      UpdateBlock( i, j );
}