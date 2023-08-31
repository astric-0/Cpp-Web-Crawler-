#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/StreamCopier.h>
#include <iostream>

int main() {
  Poco::Net::initializeSSL();
  Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pCertHandler =
      new Poco::Net::AcceptCertificateHandler(false);
  Poco::Net::Context::Ptr pContext =
      new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "",
                             Poco::Net::Context::VERIFY_RELAXED, 9, false,
                             "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
  Poco::Net::SSLManager::instance().initializeClient(0, pCertHandler, pContext);

  Poco::Net::HTTPSClientSession session("https://www.google.com", 443);
  // Replace "your-server-url" with the actual URL of the server you
  // want to send the GET request to    
  Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET,
                                 "/path-to-resource");
  // Replace "/path-to-resource" with the actual path
  // to the resource you want to access on the server

  session.sendRequest(request);

  Poco::Net::HTTPResponse response;
  std::istream &responseStream = session.receiveResponse(response);

  if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK) {
    std::cout << "Response Content: " << std::endl;
    Poco::StreamCopier::copyStream(responseStream, std::cout);
  } else {
    std::cout << "Error: " << response.getStatus() << " - " << response.getReason() << std::endl;
  }


}