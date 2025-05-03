/**
  ******************************************************************************
  * @file           : typeid_provider.h
  * @author         : An Kaichen
  * @brief          : Provides a mechanism for obtaining unique type identifiers (TypeId) for classes.
  *                   The TypeId is used to differentiate types at runtime, which is particularly useful
  *                   for dynamic type identification or type comparison in generic code.
  * @attention      : The `TypeIdProvider` class is intended to be inherited by other classes.
  *                   The macro `InitTypeId(class_name)` should be used in the derived class to implement
  *                   the `getTypeId()` function, which will return the unique type identifier for that class.
  * @date           : 25-5-2
  ******************************************************************************
  */

#ifndef THREECPP_TYPEID_PROVIDER_H
#define THREECPP_TYPEID_PROVIDER_H

#include <cstdint>

namespace three {

    /**
     * Unique ID for each type
     */
    using TypeId = intptr_t;

    /**
     * Provides an interface for obtaining TypeId
     */
    class TypeIdProvider {
    public:
        TypeIdProvider() = default;

        virtual ~TypeIdProvider() noexcept = 0;

        /**
         * Function for obtaining TypeId
         * In the subclass, use the InitTypeId(class_name) macro to rewrite this function
         * @return TypeId
         */
        [[nodiscard]] virtual TypeId getTypeId() const = 0;

        /**
         * A template function used to generate a TypeId for each type,
         * which can be used to obtain the TypeId by class name
         * @tparam Derived class name
         * @return TypeId of Derived
         */
        template<typename Derived>
        inline static intptr_t getTypeId() {
            const static int8_t dummy{0};
            return reinterpret_cast<TypeId>(&dummy);
        }
    };

}

#define InitTypeId(class_name) \
[[nodiscard]] three::TypeId getTypeId() const override { return TypeIdProvider::getTypeId<class_name>(); }

#endif //THREECPP_TYPEID_PROVIDER_H
