#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	for (p2List_item<Gui*>* i = elements.start; i != NULL; i = i->next)
	{
		i->data->Update();
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	for (p2List_item<Gui*>* i = elements.start; i != NULL; i = i->next)
	{
		i->data->Draw();
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (p2List_item<Gui*>* i = elements.start; i != NULL ; i = i->next)
	{
		RELEASE(i->data);
	}
	elements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------
const GuiImage* j1Gui::CreateGuiImage(SDL_Rect rect, iPoint pt)
{
	GuiImage* img = new GuiImage(rect, pt);

	img->texture = atlas;

	elements.add(img);	

	return img;
}

const GuiText* j1Gui::CreateGuiText(p2SString string, iPoint pt)
{
	GuiText* txt = new GuiText(string, pt);

	elements.add(txt);

	return txt;
}

const GuiButton* j1Gui::CreateGuiButton(SDL_Rect drect, SDL_Rect hrect, SDL_Rect crect, iPoint pt)
{
	GuiButton* but = new GuiButton(drect, hrect, crect, pt);

	but->texture = atlas;

	elements.add(but);

	return but;
}

bool GuiImage::Update()
{

	return true;
}

bool GuiText::Update()
{
	return true;
}

bool GuiButton::Update()
{
	iPoint mousepos;
	App->input->GetMousePosition(mousepos.x, mousepos.y);
	if (mousepos.x > position.x && mousepos.y > position.y && mousepos.x < position.x + defrect.w && mousepos.y < position.y + defrect.h)
	{
		ev = Hover;
		if (App->input->GetMouseButtonDown(1))
			ev = Clicked;
	}
	else
		ev = Default;

	return true;
}

void GuiImage::Draw()
{
	App->render->Blit(texture, position.x, position.y, &texrect);
}

void GuiText::Draw()
{
	SDL_Texture* texture = App->fonts->Print(text.GetString(), { 255, 255, 255 }, App->fonts->default);
	App->render->Blit(texture, position.x, position.y);
}

void GuiButton::Draw()
{
	if (this->ev == Default)
		App->render->Blit(texture, position.x, position.y, &defrect);
	else if (this->ev == Hover)
		App->render->Blit(texture, position.x, position.y, &hovrect);
	else if (this->ev == Clicked)
		App->render->Blit(texture, position.x, position.y, &clickrect);
}

GuiImage::~GuiImage()
{
}

GuiText::~GuiText()
{
}

GuiButton::~GuiButton()
{
}