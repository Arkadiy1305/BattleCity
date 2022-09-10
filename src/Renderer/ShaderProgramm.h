#pragma once

#include <glad/glad.h>
#include <string>
#include <ostream>
#include <iostream>

namespace Renderer{
	class ShaderProgram{
	public:
		ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader);
		~ShaderProgram();
		bool is_compiled() const { return m_is_Compiled; }
		void use() const;
		
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_is_Compiled = false;
		GLuint m_ID = 0;
	};
}
