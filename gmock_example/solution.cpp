
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

using ::testing::_;
using ::testing::A;
using ::testing::DoDefault;
using ::testing::Invoke;

class TCPLayer;

class Application;

struct Packet
{
    int seqno;
};

class Application
{
public:
    virtual bool recv(struct Packet* packet) = 0;
};

class TCPLayer
{
public:
    TCPLayer(Application& app): m_app(app) {

    }

    bool on_data(struct Packet* packet) {
        return m_app.recv(packet);
    }

private:
    Application& m_app;
};

class IPLayer
{
public:
    IPLayer(TCPLayer& tcp): m_tcp(tcp) {

    }

    bool on_data(struct Packet* packet) {
        return m_tcp.on_data(packet);
    }

private:
    TCPLayer& m_tcp;
};

class MockApplication: public Application
{
public:
    MOCK_METHOD1(recv, bool(Packet* packet));
};

class Monitor
{
public:
    bool monitor(Packet* p)
    {
        seqno.emplace_back(p->seqno);
	return true;
    }

    vector<int> get_seqno() const
    {
        return seqno;
    }

private:
    vector<int> seqno;
};

// Simple test
TEST(BasicTestCase, BasicTest)
{
    vector<int> seqno {1, 2, 3, 4, 5};

    MockApplication app;
    TCPLayer tcp(app);
    IPLayer ip(tcp);
    Packet packet;
    Monitor monitor;

    ON_CALL(app, recv(A<Packet*>()))
      .WillByDefault(Invoke(&monitor, &Monitor::monitor));

    EXPECT_CALL(app, recv(A<Packet*>()))
      .Times(seqno.size())
      .WillRepeatedly(DoDefault());

    for (const auto& s: seqno) {
      packet.seqno = s;
      ip.on_data(&packet);
    }

    ASSERT_EQ(seqno, monitor.get_seqno());
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
