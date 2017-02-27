class CMatrix
{
private:
  char* pMatrix;
  int SCols;
  int SRows;
  int STotal;

public:
  void Create( int, int );
  void Destroy( void );
  char GetElement( int, int );
  void SetElement( int, int, char );
  void Save( FILE* );
  void Load( FILE* );
  void MirrorHor( void );
  void MirrorVert( void );
  int CalcElements( void );

  CMatrix( void );
  ~CMatrix( void );
};
