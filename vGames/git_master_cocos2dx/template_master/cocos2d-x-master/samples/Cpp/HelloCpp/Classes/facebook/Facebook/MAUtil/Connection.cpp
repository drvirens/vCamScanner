

//#include <conprint.h>
#include "Connection.h"
#include "util.h"
#include "vSysCall.h"
#include "helpers.h"
#include "curl/curl.h"

namespace MAUtil {

void ConnectionListener::connectFinished(Connection* conn, int result) {
	PANIC_MESSAGE("ConnectionListener::connectFinished unimplemented!");
}
void ConnectionListener::connRecvFinished(Connection* conn, int result) {
	PANIC_MESSAGE("ConnectionListener::connRecvFinished unimplemented!");
}
void ConnectionListener::connWriteFinished(Connection* conn, int result) {
	PANIC_MESSAGE("ConnectionListener::connWriteFinished unimplemented!");
}
void ConnectionListener::connReadFinished(Connection* conn, int result) {
	PANIC_MESSAGE("ConnectionListener::connReadFinished unimplemented!");
}


//if mConn == 0 then it's uninitialized
Connection::Connection(ConnectionListener* listener, MAHandle conn)
: mConn(conn), mListener(listener), mRemain(0)
{
	ASSERT_MSG(listener != NULL, "NULL listener");
//	if(mConn)
//		Environment::getEnvironment().setConnListener(mConn, this);
}

Connection::~Connection() {
	close();
}

bool Connection::isOpen() const {
	return mConn > 0;
}

int Connection::connect(const char* url) {
	ASSERT_MSG(mConn <= 0, "already connected");
	mConn = maConnect(url);
	if(mConn < 0)
		return mConn;
//	Environment::getEnvironment().setConnListener(mConn, this);
	return 1;
}

void Connection::close() {
	if(mConn > 0) {
		maConnClose(mConn);
//		Environment::getEnvironment().removeConnListener(mConn);
		mConn = 0;
	}
}

void Connection::write(const void* src, int len) {
	maConnWrite(mConn, src, len);
}
void Connection::writeFromData(MAHandle data, int offset, int len) {
	maConnWriteFromData(mConn, data, offset, len);
}
void Connection::writeTo(const void* src, int len, const MAConnAddr& dst) {
	maConnWriteTo(mConn, src, len, &dst);
}

void Connection::recv(void* dst, int maxlen) {
	maConnRead(mConn, dst, maxlen);
}
void Connection::recvToData(MAHandle data, int offset, int maxlen) {
	maConnReadToData(mConn, data, offset, maxlen);
}
void Connection::recvFrom(void* dst, int maxlen, MAConnAddr* src) {
	maConnReadFrom(mConn, dst, maxlen, src);
}

void Connection::read(void* dst, int len) {
	ASSERT_MSG(len > 0, "invalid length");
	mDst = (byte*)dst;
	mRemain = len;
	mRecv = &Connection::recvMem;
	dummy(0);	//gcc bug causes crash unless a function is called.
	(this->*mRecv)(0);
}
void Connection::recvMem(int prevRes) {
	mDst += prevRes;
	maConnRead(mConn, mDst, mRemain);
}

void Connection::readToData(MAHandle data, int offset, int len) {
	ASSERT_MSG(len > 0, "invalid length");
	mData = data;
	mOffset = offset;
	mRemain = len;
	mRecv = &Connection::recvData;
	dummy(0);	//gcc bug causes crash unless a function is called.
	(this->*mRecv)(0);
}
void Connection::recvData(int prevRes) {
	mOffset += prevRes;
	maConnReadToData(mConn, mData, mOffset, mRemain);
}

void Connection::connEvent(const MAConnEventData& data) {
	//printf("cE %i %i\n", data.handle, mConn);
	ASSERT_MSG(data.handle == mConn, "didn't register for this connection handle");
	switch(data.opType) {
	case CONNOP_CONNECT:
		mListener->connectFinished(this, data.result);
		break;
	case CONNOP_READ:
		if(mRemain > 0) {
			if(data.result < 0) {
				mRemain = 0;
				mListener->connReadFinished(this, data.result);
				return;
			}
			mRemain -= data.result;
			MAASSERT(mRemain >= 0, "");	//failure here means this lib or the MoSync runtime is broken.
			if(mRemain == 0) {
				mListener->connReadFinished(this, 1);
			} else {
				(this->*mRecv)(data.result);
			}
		} else {
			mListener->connRecvFinished(this, data.result);
		}
		break;
	case CONNOP_WRITE:
		mListener->connWriteFinished(this, data.result);
		break;
	}
}

void Connection::setListener(ConnectionListener* listener) {
	mListener = listener;
}

int Connection::getAddr(MAConnAddr* dst) {
	return maConnGetAddr(mConn, dst);
}

#define HTTP_GET 1
#define HTTP_POST 2
#define HTTP_HEAD 3
#define HTTP_PUT 4
#define HTTP_DELETE 5
  CCHttpRequest::HttpRequestType httpMethod(int method) {
    switch(method) {
      case HTTP_GET:
        return CCHttpRequest::kHttpGet;
      case HTTP_POST:
        return CCHttpRequest::kHttpPost;
//      case HTTP_HEAD:
//        return CCHttpRequest::HttpRequestType::kHttpHead;
      case HTTP_PUT:
        return CCHttpRequest::kHttpPut;
      case HTTP_DELETE:
        return CCHttpRequest::kHttpDelete;
    }
    return CCHttpRequest::kHttpGet;
  }

//if mConn == 0 then it's uninitialized
HttpConnection::HttpConnection(HttpConnectionListener* listener) : Connection(listener) {
}

int HttpConnection::create(const char* url, int method) {
	ASSERT_MSG(mConn <= 0, "already connected");
  
  mFullUrl = std::string(url);
  mHttpMethod = httpMethod(method);
  
	mConn = maHttpCreate(url, method);
	if(mConn < 0)
		return mConn;
//	Environment::getEnvironment().setConnListener(mConn, this);
	return 1;
}

void HttpConnection::setRequestHeader(const char* key, const char* value) {
	//maHttpSetRequestHeader(mConn, key, value);
  std::string theKey(key);
  std::string theValue(value);
  mHttpHeaders.push_back( theKey + std::string(": ") + theValue);
}

int HttpConnection::getResponseHeader(const char* key, String* str) {
	int res = maHttpGetResponseHeader(mConn, key, str->pointer(), 0);
	if(res < 0)
		return res;
	str->resize(res);
	return maHttpGetResponseHeader(mConn, key, str->pointer(), str->capacity() + 1);
}

void HttpConnection::finish() {
	maHttpFinish(mConn);
}

void HttpConnection::connEvent(const MAConnEventData& data) {
	ASSERT_MSG(data.handle == mConn, "didn't register for this connection handle");
	if(data.opType == CONNOP_FINISH)
		((HttpConnectionListener*)mListener)->httpFinished(this, data.result);
	else
		Connection::connEvent(data);
}

