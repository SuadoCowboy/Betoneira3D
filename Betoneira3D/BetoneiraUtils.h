#pragma once

#include "Status.h"

namespace Betoneira {
	// @return 1 if error 0 if Status is Status::OK
	bool handleStatusLogging(Status status);
}