#ifndef __SUB_MODULE_EDITOR_CONSOLE_H
#define __SUB_MODULE_EDITOR_CONSOLE_H

#include "SubModuleEditor.h"

class SubModuleEditorConsole :
	public SubModuleEditor
{
public:
	SubModuleEditorConsole();
	~SubModuleEditorConsole();
	
	bool drawSubmodule();

};

#endif // !
