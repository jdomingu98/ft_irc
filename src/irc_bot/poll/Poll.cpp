#include "Poll.hpp"

Poll::Poll() {}

Poll::Poll(const std::string &question, const std::vector<std::string> &options) :
  _question(question),
  _options(options),
  _votes(options.size(), 0) {}

Poll::~Poll() {}

void Poll::vote(size_t option) {
  if (option >= _options.size()) {
    throw InvalidOptionException();
  }
  _votes[option]++;
}

std::string Poll::getInfo() const {
  std::string info = "Poll: " + _question + "\n";
  std::stringstream out;
  for (size_t i = 0; i < _options.size(); i++) {
    out << i << ": " << _options[i] << "\n";
  }
  return info + out.str();
}

std::string Poll::getResults() const {
  std::string results = "Results for poll: " + _question + "\n";
  std::stringstream out;
  for (size_t i = 0; i < _options.size(); i++) {
    out << _options[i] << ": " << _votes[i] << "\n";
  }
  return results + out.str();
}

const std::string Poll::getWinningOption() const {
  int maxVotes = 0;
  size_t numWinners = 0;
  for (size_t i = 0; i < _votes.size(); i++) {
    if (_votes[i] == maxVotes) {
      numWinners++;
    } else if (_votes[i] > maxVotes) {
      maxVotes = _votes[i];
      numWinners = 1;
    }
  }
  // If there is a tie, we should return all the options with the maximum number of votes:
  std::string result = "";
  if (numWinners > 1) {
    result += "Tie between: ";
  } else {
    result += "Winner: ";
  }
  for (size_t i = 0; i < _votes.size(); i++) {
    if (_votes[i] == maxVotes) {
      result += _options[i];
      if (i < numWinners - 2) {
        result += ", ";
      }
      if (i == numWinners - 2) {
        result += " and ";
      }
    }
  }
  return result;
}

const std::string Poll::usage(std::string option) {
  if (option == "") {
    std::string response = "Usage: !poll <start|vote|options|finish>\n";
    response += "start: Start a new poll in the channel\n";
    response += "vote: Vote for an option of the poll of the channel\n";
    response += "options: Get the options of the current poll\n";
    response += "finish: Finish the current poll\n";
    return response;
  }
  if (option == "start") {
    return "Usage: !poll start <question> <option1> <option2> ...";
  } else if (option == "vote") {
    return "Usage: !poll vote <option>";
  } else if (option == "options") {
    return "Usage: !poll options";
  } else if (option == "finish") {
    return "Usage: !poll finish";
  }
  return "";
}

const std::string &Poll::getQuestion() const {
  return _question;
}

const std::vector<std::string> &Poll::getOptions() const {
  return _options;
}

const std::vector<int> &Poll::getVotes() const {
  return _votes;
}

