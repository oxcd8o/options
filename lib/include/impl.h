#pragma once

#include <memory>
#include <string>
#include <vector>

#include <boost/optional.hpp>

namespace oxcd8o {
namespace impl {

class Argument
{
    public:
        Argument(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& shortForm, const std::string& longForm);

        void mandatory(bool isMandatory) { isMandatory_ = isMandatory; }
        //void multiple(bool isMultiple) { isMultiple_ = isMultiple; }
        void help(const std::string& text) { helpText_ = text; }
        void valueless(bool isValueless) { isValueless_ = isValueless;}

        boost::optional<std::string> value();

    private:
        boost::optional<std::string> optionName(const std::string& arg);

        bool isMandatory_;
        bool isMultiple_;
        bool isValueless_;
        std::string helpText_;

        std::shared_ptr<std::vector<std::string>> arguments_;
        std::string shortForm_;
        std::string longForm_;
};

class Options
{
    public:
        Options(int argc, char** argv);

        std::unique_ptr<Argument> getArgument(const std::string& shortForm, const std::string& longForm);

    private:
        std::shared_ptr<std::vector<std::string>> arguments_;
};

} // namespace impl
} // namespace oxcd8o