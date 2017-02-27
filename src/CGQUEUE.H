class CGEvent
{
public:
  int type;
  virtual void CallGFunction( void ) = 0;
  virtual int IsFinished( void ) = 0;
};

class CGRemoveBlock:CGEvent
{
public:
  void CallGFunction( void );
  int IsFinished( void );
  int frame;
  int x;
  int y;
  CGRemoveBlock( void );
};

struct QElement
{
  QElement* NextElement;
  QElement* PrevElement;
  CGEvent* Data;
};

class CEvQueue
{
private:
  QElement* FirstElement;
  void RemoveEvent( QElement* );
public:
  void RunQueue( void );
  void AddEvent( CGEvent* );
  void ClearQueue( void );
  CEvQueue( void );
  ~CEvQueue( void );
};