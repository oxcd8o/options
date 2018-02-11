#pragma once

#include <exception>
#include <string>

#include <boost/lexical_cast.hpp>

namespace oxcd8o {

class Error: public std::exception
{
    public:
        Error(const std::string& prefix = "Error: ")
            : what_(prefix)
        {}

        template <class T>
        Error&& operator<<(const T& data)
        {
            what_ += boost::lexical_cast<std::string>(data);
            return std::forward<Error>(*this);
        }

        virtual const char* what() const noexcept override { return what_.c_str(); }

    private:
        std::string what_;
};

#define DEFINE_ERROR(name) class name: public Error { public: name(): Error(#name ": ") {} };
DEFINE_ERROR(ValueError)
DEFINE_ERROR(MandatoryError)
DEFINE_ERROR(UnknownArgumentError)
DEFINE_ERROR(UninitializedError)
DEFINE_ERROR(SanityError)
#undef DEFINE_ERROR

} // namespace oxcd8o