#include "ACommand.hpp"

/**
 * ACommand constructor.
 * 
 * @param needValidation If the command needs validation
*/
ACommand::ACommand(bool needsValidation) : _needsValidation(needsValidation) {}


/**
  * Getter for the needValidation attribute.
  * 
  * @return If the command needs validation
  */
bool ACommand::needsValidation() {
    return this->_needsValidation;
}