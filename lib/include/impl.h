#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <boost/optional.hpp>

namespace oxcd8o {
namespace impl {

class Argument
{
    public:
        Argument(const std::string& shortForm, const std::string& longForm)
            : isMandatory_(false)
            , isValueless_(false)
            , helpText_()
            , metaVariable_("<value>")
            , name_(shortForm + "/" + longForm)
            , value_()
        {}

        void mandatory(bool isMandatory) { isMandatory_ = isMandatory; }
        void help(const std::string& text) { helpText_ = text; }
        void valueless(bool isValueless) { isValueless_ = isValueless; }
        void metavar(const std::string& metaVariable) { metaVariable_ = metaVariable; }
        void value(const std::string& newValue) { value_ = newValue; }

        bool mandatory() const { return isMandatory_; }
        const std::string& help() const { return helpText_; }
        bool valueless() const { return isValueless_; }
        const std::string& metavar() const { return metaVariable_; }
        const boost::optional<std::string>& value() const { return value_; }
        const std::string& name() const { return name_; }

        void validate() const;

        std::string formatHelp();
        std::string formatName() const;

    private:
        bool isMandatory_;
        bool isValueless_;
        std::string helpText_;
        std::string metaVariable_;

        std::string name_;

        boost::optional<std::string> value_;
};

class Options
{
    public:
        Options() = default;

        void parse(const std::vector<std::string>& argv);

        std::shared_ptr<Argument> getArgument(const std::string& shortForm, const std::string& longForm);

        std::string getHelp() const;

    private:
        std::unordered_map<std::string, std::shared_ptr<Argument>> arguments_;
};

} // namespace impl
} // namespace oxcd8o