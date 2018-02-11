/*
 * Usage is as simple as:
 * 
 * auto op = Options();
 * 
 * auto config = op.argument("-c", "--config")
 *                 .help("Path to config file")
 *                 .mandatory()
 *                 .metavar("<config path>");
 * auto flag = op.argument("-f", "--flag")
 *               .help("Some flag, that is implicitly defaulted to false")
 *               .valueless();
 * 
 * op.parse(argc, argv);
 * 
 * auto configPath = config.as<std::string>();
 * auto flagIsSet = flag.as<bool>();
 */


#pragma once

#include <memory>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

namespace oxcd8o {

namespace impl {
    class Options;
    class Argument;
}

class Argument
{
    public:
        Argument(std::shared_ptr<impl::Argument> data)
            : impl_(std::move(data))
        {}

        // Make this argument mandatory
        Argument&& mandatory();
        // Add help text
        Argument&& help(const std::string& text);
        // This argument will be true or false and won't treat next token from command line as value
        Argument&& valueless();
        // Metavariable name to be displayed at help message
        Argument&& metavar(const std::string& metaVariable);

        // Not exactly the most elegant solution, but saves lots of coding because do
        // not require separate classes for different types of values. And still allows
        // to hide impl from end user completely.
        template <class T>
        Argument&& defaultValue(const T& defaultValue)
        {
            setDefault(boost::lexical_cast<std::string>(defaultValue));
            return std::forward<Argument>(*this);
        }

        // Check if it's save to get value
        operator bool() const;

        // Get value casted to specified type (like int value = arg.as<int>())
        template <class T>
        T as() const { return boost::lexical_cast<T>(retrieveRawValue()); }

    private:
        const std::string& retrieveRawValue() const;
        void setDefault(const std::string& value);

        std::shared_ptr<impl::Argument> impl_;
};

class Options
{
    public:
        Options();

        // Ignore arguments, that were not explicitly registered
        Options&& allowUnknown();

        // Parse command line and fill arguments with values
        // If some option is specified more than once, the last value will be used
        void parse(int argc, char** argv);
        void parse(const std::vector<std::string>& argv);

        // Register argument. Not idempotent, second call with same values will reset parameters to default.
        // Also should be called before parse()
        Argument argument(const std::string& shortForm, const std::string& longForm) const;

        // Formats help message with arguments descriptions
        std::string getHelp() const;

    private:
        std::shared_ptr<impl::Options> impl_;
};

} //namespace oxcd8o