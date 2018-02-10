#include "lib/include/impl.h"
#include "include/error.h"

#include <ostream>

namespace oxcd8o {
namespace impl {

void Argument::validate() const
{
    auto argumentName = [this] { return shortForm_ + "/" + longForm_; };

    if (isMandatory_ && !value_) {
        throw MandatoryError() << "Argument " << argumentName() << " is mandatory.";
    }
}

void Options::parse(int argc, char** argv)
{
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
}

std::shared_ptr<Argument> Options::getArgument(const std::string& shortForm, const std::string& longForm)
{
    std::shared_ptr<Argument> newArgument(new Argument(shortForm, longForm));
    arguments_.emplace(shortForm, newArgument);
    arguments_.emplace(longForm, newArgument);

    return newArgument;
}

std::ostream& operator<<(std::ostream& os, const Argument& arg)
{
    os << arg.shortForm_ << "/" << arg.longForm_
       << ", " << (arg.isMandatory_ ? "mandatory" : "optional")
       << ", " << (arg.isValueless_ ? "valueless" : "valueful")
       << ", " << "<" << arg.helpText_ << ">"
       ;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Options& op)
{
    for (const auto& elem : op.arguments_) {
        os << elem.first << ": " << *elem.second << std::endl;
    }
    return os;
}

} // namespace impl
} // namespace oxcd8o