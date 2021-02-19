#include "Main/Application.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

ModuleTexture::~ModuleTexture()
{
	IMG_Quit();
}

bool ModuleTexture::Init()
{
	LOG("Init Image library");
	bool success = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		success = false;
	}

	LOG("Init Font library");
	if (TTF_Init() == -1)
	{
		LOG("Could not initialize Font lib. SDL_ttf Error: %s", TTF_GetError());
		success = false;
	}
	else
	{
		font = TTF_OpenFont("Assets/Font/8-BIT WONDER.TTF", 50);
		if (font == nullptr)
		{
			LOG("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
	}
	return success;
}

bool ModuleTexture::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (auto iterator = textures.begin(); iterator != textures.end(); ++iterator)
	{
		SDL_DestroyTexture((*iterator).second);
	}
	textures.clear();
	TTF_CloseFont(font);
	font = nullptr;
	return true;
}

SDL_Texture* ModuleTexture::Load(const char* path)
{
	auto iterator = textures.find(path);
	if (iterator != textures.end())
	{
		return (*iterator).second;
	}

	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = LoadSurface(path);



	if (surface)
	{
		texture = SDL_CreateTextureFromSurface(App->renderer->renderer, surface);
		if (texture == nullptr)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textures.emplace(std::make_pair(path, texture));
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

SDL_Surface* ModuleTexture::LoadSurface(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);

	if (surface == nullptr)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	return surface;
}

SDL_Texture* ModuleTexture::LoadText(const char* text, const float3* color)
{
	auto iterator = textures.find(text);
	if (iterator != textures.end())
	{
		return (*iterator).second;
	}

	SDL_Texture* texture = nullptr;
	SDL_Color textColor = { 0, 0, 0 };
	if (color)
	{
		textColor = { static_cast<Uint8>(color->x),
						static_cast<Uint8>(color->y),
						static_cast<Uint8>(color->z) };
	}
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);

	if (surface)
	{
		texture = SDL_CreateTextureFromSurface(App->renderer->renderer, surface);
		if (texture == nullptr)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textures.emplace(std::make_pair(text, texture));
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

void ModuleTexture::Unload(const SDL_Texture* texture)
{
	for (auto iterator = textures.begin(); iterator != textures.end(); ++iterator)
	{
		if ((*iterator).second == texture)
		{
			SDL_DestroyTexture((*iterator).second);
			textures.erase(iterator);
			break;
		}
	}
}
