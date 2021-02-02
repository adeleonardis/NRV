#pragma once

#include "../RenderingHardwareInterface.h"

namespace NRV {
	namespace Graphics {

		class OpenGL : public RenderingHardwareInterface
		{
		public:
			OpenGL();
			~OpenGL() override;
			void CreateWindow(const char* window_name, uint32_t width, uint32_t height, bool is_fullscreen) override;
		};

	}
}
