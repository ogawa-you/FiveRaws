#include "StoneStatus.h"

void StoneStatus::SetCount(int _count)
{
	if (count < _count)
	{
		count = _count;
	}
}

void StoneStatus::Initiarize()
{
	count = 0;
}
