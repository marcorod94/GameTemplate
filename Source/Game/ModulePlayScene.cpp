#include "Main/Application.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModulePlayScene.h"

ModulePlayScene::ModulePlayScene(bool active) : Module(active)
{

}

bool ModulePlayScene::Init()
{
	text = new RenderObject{
		App->texture->LoadText("Done by marcorod94", new float3(255,0,0)),
		{(SCREEN_WIDTH - (SCREEN_WIDTH * 0.5F)) * 0.5F, (SCREEN_HEIGHT - SCREEN_HEIGHT * 0.05F) * 0.5F, SCREEN_WIDTH * 0.5F, SCREEN_HEIGHT * 0.05F},
	};
	return true;
}

UpdateStatus ModulePlayScene::Update()
{
	App->renderer->Blit(text->texture, &text->renderSection);
	return UpdateStatus::CONTINUE;
}

bool ModulePlayScene::CleanUp()
{
	return true;
}