package project6.simulations;

//
// _______________________________________________________________________________
// 
//
network ProjectNet
{
    @display("bgb=547,175");
    submodules:
        Snd: Sender {
            @display("p=59,74");
        }
        Srv: Server {
            @display("p=440,74");
        }
        Q: Queue {
            @display("p=245,74;is=vl");
        }
    connections:
        Snd.out --> Q.in++;
        Srv.out --> Q.in++;
        Q.out --> Srv.in;
}
