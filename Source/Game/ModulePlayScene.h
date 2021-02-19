#ifndef ModulePlayScene_h
#define ModulePlayScene_h

#include "Module/Module.h"

struct RenderObject;

class ModulePlayScene : public Module
{
public:
	explicit ModulePlayScene(bool active = true);
	~ModulePlayScene() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	bool CleanUp() override;
	RenderObject* text = nullptr;

};
#endif
