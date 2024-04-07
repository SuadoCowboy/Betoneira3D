#include "Status.h"

std::string Betoneira::getStatusMessage(Betoneira::Status status) {
	switch (status) {
	case DOES_NOT_EXIST:
		return "does not exist";
	case NOT_A_FILE:
		return "not a file";
	case FILE_CLOSED:
		return "file closed";
	case SOMETHING_WRONG:
		return "something went wrong";
	default:
		return "";
	}
}