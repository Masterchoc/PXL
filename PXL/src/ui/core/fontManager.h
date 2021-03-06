#pragma once

#include <iostream>
#include <filesystem>
#include <dirent.h>

#include "../nanovg/nanovg.h"
#include "../../core/manager.h"

class FontManager : public Manager
{
public:
	FontManager();

	inline void setContext(NVGcontext* ctx) { m_ctx = ctx; }
	void loadFonts(char* path);

	virtual ~FontManager();

private:
	NVGcontext* m_ctx;
};

