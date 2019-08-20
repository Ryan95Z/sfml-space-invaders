#ifndef CORE_TOOLS_GLM_LOGGER
#define CORE_TOOLS_GLM_LOGGER

#include <glm/glm.hpp>

class GlmLogger
{
public:
	GlmLogger() = default;
	~GlmLogger() = default;

	void vec3(glm::vec3 vec) const;
	void mat4(glm::mat4 matrix) const;
};

#endif // CORE_TOOLS_GLM_LOGGER