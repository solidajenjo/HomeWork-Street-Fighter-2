#ifndef __SUB_MODULE_EDITOR_H
#define __SUB_MODULE_EDITOR_H
class SubModuleEditor
{
public:
	SubModuleEditor() {};
	~SubModuleEditor() {};

	virtual bool drawSubmodule()
	{
		return true;
	};
};

#endif
