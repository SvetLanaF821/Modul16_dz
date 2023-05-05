#include "Message.h"

Message::Message(const std::string& from, const std::string& to, const std::string& message) : _from(from), _to(to), _message(message) {}

const std::string& Message::getFrom() const { return _from; }
void Message::setFrom(const std::string& from) { _from = from; }
const std::string& Message::getTo() const { return _to; }
void Message::setTo(const std::string& to) { _to = to; }
const std::string& Message::getMessage() const { return _message; }
void Message::setMessage(const std::string& message) { _message = message; }