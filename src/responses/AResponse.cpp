#include "AResponse.hpp"

/**
 * Constructs a new Response.
 * 
 * @param nickname The nickname of the user
 * @param codeNumber The code number of the response
 */
Response::Response(std::string codeNumber, std::string nickname)
    : _codeNumber(codeNumber), _nickname(nickname) {}

/**
 * Destroys the Response.
 */
Response::~Response() {}

// =================================================================================

