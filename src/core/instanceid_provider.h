/**
  ******************************************************************************
  * @file           : instanceid_provider.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-5-3
  ******************************************************************************
  */

#ifndef THREECPP_INSTANCEID_PROVIDER_H
#define THREECPP_INSTANCEID_PROVIDER_H

#include <cstdint>
#include <atomic>
#include <type_traits>

namespace three {

    /**
     * Unique ID for each instance
     */
    using InstanceId = std::size_t;

    /**
     * Provides an interface for obtaining InstanceId
     * @tparam Derived subclass
     */
    template<typename Derived>
    class InstanceIdProvider {
    public:
        InstanceIdProvider() = default;

        virtual ~InstanceIdProvider() noexcept = 0;

        /**
         * Get the InstanceId of a variable.
         * If the call is ambiguous due to inheritance, you can use `instanceOf<Derived>::getInstanceId()`
         * @return InstanceId
         */
        [[nodiscard]] inline InstanceId getInstanceId() const {
            return this->_instanceId;
        }

    private:
        static std::atomic<InstanceId> _derivedId;
        const InstanceId _instanceId{_derivedId++};
    };

    template<typename Derived>
    InstanceIdProvider<Derived>::~InstanceIdProvider() noexcept = default;

    template<typename Derived>
    std::atomic<InstanceId> InstanceIdProvider<Derived>::_derivedId{0};

    template<typename Derived>
    using instanceOf = InstanceIdProvider<Derived>;

}

#endif //THREECPP_INSTANCEID_PROVIDER_H
