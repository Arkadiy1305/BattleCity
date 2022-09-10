

#include "ShaderProgramm.h"


namespace Renderer
{
	ShaderProgram::ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader)
	{
		GLuint vertex_shaderID;
		if (!createShader(vertex_shader, GL_VERTEX_SHADER, vertex_shaderID))
		{
			std::cerr << "VERTEX Shader compile time error" << std::endl;
			return;
		}
		
		GLuint fragment_shaderID;
		if (!createShader(fragment_shader, GL_FRAGMENT_SHADER, fragment_shaderID))
		{
			std::cerr << "FRAGMENT Shader compile time error" << std::endl;
			glDeleteShader(vertex_shaderID);
			return;
		}
		
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex_shaderID);	
		glAttachShader(m_ID, fragment_shaderID);
		glLinkProgram(m_ID);
		
		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link time error:\n" << infoLog << std::endl;
			
		}
		else
		{
			m_is_Compiled = true;
		}
		
		glDeleteShader(vertex_shaderID);	
		glDeleteShader(fragment_shaderID);
		
	}
	
	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);
		
		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile time error:\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}
	
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}
	
	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}
	
	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_is_Compiled = shaderProgram.m_is_Compiled;
		
		shaderProgram.m_ID = 0;
		shaderProgram.m_is_Compiled = false;
		return *this;
	}
	
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_is_Compiled = shaderProgram.m_is_Compiled;
		
		shaderProgram.m_ID = 0;
		shaderProgram.m_is_Compiled = false;
	}	
}
