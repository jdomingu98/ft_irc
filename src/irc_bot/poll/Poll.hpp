#ifndef POLL_HPP
# define POLL_HPP

# include <string>
# include <vector>
# include <exception>
# include <sstream>

class Poll {
    private:
      std::string _question;
      std::vector<std::string> _options;
      std::vector<int> _votes;

    public:
      Poll(const std::string &question, const std::vector<std::string> &options);
      Poll();
      ~Poll();
      void vote(size_t option);
      std::string getInfo() const;
      std::string getResults() const;
      const std::string &getQuestion() const;
      const std::vector<std::string> &getOptions() const;
      const std::vector<int> &getVotes() const;
      const std::string getWinningOption() const;
      static const std::string usage(std::string option);

      class InvalidOptionException : public std::exception {
        public:
          const char *what() {
            return "Invalid option";
          }
      };
};

#endif