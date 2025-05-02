/**
  ******************************************************************************
  * @file           : event_dispatcher.test.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-5-2
  ******************************************************************************
  */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <core/event_dispatcher.h>

using three::Event;
using three::EventDispatcher;
using three::TypeIdProvider;

class TestEvent1 : public Event {
public:
    TestEvent1() = default;

    explicit TestEvent1(int data) : _data{data} {};

    ~TestEvent1() noexcept override = default;

    InitTypeId(TestEvent1)

    int _data{0};
};

class TestEvent2 : public Event {
public:
    TestEvent2() = default;

    explicit TestEvent2(int data1, int data2) : _data1{data1}, _data2{data2} {};

    ~TestEvent2() noexcept override = default;

    InitTypeId(TestEvent2)

    int _data1{0}, _data2{0};
};

class TestClass : public EventDispatcher {
public:
    TestClass() = default;

    ~TestClass() noexcept override = default;

    virtual void func1(int data) const {
        this->dispatchEvent(std::make_shared<TestEvent1>(data));
    }

    virtual void func2(int data1, int data2) const {
        this->dispatchEvent(std::make_shared<TestEvent2>(data1, data2));
    }
};

TEST(EventDispatcher, changeEvent) {
    TestClass tc;
    int event1_data = 1, event2_data1 = 2, event2_data2 = 3;
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent1>()), 0);
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent2>()), 0);

    TestClass::Listener listener1 = [event1_data](const std::shared_ptr<Event> &event) {
        std::shared_ptr<TestEvent1> te = std::reinterpret_pointer_cast<TestEvent1>(event);
        EXPECT_EQ(te->_data, event1_data);
    };

    TestClass::Listener listener1_2 = [](const std::shared_ptr<Event> &event) {};

    TestClass::Listener listener2 = [event2_data1, event2_data2](const std::shared_ptr<Event> &event) {
        std::shared_ptr<TestEvent2> te = std::reinterpret_pointer_cast<TestEvent2>(event);
        EXPECT_EQ(te->_data1, event2_data1);
        EXPECT_EQ(te->_data2, event2_data2);
    };

    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent1>()), 0);
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent2>()), 0);

    EXPECT_NO_THROW(tc.addEventListener(TypeIdProvider::getTypeId<TestEvent1>(), listener1));
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent1>()), 1);
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent2>()), 0);

    EXPECT_NO_THROW(tc.addEventListener(TypeIdProvider::getTypeId<TestEvent2>(), listener2));
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent2>()), 1);

    EXPECT_NO_THROW(tc.addEventListener(TypeIdProvider::getTypeId<TestEvent1>(), listener1_2));
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent1>()), 2);

    EXPECT_NO_THROW(tc.addEventListener(TypeIdProvider::getTypeId<TestEvent1>(), listener1));
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent1>()), 3);

    EXPECT_NO_THROW(tc.clearEventListener(TypeIdProvider::getTypeId<TestEvent1>()));
    EXPECT_EQ(tc.getListenerCount(TypeIdProvider::getTypeId<TestEvent1>()), 0);

    EXPECT_NO_THROW(tc.clearEventListener(TypeIdProvider::getTypeId<TestEvent1>()));
}

class MockListener {
public:
    MOCK_METHOD(void, onEvent1, (), ());
    MOCK_METHOD(void, onEvent1_2, (), ());
    MOCK_METHOD(void, onEvent2, (), ());
};

TEST(EventDispatcher, dispatchEvent) {
    TestClass tc;
    int event1_data = 1, event2_data1 = 2, event2_data2 = 3;
    MockListener ml;

    TestClass::Listener listener1 = [&ml](const std::shared_ptr<Event> &event) {
        ml.onEvent1();
    };

    TestClass::Listener listener1_2 = [&ml](const std::shared_ptr<Event> &event) {
        ml.onEvent1_2();
    };

    TestClass::Listener listener2 = [&ml](const std::shared_ptr<Event> &event) {
        ml.onEvent2();
    };

    tc.addEventListener(TypeIdProvider::getTypeId<TestEvent1>(), listener1);
    tc.addEventListener(TypeIdProvider::getTypeId<TestEvent2>(), listener2);

    EXPECT_CALL(ml, onEvent1())
            .Times(3);
    EXPECT_CALL(ml, onEvent1_2())
            .Times(2);
    EXPECT_CALL(ml, onEvent2())
            .Times(1);

    tc.func1(event1_data);
    tc.addEventListener(TypeIdProvider::getTypeId<TestEvent1>(), listener1_2);
    tc.func1(event1_data);
    tc.func1(event1_data);

    tc.func2(event2_data1, event2_data2);

}