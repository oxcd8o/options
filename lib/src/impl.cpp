#include "lib/include/impl.h"
#include "include/error.h"

namespace oxcd8o {
namespace impl {

Argument::Argument(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& shortForm, const std::string& longForm)
    : isMandatory_(false)
    , isMultiple_(false)
    , isValueless_(false)
    , helpText_()
    , arguments_(arguments)
    , shortForm_(shortForm)
    , longForm_(longForm)
{
}

boost::optional<std::string> Argument::value()
{
    boost::optional<std::string> result;

    for (auto it = arguments_->begin(); it != arguments_->end(); ++it) {
        auto value = optionName(*it);

        if (!value) {
            continue;
        }
        if (*value != shortForm_ && *value != longForm_) {
            continue;
        }

        auto valueIt = it + 1;

        if (isValueless_) {
            *result = "";
        } else if (valueIt != arguments_->end()) {
            *result = *valueIt;
        } {
            throw ValueError() << "Argument " << *it << " has no value.";
        }
    }

    if (isMandatory_ && !result) {
        throw ValueError() << "Argument " << longForm_ << "/" << shortForm_ << " was not found.";
    }

    return result;
}

boost::optional<std::string> Argument::optionName(const std::string& arg)
{
    boost::optional<std::string> result;

    if (arg.size() == 2 && arg[0] == '-' && arg[1] != '-') {
        result = arg.substr(1);
    } else if (arg.size() > 2 && arg[0] == '-' && arg[1] == '-') {
        result = arg.substr(2);
    }

    return result;
}

Options::Options(int argc, char** argv)
    : arguments_(new std::vector<std::string>())
{
    for (int i = 1; i < argc; ++i) {
        arguments_->emplace_back(argv[i]);
    }
}

std::unique_ptr<Argument> Options::getArgument(const std::string& shortForm, const std::string& longForm)
{
    return std::unique_ptr<Argument>(nullptr);
}

} // namespace impl
} // namespace oxcd8o