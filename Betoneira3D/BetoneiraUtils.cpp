#include "BetoneiraUtils.h"

#include "Logger.h"

bool Betoneira::handleStatusLogging(Betoneira::Status status) {
    if (status != Betoneira::Status::OK) {
        Betoneira::Logger::log({ "(", std::to_string(status), "): ", Betoneira::getStatusMessage(status) }, { "Betoneira3D", "ERROR" });
        return 1;
    }
    return 0;
}