/**
  ******************************************************************************
  * @file           : typeid_provider.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-5-2
  ******************************************************************************
  */

#ifndef THREECPP_TYPEID_PROVIDER_H
#define THREECPP_TYPEID_PROVIDER_H

#include <cstdint>

namespace three {

    using TypeId = intptr_t;

    class TypeIdProvider {
    public:
        TypeIdProvider() = default;

        virtual ~TypeIdProvider() noexcept = 0;

        [[nodiscard]] virtual TypeId getTypeId() const = 0;

        template<typename Derived>
        static intptr_t getTypeId() {
            const static int8_t _{0};
            return reinterpret_cast<TypeId>(&_);
        }
    };

}

#define InitTypeId(class_name) \
[[nodiscard]] three::TypeId getTypeId() const override { return TypeIdProvider::getTypeId<class_name>(); }

#endif //THREECPP_TYPEID_PROVIDER_H
