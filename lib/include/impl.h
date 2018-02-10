#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <iosfwd>

#include <boost/optional.hpp>

namespace oxcd8o {
namespace impl {

class Argument
{
    public:
        Argument(std::string shortForm, std::string longForm)
            : isMandatory_(false)
            , isValueless_(false)
            , helpText_()
            , shortForm_(std::move(shortForm))
            , longForm_(std::move(longForm))
            , value_()
        {}

        void mandatory(bool isMandatory) { isMandatory_ = isMandatory; }
        void help(const std::string& text) { helpText_ = text; }
        void valueless(bool isValueless) { isValueless_ = isValueless; }

        const boost::optional<std::string>& value() const { return value_; }

        void validate() const;

        friend std::ostream& operator<<(std::ostream& os, const Argument& arg);

    private:
        bool isMandatory_;
        bool isValueless_;
        std::string helpText_;

        std::string shortForm_;
        std::string longForm_;

        boost::optional<std::string> value_;
};

class Options
{
    public:
        Options() = default;

        void parse(int argc, char** argv);

        std::shared_ptr<Argument> getArgument(const std::string& shortForm, const std::string& longForm);

        friend std::ostream& operator<<(std::ostream& os, const Options& arg);

    private:
        std::unordered_map<std::string, std::shared_ptr<Argument>> arguments_;
};

std::ostream& operator<<(std::ostream& os, const Argument& arg);
std::ostream& operator<<(std::ostream& os, const Options& arg);

} // namespace impl
} // namespace oxcd8o