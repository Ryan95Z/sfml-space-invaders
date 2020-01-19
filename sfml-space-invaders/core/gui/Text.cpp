#include "Text.hpp"

#define DEFAULT_SCALE 1.0f
#define DEFAULT_POSITION glm::fvec2(0.0f, 0.0f);
#define DEFAULT_COLOUR glm::vec3(1.0f, 1.0f, 1.0f)

Text::Text()
{
	setUp("", DEFAULT_COLOUR);
}

Text::Text(std::string text)
{
	setUp(text, DEFAULT_COLOUR);
}

Text::Text(std::string text, glm::vec3 colour)
{
	setUp(text, colour);
}

Text::~Text()
{
}

void Text::setScale(float scale)
{
	details.scale = scale;
}

void Text::setFont(Font * f)
{
	font = f;
	details.char_set = f->getCharacters();
}

void Text::setPosition(float x, float y)
{
	setPosition(glm::fvec2(x, y));
}

void Text::setPosition(glm::fvec2 pos)
{
	details.pos = pos;
}

void Text::setString(std::string text)
{
	details.text = text;
}

void Text::setColour(glm::vec3 colour)
{
	details.colour = colour;
}

void Text::setProjection(glm::mat4 projection)
{
	details.projection = projection;
}

void Text::draw()
{
	TextRenderer::getInstance().render(details);
}

void Text::setUp(std::string text, glm::vec3 colour)
{
	details.text = text;
	details.colour = colour;
	details.scale = DEFAULT_SCALE;
	details.pos = DEFAULT_POSITION;
}
