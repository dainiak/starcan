/*
Graphics queue class
for Starcan

(c)Alex Dainiak
*/

void removeblock( int, int, int, int, int );

#include "d:\bc\src\starcan\cgqueue.h"

CGRemoveBlock::CGRemoveBlock( void )
{
  frame = 500;
}
void CGRemoveBlock::CallGFunction( void )
{
  frame--;

  if( !( frame % 50 ) )
    removeblock( x, y, x + 15, y + 7, frame / 20 );
}
int CGRemoveBlock::IsFinished( void )
{
  return ( !frame );
}

CEvQueue::CEvQueue( void )
{
  FirstElement = NULL;
}
CEvQueue::~CEvQueue( void )
{
  while( FirstElement )
    RemoveEvent( FirstElement );
}
void CEvQueue::ClearQueue( void )
{
  while( FirstElement )
    RemoveEvent( FirstElement );
}

void CEvQueue::AddEvent( CGEvent* NewEvent )
{
  QElement* NewEl;
  NewEl = new QElement;
  NewEl->Data = NewEvent;
  NewEl->NextElement = FirstElement;

  if( FirstElement )
    FirstElement->PrevElement = NewEl;

  NewEl->PrevElement = NULL;
  FirstElement = NewEl;
}
void CEvQueue::RemoveEvent( QElement* El )
{
  if( El->NextElement )
    El->NextElement->PrevElement = El->PrevElement;

  if( El->PrevElement )
    El->PrevElement->NextElement = El->NextElement;
  else
    FirstElement = El->NextElement;

  delete ( El->Data );
  delete El;
}

void CEvQueue::RunQueue( void )
{
  QElement* CurrentElement;
  QElement* TempElement;
  CurrentElement = FirstElement;
  while( CurrentElement )
  {
    CurrentElement->Data->CallGFunction();
    TempElement = CurrentElement->NextElement;

    if( CurrentElement->Data->IsFinished() )
    {
      RemoveEvent( CurrentElement );
    }

    CurrentElement = TempElement;
  }
}