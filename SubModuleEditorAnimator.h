#ifndef __SUB_MODULE_EDITOR_ANIMATOR_H
#define __SUB_MODULE_EDITOR_ANIMATOR_H

#include "SubModuleEditor.h"
class PlayerAnimationBase;

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
	bool loopAnimations = false, ok = false;
	char filename[50];
	char status[50];
	char sheetName[50];
	int gizmoX = 200, gizmoY = 900, gizmoSize = 300;

	PlayerAnimationBase* animSheet = nullptr;
	int currentAnimation = -1;
};

#endif // !
