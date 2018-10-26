#ifndef __SUB_MODULE_EDITOR_ANIMATOR_H
#define __SUB_MODULE_EDITOR_ANIMATOR_H

#include "SubModuleEditor.h"

class SubModuleEditorAnimator :
	public SubModuleEditor
{
public:
	//methods

	SubModuleEditorAnimator();
	~SubModuleEditorAnimator();
	
	bool drawSubmodule();

	//members
	
	bool active = false;
	int xSheet = 0, ySheet = 0;
};

#endif // !
