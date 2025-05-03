/**
  ******************************************************************************
  * @file           : instanceid_provider.test.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-5-3
  ******************************************************************************
  */

#include <gtest/gtest.h>
#include <memory>

#include <core/instanceid_provider.h>

using three::InstanceId;
using three::InstanceIdProvider;
using three::instanceOf;

namespace InstanceIdProviderTest {
    class Base : public InstanceIdProvider<Base> {
    };

    class Derived : public Base, public InstanceIdProvider<Derived> {
    };
}

TEST(InstanceIdProvider, CreateInstance) {
    using InstanceIdProviderTest::Base;
    using InstanceIdProviderTest::Derived;
    std::shared_ptr<Base> b1 = std::make_shared<Base>();
    std::shared_ptr<Base> b2 = std::make_shared<Base>();
    EXPECT_EQ(b1->getInstanceId(), b1->getInstanceId());
    EXPECT_NE(b1->getInstanceId(), b2->getInstanceId());
}

TEST(InstanceIdProvider, DerivedInstance) {
    using InstanceIdProviderTest::Base;
    using InstanceIdProviderTest::Derived;
    std::shared_ptr<Base> b1 = std::make_shared<Base>();
    std::shared_ptr<Derived> d1 = std::make_shared<Derived>();
    std::shared_ptr<Derived> d2 = std::make_shared<Derived>();
    EXPECT_EQ(b1->getInstanceId(), b1->instanceOf<Base>::getInstanceId());
    EXPECT_NE(b1->getInstanceId(), d1->instanceOf<Base>::getInstanceId());
    EXPECT_NE(d1->instanceOf<Base>::getInstanceId(), d2->instanceOf<Base>::getInstanceId());
    EXPECT_NE(d1->instanceOf<Derived>::getInstanceId(), d2->instanceOf<Derived>::getInstanceId());
}
