package project6.simulations;

//
// _______________________________________________________________________________
// 
//
simple Sender
{
    parameters:
        double meanIAT=default(1);
        @statistic[iatSig](title="IAT"; source="iatSig";record=vector,stats);
    gates:
        output out;
}
