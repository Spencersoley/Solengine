#include <string>

namespace Solengine 
{
	class ErrorManager
	{
	public:
		static void FatalError(std::string errorString);
	};
}
