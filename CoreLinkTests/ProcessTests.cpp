#include <QtTest/QtTest>

#include "CoreLink/Node.h"
#include "CoreLink/Process.h"
#include "CoreLink/Program.h"
#include "CoreLink/InstructionSet.h"

class DummyProgram : public CoreLink::Program
{
public:
    virtual void main(CoreLink::InstructionSet& is)
    {
        while (true)
        {
            is.noOp();
        }
    }
};

class ProgramWithResources : public DummyProgram
{
    int m_resource_count;
    bool m_exit;
public:
    ProgramWithResources() : 
        m_resource_count(0),
        m_exit(false)
    {
    }

    struct ResourceHandle
    {
        int& m_count;
    public:
        ResourceHandle(int& count) : 
            m_count(count)
        {
            m_count++;
        }

        ~ResourceHandle()
        {
            m_count--;
        }
    };

    bool hasAllocatedResources() const
    {
        return m_resource_count > 0;
    }

    virtual void main(CoreLink::InstructionSet& is)
    {
        ResourceHandle h(m_resource_count);

        while (!m_exit)
        {
            is.noOp();
        }
    }

    void enableExit()
    {
        m_exit = true;
    }
};

class ProcessTests : public QObject
{
    Q_OBJECT
private slots:
    void sanity()
    {
        DummyProgram p;
        CoreLink::Node n;

        QVERIFY(n.installProgram(&p));
        QVERIFY(n.getInstalledPrograms().contains(p.getID()));

        CoreLink::PID pid = n.spawnProcess(p.getID());

        QVERIFY(pid != CoreLink::PID());
        QVERIFY(n.getRunningPrograms().contains(pid));

        n.tick(500);

        QVERIFY(n.killProcess(pid));
        QVERIFY(!n.getRunningPrograms().contains(pid));

        QVERIFY(n.deleteProgram(p.getID()));
        QVERIFY(!n.getInstalledPrograms().contains(p.getID()));
    }

    void stackUnwindsWhenKilled()
    {
        ProgramWithResources p;
        CoreLink::Node n;

        n.installProgram(&p);
        CoreLink::PID pid = n.spawnProcess(p.getID());

        n.tick(500);
        
        QVERIFY(p.hasAllocatedResources());
        
        n.killProcess(pid);

        QVERIFY(!p.hasAllocatedResources());
    }

    void stackUnwindsOnImplicitExit()
    {
        ProgramWithResources p;
        CoreLink::Node n;


        n.installProgram(&p);
        (void)n.spawnProcess(p.getID());

        n.tick(1);
        p.enableExit();

        QVERIFY(p.hasAllocatedResources());

        n.tick(1);

        QVERIFY(!p.hasAllocatedResources());
    }

    void canRunMultiplePrograms()
    {
        CoreLink::Node n;
        DummyProgram p1, p2;

        QVERIFY(n.installProgram(&p1));
        QVERIFY(n.installProgram(&p2));

        CoreLink::PID p1_pid = n.spawnProcess(p1.getID());
        CoreLink::PID p2_pid = n.spawnProcess(p2.getID());

        QVERIFY(p1_pid != CoreLink::PID());
        QVERIFY(p2_pid != CoreLink::PID());

        CoreLink::PIDList pids = n.getRunningPrograms();
        QVERIFY(pids.contains(p1_pid) && pids.contains(p2_pid));

        n.tick(500);

        QVERIFY(n.killProcess(p1_pid));
        QVERIFY(!n.getRunningPrograms().contains(p1_pid));
    }
};

QTEST_MAIN(ProcessTests)
#include "ProcessTests.moc"
