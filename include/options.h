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

        Argument&& mandatory(bool isMandatory = true);
        Argument&& help(const std::string& text);
        Argument&& valueless(bool isValueless = true);
        Argument&& metavar(const std::string& metaVariable);

        // Not exactly the most elegant solution, but saves lots of coding because do
        // not require separate classes for different types of values. And still allows
        // to hide impl from end user completely.
        template <class T>
        Argument&& defaultValue(const T& defaultValue)
        {
            setDefault(boost::lexical_cast<std::string>(defaultValue));
        }

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

        void parse(int argc, char** argv);
        void parse(const std::vector<std::string>& argv);

        Argument argument(const std::string& shortForm, const std::string& longForm) const;

        std::string getHelp() const;

    private:
        std::shared_ptr<impl::Options> impl_;
};

} //namespace oxcd8o