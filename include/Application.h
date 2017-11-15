#pragma once
#include "SBTStateStack.h"
#include "ResourceHolder.h"
#include "SBTAbstractCommandManager.h"
#include "SBTGameWindow.h"
#include "SBTAbstractApplication.h"

class Application: public SBTAbstractApplication
{
public:
	Application();
protected:
	void				registerStates();
};

