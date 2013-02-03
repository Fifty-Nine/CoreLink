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
public:
    ProgramWithResources() : 
        m_resource_count(0)
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

    bool HasAllocatedResources() const
    {
        return m_resource_count > 0;
    }

    virtual void main(CoreLink::InstructionSet& is)
    {
        ResourceHandle h(m_resource_count);
        DummyProgram::main(is);
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
        
        QVERIFY(p.HasAllocatedResources());
        
        n.killProcess(pid);

        QVERIFY(!p.HasAllocatedResources());
    }
};

QTEST_MAIN(ProcessTests)
#include "ProcessTests.moc"
