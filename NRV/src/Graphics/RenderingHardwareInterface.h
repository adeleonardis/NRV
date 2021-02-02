#pragma once

#include <unordered_map>
#include <string>
#include <stdint.h>

namespace NRV {
	namespace Graphics {

		class RenderingHardwareInterface
		{
		protected:
			using Name = std::string&;
			using UInt = std::uint32_t;
			using NameMap = std::unordered_map<Name, UInt>;
		private:
			NameMap* VertexBufferCache,
				* VertexArrayCache,
				* IndexBufferCache,
				* ProgramCache,
				* ShaderCache;
		public:
			virtual ~RenderingHardwareInterface() {}

			virtual void CreateWindow(const char* window_name, uint32_t width, uint32_t height, bool IsFullscreen) = 0;
			void CreateWindow(const char* window_name, uint32_t width, uint32_t height) { CreateWindow(window_name, width, height, false); }

			//// Vertex Array functions
			//virtual void CreateVertexArray(Name name) = 0;
			//virtual void BindVertexArray(UInt id) = 0;
			////inline  void BindVertexArray(Name name) { BindVertexArray(VertexArrayCache->find(name)->second); }

			//// Vertex Buffer functions
			//virtual void CreateVertexBuffer(Name name, void* data, size_t size, UInt info) = 0;
			//virtual void BindVertexBuffer(UInt id) = 0;
			////inline  void BindVertexBuffer(Name name) { BindVertexBuffer(VertexBufferCache->find(name)->second); }
			////virtual void DrawVertexBuffer(Name vertexBuffer, Name vertexArray, UInt info) = 0;

			//// Index Buffer functions
			//virtual void CreateIndexBuffer(Name name, void* data, size_t size, UInt info) = 0;
			//virtual void BindIndexBuffer(UInt id) = 0;
			////inline  void BindIndexBuffer(Name name) { BindIndexBuffer(VertexBufferCache->find(name)->second); }
			////virtual void DrawIndexBuffer(Name indexBuffer, Name vertexBuffer, Name vertexArray) = 0;

			//// Shader functions
			//virtual void CreateShader(Name name, std::string& source, UInt info) = 0;

			//// Program functions
			//virtual void CreateProgram(Name name) = 0;
			//virtual void BindProgram(UInt id) = 0;
			////inline  void BindProgram(Name name) { BindProgram(ProgramCache->find(name)->second); }
			//virtual void AttachShader(Name program, Name shader) = 0;
			//virtual void RemoveShader(Name program, Name shader) = 0;

		};

	}
}