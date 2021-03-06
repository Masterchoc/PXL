#include "table.h"
#include "layout.h"

Table::Table(const glm::vec2& position, const glm::vec2& size, const std::string& font) : Widget(position, size)
{
	m_margin = glm::vec4(
		30.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_font = font;
	m_fontSize = 18.0f;
	m_blur = 0.0f;
	m_align = NVG_ALIGN_LEFT;
	m_color = nvgRGBA(255, 255, 255, 100);
	m_background = nvgRGB(40, 40, 40);
	m_stripLines = nvgRGB(35, 35, 35);
	m_borderColor = nvgRGB(70, 70, 70);
}

void Table::update(double delta)
{

}

void Table::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 pos = this->getRelativePosition();
	glm::vec2 size = this->getSize();

	switch (this->getExpandModeX())
	{
	case ExpandMode::LAYOUT:
		size.x = this->getLayout()->getComputedSize().x;
		break;
	case ExpandMode::PARENT:
		size.x = this->getParent()->getSize().x;
		break;
	case ExpandMode::FIXED:
		size.x = this->getSize().x;
		break;
	}

	switch (this->getExpandModeY())
	{
	case ExpandMode::LAYOUT:
		size.y = this->getLayout()->getComputedSize().y;
		break;
	case ExpandMode::PARENT:
		size.y = this->getParent()->getSize().y;
		break;
	case ExpandMode::FIXED:
		size.y = this->getSize().y;
		break;
	}



	switch (this->getPositionModeX())
	{
	case ExpandMode::LAYOUT:
		pos.x = this->getLayout()->getComputedPosition().x;
		break;
	case ExpandMode::PARENT:
		pos.x = this->getParent()->getPosition().x;
		break;
	case ExpandMode::FIXED:
		pos.x = this->getPosition().x;
		break;
	}

	switch (this->getPositionModeY())
	{
	case ExpandMode::LAYOUT:
		pos.y = this->getLayout()->getComputedPosition().y;
		break;
	case ExpandMode::PARENT:
		pos.y = this->getParent()->getPosition().y;
		break;
	case ExpandMode::FIXED:
		pos.y = this->getPosition().y;
		break;
	}


	nvgBeginPath(ctx);
	nvgRect(ctx,
		pos.x,
		pos.y + m_margin.x,
		this->getLayout()->getComputedSize().x,
		this->getSize().y
	);

	nvgFillColor(ctx, m_background);
	nvgFill(ctx);


	int i = 0, j = 0;
	float lh = 25.0f;
	float cw = 0;
	for (unsigned int r = 0; r < m_rows.size(); r++)
	{
		i++;
		unsigned int cs = m_rows[r]->m_columns.size();
		float y = pos.y + m_margin.x + (lh * i);
		cw = ceil(this->getLayout()->getComputedSize().x / cs);

		if (i % 2 == 0) {
			nvgBeginPath(ctx);
			nvgRect(ctx,
				pos.x,
				y - lh,
				this->getLayout()->getComputedSize().x,
				lh
			);

			nvgFillColor(ctx, m_stripLines);
			nvgFill(ctx);
		}

		for (unsigned int c = 0; c < cs; c++)
		{
			float x = pos.x + (cw * j);

			if (j > 0) 
			{
				nvgBeginPath(ctx);
				nvgRect(ctx,
					x,
					y - lh,
					1.0f,
					lh
				);

				nvgFillColor(ctx, m_borderColor);
				nvgFill(ctx);
			}

			nvgFontSize(ctx, m_fontSize);
			nvgFontFace(ctx, m_font.c_str());
			nvgTextAlign(ctx, m_align);
			nvgFontBlur(ctx, m_blur);
			nvgFillColor(ctx, m_color);

			nvgScissor(ctx, x, y - lh, cw - 10, lh);

			nvgText(ctx,
				x + 10,
				y - 7,
				m_rows[r]->m_columns[c]->m_data.c_str(),
				NULL
			);
			
			nvgResetScissor(ctx);

			j++;
		}

		j = 0;
	}

	nvgRestore(ctx);
}

Table::~Table()
{

}