#include "lib/include/impl.h"
#include "include/error.h"

#include <sstream>
#include <map>

namespace oxcd8o {
namespace impl {

void Argument::validate() const
{
    if (isMandatory_ && !value_) {
        throw MandatoryError() << "Argument " << name_ << " is mandatory.";
    }
}

std::string Argument::formatHelp()
{
    std::stringstream ss;
    ss << "  " << name_ << (isValueless_ ? "" : " " + metaVariable_) << std::endl
       << "        ("  << (isMandatory_ ? "mandatory" : "optional") << ")" << std::endl
       << "    " << helpText_ << std::endl;
    return ss.str();
}

void Options::parse(const std::vector<std::string>& argv)
{
    for (const auto& arg : arguments_) {
        arg.second->validate();
    }
}

std::shared_ptr<Argument> Options::getArgument(const std::string& shortForm, const std::string& longForm)
{
    std::shared_ptr<Argument> newArgument(new Argument(shortForm, longForm));
    arguments_.emplace(shortForm, newArgument);
    arguments_.emplace(longForm, newArgument);

    return newArgument;
}

std::string Options::getHelp() const
{
    std::map<std::string, std::shared_ptr<Argument>> uniqueArguments;
    for (const auto& elem : arguments_) {
        const auto& name = elem.second->name();
        if (!uniqueArguments.count(name)) {
            uniqueArguments[name] = elem.second;
        }
    }

    std::stringstream ss;
    for (const auto& elem : uniqueArguments) {
        ss << elem.second->formatHelp() << std::endl;
    }
    return ss.str();
}

} // namespace impl
} // namespace oxcd8o