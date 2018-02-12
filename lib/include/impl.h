#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <boost/optional.hpp>

const std::string TRUE  = "1";
const std::string FALSE = "0";

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
            , defaultValue_()
            , value_()
        {}

        void mandatory() { isMandatory_ = true; }
        void help(const std::string& text) { helpText_ = text; }
        void valueless()
        {
            isValueless_ = true;
            defaultValue_ = FALSE;
            metaVariable_.reset();
        }
        void metavar(const std::string& metaVariable) { metaVariable_ = metaVariable; }
        void value(const std::string& newValue) { value_ = newValue; }
        void defaultValue(const std::string& value) { defaultValue_ = value; }

        bool isMandatory() const { return isMandatory_; }
        const std::string& help() const { return helpText_; }
        bool isValueless() const { return isValueless_; }
        const std::string& metavar() const { return *metaVariable_; }
        const boost::optional<std::string>& value() const { return (value_ ? value_ : defaultValue_); }
        const boost::optional<std::string>& defaultValue() const { return defaultValue_; }
        const std::string& name() const { return name_; }

        operator bool() const { return static_cast<bool>(value_) || static_cast<bool>(defaultValue_); }

        void validate() const;

        std::string formatHelp();
        std::string formatName() const;

    private:
        bool isMandatory_;
        bool isValueless_;
        std::string helpText_;
        boost::optional<std::string> metaVariable_;

        std::string name_;

        boost::optional<std::string> defaultValue_;
        boost::optional<std::string> value_;
};

class Options
{
    public:
        Options()
            : allowUnknown_(false)
        {}

        void allowUnknown() { allowUnknown_ = true; }

        void parse(const std::vector<std::string>& argv);

        std::shared_ptr<Argument> getArgument(const std::string& shortForm, const std::string& longForm);

        std::string getHelp() const;

    private:
        bool allowUnknown_;
        std::unordered_map<std::string, std::shared_ptr<Argument>> arguments_;
};

} // namespace impl
} // namespace oxcd8o