#include "DelayedActions.h"

DelayedActions::DelayedActions() : DelayedActionsBase()
{
}

DelayedActions::~DelayedActions()
{
}

void DelayedActions::setActionTime(const Action a, const Time t)
{
  doSetActionTime(a, t);
}
void DelayedActions::cancelAction(const Action a)
{
	doCancelAction(a);
}
