#include "ACommand.hpp"

/**
 * ACommand constructor.
 * 
 * @param needValidation If the command needs validation
 */
ACommand::ACommand(bool needsValidation) : _needsValidation(needsValidation) {}

/**
 * ACommand destructor.
 */
ACommand::~ACommand() {}

/**
  * Getter for the needValidation attribute.
  * 
  * @return If the command needs validation
  */
bool ACommand::needsValidation() const {
    return this->_needsValidation;
}