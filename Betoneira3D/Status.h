#pragma once

#include <string>

namespace Betoneira {
	enum Status {
		OK = 0,
		DOES_NOT_EXIST,
		NOT_A_FILE,
		FILE_CLOSED,
		SOMETHING_WRONG,
	};

	std::string getStatusMessage(Status status);
}