#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Fonts.h"
#include "SDL_image/include/SDL_image.h"

#define CURSOR_WIDTH 2

enum event
{
	Default,
	Hover,
	Unhover,
	Clicked,
	Released,
	InputChanged,
	InputSubmit,
	GainFocus,
	LoseFocus
};

// TODO 1: Create your structure of classes
class Gui
{
public:
	Gui()
	{}

	virtual ~Gui()
	{}

	iPoint position;

	virtual void Draw()
	{}

	virtual bool Update()
	{
		return true;
	}

private:
};

class GuiImage : public Gui
{
public:
	SDL_Rect texrect;

	SDL_Texture* texture;

	GuiImage(SDL_Rect rct, iPoint pt)
	{
		texrect = rct;
		position = pt;
	}

	virtual ~GuiImage();

	bool Update();

	void Draw();
};

class GuiText : public Gui
{
public:
	p2SString text;

	GuiText(p2SString str, iPoint pt)
	{
		text = str;
		position = pt;
	}

	virtual ~GuiText();

	bool Update();

	void Draw();
};

class GuiButton : public Gui
{
public:
	SDL_Rect defrect;

	SDL_Rect hovrect;

	SDL_Rect clickrect;

	SDL_Texture* texture;

	event ev = Default;

	GuiButton(SDL_Rect drct, SDL_Rect hrct, SDL_Rect crct, iPoint pt)
	{
		defrect = drct;
		hovrect = hrct;
		clickrect = crct;
		position = pt;
	}

	virtual ~GuiButton();

	bool Update();

	void Draw();
};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	// TODO 2: Create the factory methods
	// Gui creation functions

	const GuiImage* CreateGuiImage(SDL_Rect rect, iPoint pt);
	const GuiButton* CreateGuiButton(SDL_Rect drect, SDL_Rect hrect, SDL_Rect crect, iPoint pt);
	const GuiText* CreateGuiText(p2SString string, iPoint pt);

	SDL_Texture* GetAtlas() const;

private:

	_TTF_Font* font;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2List<Gui*> elements;
};

#endif // __j1GUI_H__