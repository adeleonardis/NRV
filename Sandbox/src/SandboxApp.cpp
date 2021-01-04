#include <NRV.h>

class Sandbox : public NRV::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

NRV::Application* NRV::CreateApplication()
{
	return new Sandbox();
}