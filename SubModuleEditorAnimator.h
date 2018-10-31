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
	int gizmoX = 100, gizmoY = 1000, gizmoSize = 300, xSheet = 0, ySheet = 0, xFrame = 60, yFrame = 340;

	PlayerAnimationBase* animSheet = nullptr;
	int currentAnimation = 0, currentFrame = 0, lowCut = 50;
};

#endif // !
