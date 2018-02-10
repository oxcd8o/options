#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <iosfwd>

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
        //template <class T>
        //Argument&& default(const T& defaultValue);

        template <class T>
        T as() const { return boost::lexical_cast<T>(retrieveRawValue()); }

        friend std::ostream& operator<<(std::ostream& os, const Argument& arg);

    private:
        boost::optional<std::string> retrieveRawValue() const;

        std::shared_ptr<impl::Argument> impl_;
};

class Options
{
    public:
        Options();

        void parse(int argc, char** argv);

        Argument argument(const std::string& shortForm, const std::string& longForm) const;

        friend std::ostream& operator<<(std::ostream& os, const Options& arg);

    private:
        std::shared_ptr<impl::Options> impl_;
};

std::ostream& operator<<(std::ostream& os, const Argument& arg);
std::ostream& operator<<(std::ostream& os, const Options& arg);

} //namespace oxcd8o