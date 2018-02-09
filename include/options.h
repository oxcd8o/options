#pragma once

#include <memory>
#include <string>
#include <type_traits>

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
        Argument(std::unique_ptr<impl::Argument>&& data);

        Argument&& mandatory(bool isMandatory = true);
        Argument&& help(const std::string& text);
        //Argument&& multiple(bool isMultiple = true);
        Argument&& valueless(bool isValueless = true);

        template <class T>
        T as(const T& defaultValue) const
        {
            boost::optional<std::string> value = retrieveRawValue();
            return (value ? boost::lexical_cast<T>(*value) : defaultValue);
        }

    private:
        boost::optional<std::string> retrieveRawValue() const;

        std::unique_ptr<impl::Argument> impl_;
};

class Options
{
    public:
        Options(int argc, char** argv);
        ~Options();

        Argument getArgument(const std::string& shortForm, const std::string& longForm) const;

    private:
        impl::Options* impl_;
};

} //namespace oxcd8o