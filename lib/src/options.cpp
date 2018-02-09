#include "lib/include/impl.h"
#include "include/options.h"

namespace oxcd8o {

Argument::Argument(std::unique_ptr<impl::Argument>&& data)
    : impl_(std::move(data))
{
}

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

/*Argument&& Argument::multiple(bool isMultiple)
{
    impl_->multiple(isMultiple);
    return std::forward<Argument>(*this);
}*/

Argument&& Argument::valueless(bool isValueless)
{
    impl_->valueless(isValueless);
    return std::forward<Argument>(*this);
}

boost::optional<std::string> Argument::retrieveRawValue() const
{
    return impl_->value();
}

Options::Options(int argc, char** argv)
    : impl_(new impl::Options(argc, argv))
{
}

Options::~Options()
{
    delete impl_;
}

Argument Options::getArgument(const std::string& shortForm, const std::string& longForm) const
{
    return Argument(impl_->getArgument(shortForm, longForm));
}

} //namespace oxcd8o