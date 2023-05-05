#pragma once

#include <string>

class Message
{
	std::string _from;
	std::string _to;
	std::string _message;

public:
	Message() = default;
	Message(const std::string& from, const std::string& to, const std::string& message);
	~Message() = default;

	const std::string& getFrom() const;
	void setFrom(const std::string& from);
	const std::string& getTo() const;
	void setTo(const std::string& to);
	const std::string& getMessage() const;
	void setMessage(const std::string& message);
};