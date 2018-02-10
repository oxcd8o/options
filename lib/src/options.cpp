#include "lib/include/impl.h"
#include "include/options.h"

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

boost::optional<std::string> Argument::retrieveRawValue() const
{
    return impl_->value();
}

Options::Options()
    : impl_(new impl::Options())
{}

void Options::parse(int argc, char** argv)
{
    impl_->parse(argc, argv);
}

Argument Options::argument(const std::string& shortForm, const std::string& longForm) const
{
    return Argument(impl_->getArgument(shortForm, longForm));
}

std::ostream& operator<<(std::ostream& os, const Argument& arg)
{
    os << *arg.impl_;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Options& op)
{
    os << *op.impl_;
    return os;
}

} //namespace oxcd8o