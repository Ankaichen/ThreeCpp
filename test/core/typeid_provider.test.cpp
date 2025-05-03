/**
  ******************************************************************************
  * @file           : typeid_provider.test.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-5-2
  ******************************************************************************
  */

#include <gtest/gtest.h>
#include <memory>

#include <core/typeid_provider.h>

using three::TypeId;
using three::TypeIdProvider;

namespace TypeIdProviderTest {

    class Base : public TypeIdProvider {
    public:
        InitTypeId(Base)
    };

    class Derived1 : public Base {
    public:
        InitTypeId(Derived1)
    };

    class Derived2 : public Base {
    public:
        InitTypeId(Derived2)
    };

    class Other : public TypeIdProvider {
    public:
        InitTypeId(Other)
    };

}

TEST(TypeIdProvider, SameType) {
    using TypeIdProviderTest::Base;
    auto b1 = std::make_shared<Base>();
    auto b2 = std::make_shared<Base>();
    EXPECT_EQ(TypeIdProvider::getTypeId<Base>(), TypeIdProvider::getTypeId<Base>());
    EXPECT_EQ(b1->getTypeId(), TypeIdProvider::getTypeId<Base>());
    EXPECT_EQ(b2->getTypeId(), TypeIdProvider::getTypeId<Base>());
    EXPECT_EQ(b1->getTypeId(), b1->getTypeId());
    EXPECT_EQ(b2->getTypeId(), b2->getTypeId());
    EXPECT_EQ(b1->getTypeId(), b2->getTypeId());
}

TEST(TypeIdProvider, DifferentType) {
    using TypeIdProviderTest::Base;
    using TypeIdProviderTest::Other;
    auto b1 = std::make_shared<Base>();
    auto o1 = std::make_shared<Other>();
    EXPECT_NE(TypeIdProvider::getTypeId<Base>(), TypeIdProvider::getTypeId<Other>());
    EXPECT_NE(b1->getTypeId(), TypeIdProvider::getTypeId<Other>());
    EXPECT_NE(o1->getTypeId(), TypeIdProvider::getTypeId<Base>());
    EXPECT_NE(b1->getTypeId(), o1->getTypeId());
}

TEST(TypeIdProvider, DerivedType) {
    using TypeIdProviderTest::Base;
    using TypeIdProviderTest::Other;
    using TypeIdProviderTest::Derived1;
    using TypeIdProviderTest::Derived2;
    std::shared_ptr<Base> b = std::make_shared<Base>(),
            d1 = std::make_shared<Derived1>(), d2 = std::make_shared<Derived2>();
    EXPECT_EQ(d1->getTypeId(), TypeIdProvider::getTypeId<Derived1>());
    EXPECT_EQ(d2->getTypeId(), TypeIdProvider::getTypeId<Derived2>());
    EXPECT_NE(d1->getTypeId(), TypeIdProvider::getTypeId<Base>());
    EXPECT_NE(d2->getTypeId(), TypeIdProvider::getTypeId<Base>());
    EXPECT_NE(d1->getTypeId(), TypeIdProvider::getTypeId<Derived2>());
    EXPECT_NE(d2->getTypeId(), TypeIdProvider::getTypeId<Derived1>());
    EXPECT_NE(d1->getTypeId(), b->getTypeId());
    EXPECT_NE(d2->getTypeId(), b->getTypeId());
    EXPECT_NE(d1->getTypeId(), d2->getTypeId());
}
