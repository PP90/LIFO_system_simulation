#include "Server.h"
#include "Job_m.h"
Define_Module(Server);

//
// _______________________________________________________________________________
// The following function initialize statistics and parameter
//
void Server::initialize()
{
    rhoSig=registerSignal("rhoSig");
    stSig=registerSignal("stSig");
    serviceTime=0;
}

//
// _______________________________________________________________________________
// The following function simulate the server of the system. When a job comes from
// the queue, it will served for a time "serviceTime" that is an exponential
//  distributed RV with mean value set through parameter "stMean".
//
void Server::handleMessage(cMessage *msg)
{
    Job *j=check_and_cast<Job*>(msg);

    if(par("isScenario1").boolValue())
        {
        serviceTime=(simtime_t)exponential((double)par("meanSTexp"));
        emit(rhoSig,((double)par("meanSTexp"))/j->getIat());
        }
    else
        {
        serviceTime=(simtime_t)lognormal((double)par("meanSTlogn"),(double)par("devSTlogn"));
        double expValue=exp((double)par("meanSTlogn")+(double)(pow(par("devSTlogn"),2))/2);
        emit(rhoSig,expValue/j->getIat());
        }

//rho=lambda/mu=E[ST]/IAT
    emit(stSig,serviceTime);
    delete msg;

    cMessage *serverStatus=new cMessage();
    serverStatus->setKind(1);
    sendDelayed(serverStatus,serviceTime,"out");

}