  void HttpConnection::write(const void* src, int len) {
    //maConnWrite(mConn, src, len);
    this->request(mHttpMethod, mFullUrl, (const char*)src, len, 0, 0, 0);
  }

    /// communication
  void HttpConnection::request(CCHttpRequest::HttpRequestType op,
                                    const std::string &url,
                                    const char* buffer,
                                    size_t size,
                                    CCObject *receiver,
                                    SEL_CallFuncND selector,
                                    const char* contentType)
  {
    CCHttpRequest* request = new CCHttpRequest();
    
//    std::vector<std::string> mHttpHeaders;
    
    request->setRequestType(op);
    
    std::string fullUrl;
//    if (strncmp(url.c_str(), "http", 4) != 0)
//    {
//      fullUrl = "https://api.parse.com" + url;
//    }
//    else
//    {
      fullUrl = url;
//    }
    
    request->setUrl(fullUrl.c_str());
    
    request->setResponseCallback(receiver, selector);
    
    //request->setUserData(param);
    
    CCHttpClient* client = CCHttpClient::getInstance();
    
    if (contentType)
    {
      mHttpHeaders.push_back(contentType);
    }
    
    switch(op)
    {
      case CCHttpRequest::kHttpGet:
        if (size > 0)
        {
          char* condition = curl_escape(buffer, size);
          request->setUrl((fullUrl + "?" + condition).c_str());
        }
        break;
      case CCHttpRequest::kHttpPost:
        if (contentType == 0)
        {
         // mHttpHeaders.push_back("Content-Type: application/json");
        }
        if (size > 0)
        {
          request->setRequestData(buffer, size);
        }
        break;
      case CCHttpRequest::kHttpPut:
        if (contentType == 0)
        {
          mHttpHeaders.push_back("Content-Type: application/json");
        }
        if (size > 0)
        {
          request->setRequestData(buffer, size);
        }
        break;
      case CCHttpRequest::kHttpDelete:
        break;
    }
    
//    mHttpHeaders.push_back(std::string("X-Parse-Application-Id: ") + this->_applicationId);
//    if (setMasterKey)
//    {
//      mHttpHeaders.push_back(std::string("X-Parse-Master-Key: ") + this->_masterKey);
//    }
//    else
//    {
//      mHttpHeaders.push_back(std::string("X-Parse-REST-API-Key: ") + this->_apiKey);
//    }
    request->setHeaders(mHttpHeaders);
    
    client->send(request);
    
    request->release();
    
    return ;
  }

}	//namespace MAUtil
