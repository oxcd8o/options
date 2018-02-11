#include "lib/include/impl.h"
#include "include/options.h"
#include "include/error.h"

namespace oxcd8o {

Argument&& Argument::mandatory(bool isMandatory)
{
    impl_->mandatory(isMandatory);
    return std::forward<Argument>(*this);
}

Argument&& Argument::help(const std::string& text)
{
    impl_->help(text);
    return std::forward<Argument>(*this);
}

Argument&& Argument::valueless(bool isValueless)
{
    impl_->valueless(isValueless);
    return std::forward<Argument>(*this);
}

Argument&& Argument::metavar(const std::string& metaVariable)
{
    impl_->metavar(metaVariable);
    return std::forward<Argument>(*this);
}

const std::string& Argument::retrieveRawValue() const
{
    if (!*this) {
        throw UninitializedError() << impl_->name() << " is uninitialized.";
    }
    return *impl_->value();
}

Argument::operator bool() const
{
    return impl_->operator bool();
}

void Argument::setDefault(const std::string& value)
{
    impl_->defaultValue(value);
}

Options::Options()
    : impl_(new impl::Options())
{}

Options&& Options::allowUnknown(bool unknownPermitted)
{
    impl_->allowUnknown(unknownPermitted);
    return std::forward<Options>(*this);
}

void Options::parse(int argc, char** argv)
{
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    parse(args);
}

void Options::parse(const std::vector<std::string>& argv)
{
    impl_->parse(argv);
}

Argument Options::argument(const std::string& shortForm, const std::string& longForm) const
{
    return Argument(impl_->getArgument(shortForm, longForm));
}

std::string Options::getHelp() const
{
    return impl_->getHelp();
}

} //namespace oxcd8o