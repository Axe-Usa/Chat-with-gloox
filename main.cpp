#include <client.h>
#include <messagehandler.h>
#include <message.h>
#include <presencehandler.h>
#include <connectionlistener.h>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
using namespace gloox;
//my one
const string LOGIN = "gmail.com";
ostream& operator<<(ostream& os, Message::MessageType type) {
    switch (type) {
        case Message::Chat:
            os << "Chat";
            break;
        case Message::Error:
            os << "Error";
            break;
        case Message::Groupchat:
            os << "Groupchat";
            break;
        case Message::Headline:
            os << "Headline";
            break;
        case Message::Normal:
            os << "Normal";
            break;
        case Message::Invalid:
            os << "Invalid";
            break;
        default:
            os << "unknown type";
            break;
    }
return os;
}

ostream& operator<<(ostream& os, const Message& stanza) {
    os << "type:'" << stanza.subtype() <<  "' from:'" << stanza.from().full() << "' body:'" << stanza.body() << "'";
    return os;
}

class Bot : public MessageHandler,
            /*public PresenceHandler,*/
            public ConnectionListener
            /*,public RosterListener*/{
 public:
   Bot(){
      JID jid( "ringostar@jabber.at" );
      client = new Client( jid, "k1k1k1k1" );
      client->registerConnectionListener( this );
      client->registerMessageHandler( this );
      client->connect(true);
   }

    virtual void onConnect() {
        cout << "It is connected good:)"  << endl;
        //sleep(5);
        client->disconnect();
    }

    virtual void onDisconnect(ConnectionError e) {
        cout << "ConnListener::onDisconnect() " << endl;
    }

    virtual bool onTLSConnect(const CertInfo& Info) {

       time_t tm = Info.date_from;
       time_t tm_to = Info.date_to;
       cout << "\t Certificate information to " << LOGIN << endl;
       cout << "\t========================================" << endl;
      // number code << "\tServer status: " << Info.status;
        if (Info.status !=0)
            {
            cout << "\t !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            cout << "\t !!!  The certificate has a problem !!!" << endl;
            cout << "\t !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            // parsing binary Status Cert
            if ((CertInvalid) & Info.status)
                {
                    cout << "\t- The certificate is not trusted " << endl;
                }
            if (( CertSignerUnknown) & Info.status)
                {
                    cout << "\t- The certificate hasn't got a kown issuer" << endl;
                }
            if ((CertRevoked) & Info.status)
                {
                    cout << "\t- The certificate has been revoked " << endl;
                }
            if ((CertExpired) & Info.status)
                {
                    cout << "\t- The certificate has expired " << endl;
                }
            if ((CertNotActive) & Info.status)
                {
                    cout << "\t- The certificate is not yet active " << endl;
                }
            if ((CertWrongPeer) & Info.status)
                {
                    cout << "\t- The certificate has not issued for the peer we're connected to " << endl;
                }
            if ((CertSignerNotCa) & Info.status)
                {
                    cout << "\t- The signer is not CA " << endl;
                }
            cout << endl;
            }
            // end parsing
        else
            // if Info.status=0 sertificate is valide
            cout << " *** Cert is OK!" << endl;

       cout << "\tChain: " << Info.chain << endl;
       cout << "\tIssuer: " << Info.issuer << endl;
       cout << "\tServer: " << Info.server << endl;
       cout << "\tCert date from: " << ctime(&tm);
       cout << "\tCert date to: " << ctime(&tm_to);
       cout << "\tProtocol: " << Info.protocol << endl;
       cout << "\tCipher: " << Info.cipher << endl;
       cout << "\tMAC: " << Info.mac << endl;
       cout << "\tCompression: " << Info.compression << endl;
       cout << "\t========================================" << endl;
     return true;

    }

   virtual void handleMessage( const Message& stanza,
                               MessageSession* session = 0 ){
     Message msg(Message::Chat, stanza.from(), "hello world" );
     client->send( msg );
   }

 private:
   Client* client;
};

int main( int argc, char* argv[] ){
    cout << "1" << endl;
    Bot b;
}
