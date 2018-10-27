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
	bool loopAnimations = false;
	int gizmoX = 200, gizmoY = 900, gizmoSize = 300;
};

#endif // !
